#include "stdafx.h"
#include "../Streams/CMemoryInputStream.h"
#include "../Streams/CInputStreamDecompressor.h"
#include "TestsUtils.h"

std::vector<uint8_t> MakeArrayWithPacket(uint8_t amount, uint8_t byte)
{
	std::vector<uint8_t> arr;
	arr.push_back(amount);
	arr.push_back(byte);
	return arr;
}

std::unique_ptr<CInputStreamDecompressor> MakeInputDecompressDecorator(std::vector<uint8_t>& data)
{
	auto stream = std::make_unique<CMemoryInputStream>(data);
	auto decompressedStream = std::make_unique<CInputStreamDecompressor>(std::move(stream));
	return decompressedStream;
}

BOOST_AUTO_TEST_SUITE(Test_decompressed_input_stream_with_data)
	BOOST_AUTO_TEST_SUITE(when_reading_sequence_of_byte)
		BOOST_AUTO_TEST_CASE(should_decompress_data)
		{
			std::vector<uint8_t> vec = { 50, 48 };
			auto decompressedStream = MakeInputDecompressDecorator(vec);
			for (size_t i = 0; i < vec[0]; i++)
			{
				BOOST_CHECK(decompressedStream->ReadByte() == 48);
			}				
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(when_reading_2_difference_sequence_of_byte)
		BOOST_AUTO_TEST_CASE(should_decompress_data)
		{
			std::vector<uint8_t> vec = { 50, 48, 3, 49 };
			auto decompressedStream = MakeInputDecompressDecorator(vec);
			for (size_t i = 0; i < vec[0]; i++)
			{
				BOOST_CHECK(decompressedStream->ReadByte() == 48);
			}
			for (size_t i = 0; i < vec[2]; i++)
			{
				BOOST_CHECK(decompressedStream->ReadByte() == 49);
			}
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(when_reading_block_with_0_size)
		BOOST_AUTO_TEST_CASE(should_return_0_size)
		{
			std::vector<uint8_t> vec = { 20, 48 };
			auto decompressedStream = MakeInputDecompressDecorator(vec);
			std::array<uint8_t, 0> arr = {};
			BOOST_CHECK(decompressedStream->ReadBlock(arr.data(), arr.size()) == 0);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(when_stream_has_1_byte)
		BOOST_AUTO_TEST_CASE(should_throw_exception)
		{
			std::vector<uint8_t> vec = { 50 };
			auto decompressedStream = MakeInputDecompressDecorator(vec);
			std::array<uint8_t, 4> arr = { 1, 2, 3 };
			BOOST_CHECK_THROW(decompressedStream->ReadBlock(arr.data(), arr.size()), std::logic_error);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(when_reading_block_of_2_rle_pack)
		BOOST_AUTO_TEST_CASE(should_decompress_block)
		{
			std::vector<uint8_t> vec = { 20, 48, 20, 49 };
			auto decompressedStream = MakeInputDecompressDecorator(vec);
			std::array<uint8_t, 25> arr;
			std::streamsize size = decompressedStream->ReadBlock(arr.data(), arr.size());
			BOOST_CHECK(size == 25);
			for (size_t i = 0; i < 20; i++)
			{
				BOOST_CHECK_EQUAL(arr[i], 48);
			}
			for (size_t i = 20; i < 25; i++)
			{
				BOOST_CHECK_EQUAL(arr[i], 49);
			}
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(when_reading_block_that_greater_than_stream_size)
		BOOST_AUTO_TEST_CASE(should_return_correct_read_size)
		{
			std::vector<uint8_t> vec = { 255, 48, 255, 49 };
			auto decompressedStream = MakeInputDecompressDecorator(vec);
			std::array<uint8_t, 1000> arr;
			std::streamsize size = decompressedStream->ReadBlock(arr.data(), arr.size());
			BOOST_CHECK(size == 510);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(when_reading_block_of_byte)
		BOOST_AUTO_TEST_CASE(should_return_correct_read_size)
		{
			std::vector<uint8_t> vec = { 1, 48 };
			auto decompressedStream = MakeInputDecompressDecorator(vec);
			std::array<uint8_t, 2> arr;
			std::streamsize size = decompressedStream->ReadBlock(arr.data(), arr.size());
			BOOST_CHECK(size == 1);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

