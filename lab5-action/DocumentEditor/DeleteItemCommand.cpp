#include "DeleteItemCommand.h"

CDeleteItemCommand::CDeleteItemCommand(std::vector<DocumentItemPtr>& documentItems, size_t position)
	: m_items(documentItems)
	, m_position(position)
{
}

void CDeleteItemCommand::DoExecute()
{
	if (m_position >= m_items.size())
	{
		throw std::runtime_error("Out of range position. Can't delete.");
	}
	auto itemIt = m_items.begin() + m_position;
	m_deletedItem = *itemIt;
	m_items.erase(itemIt);
}

void CDeleteItemCommand::DoUnexecute()
{
	if (m_position >= m_items.size())
	{
		m_items.push_back(m_deletedItem);
	}
	else
	{
		m_items.insert(m_items.begin() + m_position, m_deletedItem);
	}
}
