#pragma once
#include "stdafx.h"


class IOutputStream
{
public: 
	virtual void WriteByte(uint8_t data) = 0;
	virtual void WriteBlock(const void* srcData, std::streamsize size) = 0;

	virtual ~IOutputStream() = default;
};

typedef std::unique_ptr<IOutputStream> IOutputStreamPtr;