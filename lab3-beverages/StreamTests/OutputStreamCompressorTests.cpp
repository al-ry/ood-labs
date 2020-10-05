#include "stdafx.h"
#include "../Streams/COutputStreamCompressor.h"
#include "../Streams/CMemoryOutputStream.h"
#include "../Streams/CFileOutputStream.h"
#include "TestsUtils.h"

void WriteRepeatedByte(size_t amount, uint8_t data, std::unique_ptr<COutputStreamCompressor>& stream)
{
	for (size_t i = 0; i < amount; i++)
	{
		stream->WriteByte(data);
	}
}

BOOST_AUTO_TEST_SUITE(Test_compress_decorator_for_file_output_stream)
	BOOST_AUTO_TEST_SUITE(Test_write_byte)
		BOOST_AUTO_TEST_CASE(compress_0_bytes)
		{
			auto stream = std::make_unique<CFileOutputStream>("test_files/compress0bytes.bin");
			auto compressedStream = std::make_unique<COutputStreamCompressor>(std::move(stream));
			std::string result = GetFileContent("test_files/compress0bytes.bin");
			BOOST_CHECK(result == "");
		}
		BOOST_AUTO_TEST_CASE(compress_1_bytes)
		{
			{		
				auto stream = std::make_unique<CFileOutputStream>("test_files/compress1byte.bin");
				auto compressedStream = std::make_unique<COutputStreamCompressor>(std::move(stream));
				compressedStream->WriteByte(48);
			}
			std::string result = GetFileContent("test_files/compress1byte.bin");
			BOOST_CHECK_EQUAL(result, "\x1\x30");
		}
		BOOST_AUTO_TEST_CASE(can_compress_50_identical_bytes)
		{
			{
				auto stream = std::make_unique<CFileOutputStream>("test_files/compress50bytes.bin");
				auto compressedStream = std::make_unique<COutputStreamCompressor>(std::move(stream));
				WriteRepeatedByte(50, 48, compressedStream);
			}
			std::string result = GetFileContent("test_files/compress50bytes.bin");
			BOOST_CHECK_EQUAL(result, "\x32\x30");
		}
		BOOST_AUTO_TEST_SUITE(when_gives_255_bytes)
			BOOST_AUTO_TEST_CASE(should_compress_255_bytes)
			{
				{
					auto stream = std::make_unique<CFileOutputStream>("test_files/compress255bytes.bin");
					auto compressedStream = std::make_unique<COutputStreamCompressor>(std::move(stream));
					WriteRepeatedByte(255, 48, compressedStream);
				}
				std::string result = GetFileContent("test_files/compress255bytes.bin");
				BOOST_CHECK_EQUAL(result, "\xFF\x30");
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(when_gives_greater_than_255_bytes)
			BOOST_AUTO_TEST_CASE(should_separate_bytes_to_differents_packages)
			{
				{
					auto stream = std::make_unique<CFileOutputStream>("test_files/compress300bytes.bin");
					auto compressedStream = std::make_unique<COutputStreamCompressor>(std::move(stream));
					WriteRepeatedByte(300, 48, compressedStream);
				}
				std::string result = GetFileContent("test_files/compress300bytes.bin");
				BOOST_CHECK_EQUAL(result, "\xFF\x30\x2D\x30");
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(when_gives_two_different_sequences)
			BOOST_AUTO_TEST_CASE(should_compress_these_to_different_packs)
			{
				{
					auto stream = std::make_unique<CFileOutputStream>("test_files/compress_two_diffrent_sequences.bin");
					auto compressedStream = std::make_unique<COutputStreamCompressor>(std::move(stream));
					WriteRepeatedByte(50, 48, compressedStream);
					WriteRepeatedByte(20, 50, compressedStream);
				}
				std::string result = GetFileContent("test_files/compress_two_diffrent_sequences.bin");
				BOOST_CHECK_EQUAL(result, "\x32\x30\x14\x32");
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(Test_write_block)
		BOOST_AUTO_TEST_CASE(compress_1_bytes)
		{

			{
				auto stream = std::make_unique<CFileOutputStream>("test_files/compress1byte.bin");
				auto compressedStream = std::make_unique<COutputStreamCompressor>(std::move(stream));
				std::array<uint8_t, 1> arr = { 1 };
				compressedStream->WriteBlock(arr.data(), arr.size());
			}
			std::string result = GetFileContent("test_files/compress1byte.bin");
			BOOST_CHECK_EQUAL(result, "\x1\x1");
		}
		BOOST_AUTO_TEST_CASE(can_compress_50_identical_bytes)
		{
			{
				auto stream = std::make_unique<CFileOutputStream>("test_files/compress50bytes.bin");
				auto compressedStream = std::make_unique<COutputStreamCompressor>(std::move(stream));
				std::vector<uint8_t> arr = PushIdenticalSymbolsToArray(50, 48);
				compressedStream->WriteBlock(arr.data(), arr.size());
			}
			std::string result = GetFileContent("test_files/compress50bytes.bin");
			BOOST_CHECK_EQUAL(result, "\x32\x30");
		}
		BOOST_AUTO_TEST_SUITE(when_gives_255_bytes)
			BOOST_AUTO_TEST_CASE(should_compress_255_bytes)
			{
				{
					auto stream = std::make_unique<CFileOutputStream>("test_files/compress255bytes.bin");
					auto compressedStream = std::make_unique<COutputStreamCompressor>(std::move(stream));
					std::vector<uint8_t> arr = PushIdenticalSymbolsToArray(255, 48);
					compressedStream->WriteBlock(arr.data(), arr.size());
				}
				std::string result = GetFileContent("test_files/compress255bytes.bin");
				BOOST_CHECK_EQUAL(result, "\xFF\x30");
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(when_gives_greater_than_255_bytes)
			BOOST_AUTO_TEST_CASE(should_separate_bytes_to_differents_packages)
			{
				{
					auto stream = std::make_unique<CFileOutputStream>("test_files/compress300bytes.bin");
					auto compressedStream = std::make_unique<COutputStreamCompressor>(std::move(stream));
					std::vector<uint8_t> arr = PushIdenticalSymbolsToArray(300, 48);
					compressedStream->WriteBlock(arr.data(), arr.size());
				}
				std::string result = GetFileContent("test_files/compress300bytes.bin");
				BOOST_CHECK_EQUAL(result, "\xFF\x30\x2D\x30");
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(when_gives_two_different_sequences)
			BOOST_AUTO_TEST_CASE(should_compress_these_to_different_packs)
			{
				{
					auto stream = std::make_unique<CFileOutputStream>("test_files/compress_two_diffrent_sequences.bin");
					auto compressedStream = std::make_unique<COutputStreamCompressor>(std::move(stream));
					std::vector<uint8_t> arr1 = PushIdenticalSymbolsToArray(50, 48);
					compressedStream->WriteBlock(arr1.data(), arr1.size());
					std::vector<uint8_t> arr2 = PushIdenticalSymbolsToArray(20, 50);
					compressedStream->WriteBlock(arr2.data(), arr2.size());
				}
				std::string result = GetFileContent("test_files/compress_two_diffrent_sequences.bin");
				BOOST_CHECK_EQUAL(result, "\x32\x30\x14\x32");
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(when_block_contains_different_bytes)
			BOOST_AUTO_TEST_CASE(should_divide_these_to_different_packs)
			{
				{
					auto stream = std::make_unique<CFileOutputStream>("test_files/compress_two_diffrent_sequences.bin");
					auto compressedStream = std::make_unique<COutputStreamCompressor>(std::move(stream));
					std::array<uint8_t, 5> arr = { 1, 2, 3, 4, 5 };
					compressedStream->WriteBlock(arr.data(), arr.size());
				}
				std::string result = GetFileContent("test_files/compress_two_diffrent_sequences.bin");
				BOOST_CHECK_EQUAL(result, "\x1\x1\x1\x2\x1\x3\x1\x4\x1\x5");
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

struct EmptyMemoryData
{
	std::vector<uint8_t> data;
};

struct EmptyOuptutMemoryStream : EmptyMemoryData
{
	std::unique_ptr<CMemoryOutputStream> stream;
	EmptyOuptutMemoryStream()
		: stream(std::make_unique<CMemoryOutputStream>(data))
	{
	}
};

void CheckRLEPacket(uint8_t amount, uint8_t byte, uint8_t expectedAmount, uint8_t expectedByte)
{
	BOOST_CHECK(amount == expectedAmount);
	BOOST_CHECK(byte == expectedByte);
}

BOOST_FIXTURE_TEST_SUITE(Test_memory_input_stream, EmptyOuptutMemoryStream)
	BOOST_AUTO_TEST_SUITE(Test_write_byte)
		BOOST_AUTO_TEST_CASE(compress_0_bytes)
		{
			auto compressedStream = std::make_unique<COutputStreamCompressor>(std::move(stream));
			BOOST_CHECK(data.empty());
		}
		BOOST_AUTO_TEST_CASE(compress_1_bytes)
		{
			{
				auto compressedStream = std::make_unique<COutputStreamCompressor>(std::move(stream));
				compressedStream->WriteByte(48);
			}
			CheckRLEPacket(1, 48, data[0], data[1]);
		}
		BOOST_AUTO_TEST_CASE(can_compress_50_identical_bytes)
		{	
			{
				auto compressedStream = std::make_unique<COutputStreamCompressor>(std::move(stream));
				WriteRepeatedByte(50, 48, compressedStream);
			}
			CheckRLEPacket(50, 48, data[0], data[1]);
		}
		BOOST_AUTO_TEST_SUITE(when_gives_255_bytes)
			BOOST_AUTO_TEST_CASE(should_compress_255_bytes)
			{	
				{
					auto compressedStream = std::make_unique<COutputStreamCompressor>(std::move(stream));
					WriteRepeatedByte(255, 48, compressedStream);
				}
				CheckRLEPacket(255, 48, data[0], data[1]);
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(when_gives_greater_than_255_bytes)
			BOOST_AUTO_TEST_CASE(should_separate_bytes_to_differents_packages)
			{
				{
					auto compressedStream = std::make_unique<COutputStreamCompressor>(std::move(stream));
					WriteRepeatedByte(509, 48, compressedStream);
				}
				CheckRLEPacket(255, 48, data[0], data[1]);
				CheckRLEPacket(254, 48, data[2], data[3]);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
