#include "Paragraph.h"
#include "ChangeStringCommand.h"
CParagraph::CParagraph(const std::string& text, ICommandSinkPtr&& command)
	: m_text(text)
	, m_commandSink(std::move(command))
{
}

std::string CParagraph::GetText() const
{
	return m_text;
}

void CParagraph::SetText(const std::string& text)
{
	m_commandSink->AddCommand(std::make_unique<CChangeStringCommand>(m_text, text));
}
