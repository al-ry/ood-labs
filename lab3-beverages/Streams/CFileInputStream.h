#pragma once
#include "stdafx.h"
#include "IInputStream.h"

class CFileInputStream : public IInputStream
{
public:
	CFileInputStream(const std::string& fileName)
	{
		m_inputFileStream.open(fileName, std::ios::binary);
		if (!m_inputFileStream.is_open())
		{
			throw std::ios::failure("Cannot open file: " + fileName);
		}
	}

	bool IsEOF()const override
	{
		return m_inputFileStream.eof();
	}

	uint8_t ReadByte() override
	{
		char readByte;
		m_inputFileStream.read(&readByte, 1);
		if (IsEOF())
		{
			throw std::ios_base::failure("Cannot read byte. Reached end of stream");
		}
		return (uint8_t)readByte;		
	}
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		if (!m_inputFileStream.read(static_cast<char*>(dstBuffer), size))
		{
			throw std::ios_base::failure("Cannot read block");
		}
		return size;
	}

private:
	std::ifstream m_inputFileStream;
};