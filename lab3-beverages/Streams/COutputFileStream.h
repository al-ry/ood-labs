#pragma once
#include "IOutputStream.h"

class COutputFileStream: public IOutputStream
{
public:
	COutputFileStream(const std::string& fileName)
	{
		m_stream.open(fileName, std::ios::binary);
		if(!m_stream.is_open())
		{
			throw std::ios::failure("Cannot open file: " + fileName);
		}
	}
	void WriteByte(uint8_t data) override
	{
		char byte = static_cast<uint8_t>(data);
		if (!m_stream.write(&byte, 1))
		{
			throw std::ios_base::failure("Cannot write byte.");
		}
	}
	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		const char* block = static_cast<const char*>(srcData);
		if (!m_stream.write(block, size))
		{
			throw std::ios_base::failure("Cannot write block.");
		}
		m_stream.flush();
	}

private:
	std::ofstream m_stream;
};