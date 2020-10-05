#include "stdafx.h"
#include "../Streams/CFileOutputStream.h"
#include "../Streams/CFileInputStream.h"
#include "TestsUtils.h"

const std::string FILE_NAME = "test_files/output_stream_test.bin";

BOOST_AUTO_TEST_SUITE(Test_output_file_stream)
	BOOST_AUTO_TEST_CASE(can_write_byte_to_stream)
	{
		{
			CFileOutputStream stream(FILE_NAME);
			stream.WriteByte(48);
			stream.WriteByte(49);
		}
		std::string res = GetFileContent(FILE_NAME);
		BOOST_CHECK_EQUAL(res, "01");
	}
	BOOST_AUTO_TEST_CASE(can_write_block_of_bytes_to_stream)
	{
		{
			CFileOutputStream stream(FILE_NAME);
			std::array<uint8_t, 4> arr = { 48, 49, 50, 51 };
			stream.WriteBlock(arr.data(), arr.size());
		}
		std::string result = GetFileContent(FILE_NAME);
		BOOST_CHECK_EQUAL(result, "0123");
	}
BOOST_AUTO_TEST_SUITE_END()

