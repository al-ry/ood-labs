#include "stdafx.h"
#include "../Streams/CMemoryOutputStream.h"

struct EmptyMemoryData
{
	std::vector<uint8_t> bytes;
};

struct EmptyMemoryOutputStream: EmptyMemoryData
{
	CMemoryOutputStream stream;
	EmptyMemoryOutputStream()
		: stream(bytes)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Test_memory_output_stream, EmptyMemoryOutputStream)
	BOOST_AUTO_TEST_SUITE(when_output_stream_data_empty)
		BOOST_AUTO_TEST_CASE(can_write_byte)
		{
			stream.WriteByte(48);
			stream.WriteByte(49);
			BOOST_CHECK(bytes.at(0) == 48);
			BOOST_CHECK(bytes.at(1) == 49);
		}
		BOOST_AUTO_TEST_CASE(can_write_block_of_bytes)
		{
			std::array<uint8_t, 5> arr = { 0, 1, 2, 3, 4 };
			stream.WriteBlock(arr.data(), arr.size());
			for (std::size_t i = 0; i < arr.size(); i++)
			{
				BOOST_CHECK(bytes.at((size_t)i) == i);
			}
		}
		BOOST_AUTO_TEST_SUITE(when_parametr_is_simple_array)
			BOOST_AUTO_TEST_CASE(can_write_block_of_bytes)
			{
				uint8_t arr[5] = {0, 1, 2, 3, 4};
				stream.WriteBlock(arr, 5);
				for (std::streamsize i = 0; i < 5; i++)
				{
					BOOST_CHECK_EQUAL(bytes.at((size_t)i), i);
				}
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()