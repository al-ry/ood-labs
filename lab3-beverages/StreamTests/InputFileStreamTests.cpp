#include "stdafx.h"
#include "../Streams/CFileInputStream.h"
#include <filesystem>

auto tempPath = std::filesystem::temp_directory_path();

struct EmptyInputStream
{
	CFileInputStream fileStream;
	EmptyInputStream()
		: fileStream("test_files/empty.bin"){
	}
};

BOOST_FIXTURE_TEST_SUITE(Test_file_input_stream, EmptyInputStream)
	BOOST_AUTO_TEST_SUITE(when_input_file_stream_is_empty)
		BOOST_AUTO_TEST_CASE(is_eof)
		{
			BOOST_CHECK_THROW(fileStream.ReadByte(), std::ios_base::failure);
			BOOST_CHECK(fileStream.IsEOF());
		}
		BOOST_AUTO_TEST_CASE(cannot_read_block_from_empty_stream)
		{
			uint8_t *block = (uint8_t *)malloc(5 * sizeof(uint8_t)); 
			BOOST_CHECK_THROW(fileStream.ReadBlock(block, 5), std::ios_base::failure);
			BOOST_CHECK(fileStream.IsEOF());
			free(block);
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct StreamWithData
	{
		CFileInputStream inputStream;
		StreamWithData()
			: inputStream("test_files/data.bin")
		{
		}
	};
	BOOST_FIXTURE_TEST_SUITE(when_stream_contains_data, StreamWithData)
		BOOST_AUTO_TEST_CASE(can_read_byte)
		{
			BOOST_CHECK(inputStream.ReadByte() == 'q');
			BOOST_CHECK(!inputStream.IsEOF());
			BOOST_CHECK(inputStream.ReadByte() == 'w');
		}
		BOOST_AUTO_TEST_CASE(can_read_block_of_byte)
		{
			std::string result = "qwerty!";
			uint8_t* buffer = (uint8_t*)malloc(3 * sizeof(uint8_t));
			std::streamsize size = inputStream.ReadBlock(buffer, 3);
			for (std::streamsize i = 0; i < size; i++)
			{
				BOOST_CHECK(buffer[(size_t)i] == result[(size_t)i]);
			}
			free(buffer);
		}
		BOOST_AUTO_TEST_CASE(can_read_all_stream)
		{
			std::string result = "qwerty!";
			uint8_t* buffer = (uint8_t*)malloc(7 * sizeof(uint8_t));
			std::streamsize size = inputStream.ReadBlock(buffer, 7);
			for (std::streamsize i = 0; i < size; i++)
			{
				BOOST_CHECK(buffer[(size_t)i] == result[(size_t)i]);
			}
			free(buffer);
		}
		BOOST_AUTO_TEST_CASE(when_trying_read_too_big_block)
		{
			uint8_t* buffer = (uint8_t*)malloc(500 * sizeof(uint8_t));
			BOOST_CHECK_THROW(inputStream.ReadBlock(buffer, 500), std::ios_base::failure);
			free(buffer);
		}
		
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()