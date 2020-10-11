#pragma once
#include "stdafx.h"
#include "IOutputStream.h"
#include "COutputStreamDecorator.h"
#include "CEncodingByteTable.h"



class CEncryptedOutputStream : public COutputStreamDecorator
{
public:
	CEncryptedOutputStream(IOutputStreamPtr&& stream, uint32_t key)
		: COutputStreamDecorator(std::move(stream))
		, m_encodingTable(key)
	{

	}

	void WriteByte(uint8_t data) override
	{
		m_stream->WriteByte(m_encodingTable.GetEncrytedByte(data));
	}
	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		const uint8_t* block = static_cast<const uint8_t*>(srcData);
		for (std::streamsize i = 0; i < size; i++)
		{
			WriteByte(block[i]);
		}
	}
private:
	CEncodingByteTable m_encodingTable;
};

