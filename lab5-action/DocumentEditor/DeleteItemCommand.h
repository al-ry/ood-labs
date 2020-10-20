#pragma once
#include "AbstractCommand.h"
#include <vector>
#include "DocumentItem.h"


class CDeleteItemCommand: public CAbstractCommand
{
public:
	CDeleteItemCommand(std::vector<DocumentItemPtr>& documentItems, size_t position);

protected:
	void DoExecute();
	void DoUnexecute();

private:
	std::vector<DocumentItemPtr>& m_items;
	size_t m_position;
	DocumentItemPtr m_deletedItem;
};