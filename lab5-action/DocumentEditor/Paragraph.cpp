#include "Paragraph.h"
#include "ChangeStringCommand.h"
CParagraph::CParagraph(const std::string& text, CHistory& history)
	: m_text(text)
	, m_history(history)
{
}

std::string CParagraph::GetText() const
{
	return m_text;
}

void CParagraph::SetText(const std::string& text)
{
	m_history.AddAndExecuteCommand(std::make_unique<CChangeStringCommand>(m_text, text));
}
