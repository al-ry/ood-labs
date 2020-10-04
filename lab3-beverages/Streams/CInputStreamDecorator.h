#pragma once
#include "IInputStream.h"



class CInputStreamDecorator : public IInputStream
{
public:
	bool IsEOF() const override
	{
		return m_stream->IsEOF();
	}
protected:
	CInputStreamDecorator(IInputStreamPtr&& stream)
		: m_stream(std::move(stream))
	{
	}

	IInputStreamPtr m_stream;
};