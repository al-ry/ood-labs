#include "InsertItemCommand.h"


CInsertItemCommand::CInsertItemCommand(std::vector<DocumentItemPtr>& documentItems, const DocumentItemPtr item, const boost::optional<size_t>& position)
	: m_items(documentItems)
	, m_item(item)
	, m_position(position)
{
}

void CInsertItemCommand::DoExecute()
{
	if (m_position.has_value() && m_position > m_items.size())
	{
		throw std::runtime_error("Out of range index specified. Can't execute command");
	}
	else if (!m_position.has_value())
	{
		m_items.push_back(m_item);
	}
	else
	{
		m_items.insert(m_items.begin() + *m_position, m_item);
	}

}

void CInsertItemCommand::DoUnexecute()
{
	assert(m_items.size() > 0);
	if (m_position.has_value() && m_position > m_items.size())
	{
		throw std::runtime_error("Out of range index specified. Can't unexecute command");
	}
	else if (!m_position.has_value())
	{
		m_items.pop_back();
	}
	else
	{
		m_items.erase(m_items.begin() + *m_position);
	}
}
