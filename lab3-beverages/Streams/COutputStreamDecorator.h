#pragma once
#include "IOutputStream.h"

class COutputStreamDecorator : public IOutputStream
{
protected:
	COutputStreamDecorator(IOutputStreamPtr&& stream)
		: m_stream(std::move(stream))
	{
	} 

	IOutputStreamPtr m_stream;
};
