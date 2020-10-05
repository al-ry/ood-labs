#include "stdafx.h"
#include "../Streams/CMemoryInputStream.h"
#include "../Streams/CMemoryOutputStream.h"
#include "../Streams/CEncryptedOutputStream.h"
#include "../Streams/CDecryptedInputStream.h"


std::unique_ptr<CEncryptedOutputStream> MakeOutputEncryptedDecorator(std::vector<uint8_t> &data, uint32_t key)
{
	auto stream = std::make_unique<CMemoryOutputStream>(data);
	auto decodingStream = std::make_unique<CEncryptedOutputStream>(std::move(stream), key);
	return decodingStream;
}

std::unique_ptr<CDecryptedInputStream> MakeInputDecryptedDecorator(std::vector<uint8_t> &data, uint32_t key)
{
	auto stream = std::make_unique<CMemoryInputStream>(data);
	auto decodingStream = std::make_unique<CDecryptedInputStream>(std::move(stream), key);
	return decodingStream;
}

BOOST_AUTO_TEST_SUITE(Test_encoding_decorator)
	BOOST_AUTO_TEST_CASE(can_encode_and_decode_stream_by_one_byte)
	{
		std::vector<uint8_t> vec = {};
		auto encodingStream = MakeOutputEncryptedDecorator(vec, 2020);
		encodingStream->WriteByte('Z');
		encodingStream->WriteByte('0');
		encodingStream->WriteByte('f');
		encodingStream->WriteByte('A');

		BOOST_CHECK(vec[0] != 'Z');
		BOOST_CHECK(vec[1] != '0');
		BOOST_CHECK(vec[2] != 'f');
		BOOST_CHECK(vec[3] != 'A');

		auto decodingStream = MakeInputDecryptedDecorator(vec, 2020);
		BOOST_CHECK(decodingStream->ReadByte() == 'Z');
		BOOST_CHECK(decodingStream->ReadByte() == '0');
		BOOST_CHECK(decodingStream->ReadByte() == 'f');
		BOOST_CHECK(decodingStream->ReadByte() == 'A');
	}
	BOOST_AUTO_TEST_CASE(can_encode_and_decode_stream_block_of_bytes)
	{
		std::vector<uint8_t> vec = {};
		auto encodingStream = MakeOutputEncryptedDecorator(vec, 2020);
		std::array<uint8_t, 5> block = { 'A', '9', 'd', ' ', '~' };
		encodingStream->WriteBlock(block.data(), block.size());

		auto decodingStream = MakeInputDecryptedDecorator(vec, 2020);
		std::array<uint8_t, 5> result;
		decodingStream->ReadBlock(result.data(), result.size());
		BOOST_CHECK(result[0] == 'A');
		BOOST_CHECK(result[1] == '9');
		BOOST_CHECK(result[2] == 'd');
		BOOST_CHECK(result[3] == ' ');
		BOOST_CHECK(result[4] == '~');
	}

BOOST_AUTO_TEST_SUITE_END()