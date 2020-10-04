#include "stdafx.h"
#include "../Streams/CMemoryInputStream.h"

struct EmptyMemoryData
{
	std::vector<uint8_t> data;
};

struct EmptyInputMemoryStream : EmptyMemoryData
{
	CMemoryInputStream inputMemoryStream;
	EmptyInputMemoryStream()
		: inputMemoryStream(data)
	{
	}
};


BOOST_FIXTURE_TEST_SUITE(Test_memory_input_stream, EmptyInputMemoryStream)
	BOOST_AUTO_TEST_SUITE(when_input_stream_data_empty)
		BOOST_AUTO_TEST_CASE(is_eof)
		{
			BOOST_CHECK(inputMemoryStream.IsEOF());
		}
		BOOST_AUTO_TEST_CASE(shouldnt_read_byte_from_empty_stream)
		{
			BOOST_CHECK_THROW(inputMemoryStream.ReadByte(), std::ios_base::failure);
		}
		BOOST_AUTO_TEST_CASE(shouldnt_read_block_from_empty_stream)
		{
			uint8_t arr[5] = {0,1,2,3,4};
			BOOST_CHECK_EQUAL(inputMemoryStream.ReadBlock(&arr, 5), 0);
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct MemoryWithData
	{
		std::vector<uint8_t> data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	};
	struct InputMemoryStreamWithData : MemoryWithData
	{
		CMemoryInputStream inputMemoryStream;
		InputMemoryStreamWithData()
			: inputMemoryStream(data)
		{
		}
	};
	BOOST_FIXTURE_TEST_SUITE(when_stream_has_some_data, InputMemoryStreamWithData)
		BOOST_AUTO_TEST_CASE(start_position_should_not_be_eof)
		{
			BOOST_CHECK(!inputMemoryStream.IsEOF());
		}
		BOOST_AUTO_TEST_CASE(can_read_bytes_from_stream)
		{
			auto readByte = inputMemoryStream.ReadByte();
			BOOST_CHECK(readByte == 0);
			readByte = inputMemoryStream.ReadByte();
			BOOST_CHECK(readByte == 1);
		}
		BOOST_AUTO_TEST_CASE(can_read_block_from_stream)
		{
			std::streamsize size = 5;
			uint8_t* arrBytes = (uint8_t*)malloc((size_t)size * sizeof(uint8_t));
			auto readSize = inputMemoryStream.ReadBlock(arrBytes, size);
			BOOST_CHECK(readSize == 5);
			for  (std::streamsize i = 0; i < readSize; i++)
			{
				BOOST_CHECK(arrBytes[i] == i);
			}
			free(arrBytes);
		}
		BOOST_AUTO_TEST_SUITE(when_buffer_size_greater_than_stream_size)
			BOOST_AUTO_TEST_CASE(should_read_all_block)
			{
				std::streamsize size = 20;
				uint8_t* arrBytes = (uint8_t*)malloc((size_t)size * sizeof(uint8_t));
				auto readSize = inputMemoryStream.ReadBlock(arrBytes, size);
				BOOST_CHECK(readSize == 10);
				for (std::streamsize i = 0; i < readSize; i++)
				{
					BOOST_CHECK(arrBytes[i] == i);
				}
				free(arrBytes);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()