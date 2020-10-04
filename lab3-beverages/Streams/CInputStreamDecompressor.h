#pragma once
#include "CInputStreamDecorator.h"
#include "RLEPacket.h"

class CInputStreamDecompressor : public CInputStreamDecorator
{
public:
	CInputStreamDecompressor(IInputStreamPtr&& stream)
		: CInputStreamDecorator(std::move(stream))
	{
	}
	uint8_t ReadByte() override
	{
		if (m_packet.bytesCounter == 0)
		{
			m_packet.bytesCounter = m_stream->ReadByte();
			try
			{
				m_packet.dataByte = m_stream->ReadByte();
			}
			catch (std::ios_base::failure&)
			{
				throw std::logic_error("File size should be even so that can decompress data");
			}
		}
		m_packet.bytesCounter--;
		return m_packet.dataByte;
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		uint8_t* buffer = static_cast<uint8_t*>(dstBuffer);
		for (std::streamsize i = 0; i < size; i++)
		{
			try
			{
				buffer[i] = ReadByte();
			}
			catch (std::logic_error& e)
			{
				std::cout << e.what();
				throw e;
			}
			catch (std::ios_base::failure&)
			{
				return i;
			}
		}
		return size;
	}

private:
	Packet m_packet;
	std::vector<uint8_t> decompressedData;
};