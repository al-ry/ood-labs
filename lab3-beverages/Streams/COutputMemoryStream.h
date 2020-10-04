#pragma once
#include "IOutputStream.h"

class COutputMemoryStream: public IOutputStream
{
public:
	COutputMemoryStream(std::vector<uint8_t>& stream)
		: m_stream(stream)
	{
	}
	void WriteByte(uint8_t data) override
	{
		try
		{
			m_stream.push_back(data);
		}
		catch (std::exception&)
		{
			throw std::ios_base::failure("Cannot write byte");
		}
	}
	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		const uint8_t* buffer = static_cast<const uint8_t*>(srcData);
		for (size_t i = 0; i < size; i++)
		{
			try
			{
				WriteByte(buffer[i]);
			}
			catch (std::exception&)
			{
				throw std::ios_base::failure("Cannot write block of bytes");
			}
		}		
	}
private:
	std::vector<uint8_t>& m_stream;
};