#pragma once
#include "AbstractCommand.h"
#include "DocumentItem.h"
#include <vector>
#include "History.h"
#include <boost\optional\optional.hpp>

class CInsertItemCommand : public CAbstractCommand
{
public:
	CInsertItemCommand(std::vector<DocumentItemPtr>& documentItems, const DocumentItemPtr item, const boost::optional<size_t>& position);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::vector<DocumentItemPtr>& m_items;
	DocumentItemPtr m_item;
	boost::optional<size_t> m_position;
};