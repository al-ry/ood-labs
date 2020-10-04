#pragma once
#include "stdafx.h"
#include "CInputStreamDecorator.h"
#include "CEncodingByteTable.h"

class CDecryptedInputStream : public CInputStreamDecorator
{
public: 
	CDecryptedInputStream(IInputStreamPtr&& stream, uint32_t key)
		: CInputStreamDecorator(std::move(stream))
		, m_encodingTable(key)
	{
	}
	uint8_t ReadByte()
	{
		return m_encodingTable.GetDecrytedByte(m_stream->ReadByte());
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size)
	{
		std::streamsize encryptedBytesSize = m_stream->ReadBlock(dstBuffer, size);
		uint8_t* buffer = static_cast<uint8_t*>(dstBuffer);
		for (size_t i = 0; i < encryptedBytesSize; i++)
		{
			buffer[i] = m_encodingTable.GetDecrytedByte(buffer[i]);
		}
		return encryptedBytesSize;
	}

private:
	CEncodingByteTable m_encodingTable;
};