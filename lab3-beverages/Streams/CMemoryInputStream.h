#pragma once
#include "IInputStream.h"

class CMemoryInputStream : public IInputStream
{
public:
	CMemoryInputStream(std::vector<uint8_t>& data)
		: m_memoryStream(data)
	{
	}

	bool IsEOF() const
	{
		return m_memoryStream.size() == m_pos;
	}

	uint8_t ReadByte() override
	{
		if (IsEOF() || m_pos > m_memoryStream.size())
		{
			throw std::ios_base::failure("Cannot read byte. Reached end of stream");
		}

		return m_memoryStream.at(m_pos++);
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		if (static_cast<std::size_t>(size) > m_memoryStream.size() - m_pos)
		{
			size = m_memoryStream.size() - m_pos;
		}
		uint8_t* bytesBuffer = static_cast<uint8_t*>(dstBuffer);
		for (std::streamsize i = 0; i < size; i++)
		{
			*(bytesBuffer++) = ReadByte();
		}
		return size;
	}

private:
	std::vector<uint8_t> &m_memoryStream;
	size_t m_pos = 0;
};
