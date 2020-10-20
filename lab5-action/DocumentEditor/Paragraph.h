#pragma once 
#include "IParagraph.h"
#include "History.h"
#include "ICommandSink.h"

class CParagraph: public IParagraph
{
public: 
	CParagraph(const std::string& text, ICommandSinkPtr&& command);
	std::string GetText() const override;
	void SetText(const std::string& text) override;

private:
	std::string m_text;
	ICommandSinkPtr m_commandSink;
};