#include "stdafx.h"
#include "Document.h"
#include "ChangeStringCommand.h"
#include "Paragraph.h"
#include "Image.h"
#include "InsertItemCommand.h"
#include "DeleteItemCommand.h"
#include "HtmlConverter.h"

std::shared_ptr<IParagraph> CDocument::InsertParagraph(const std::string& text, optional<size_t> position)
{
	auto paragraph = std::make_shared<CParagraph>(text, m_history);
	auto docItem = std::make_shared<CDocumentItem>(paragraph);
	m_history.AddAndExecuteCommand(std::make_unique<CInsertItemCommand>(m_documentItems, docItem, position));
	return paragraph;
}

std::shared_ptr<IImage> CDocument::InsertImage(const Path& path, int width, int height, optional<size_t> position)
{
	auto image = std::make_shared<CImage>(path, width, height, m_history);
	auto docItem = std::make_shared<CDocumentItem>(image);
	m_history.AddAndExecuteCommand(std::make_unique<CInsertItemCommand>(m_documentItems, docItem, position));
	return image;
}

size_t CDocument::GetItemsCount() const
{
	return m_documentItems.size();
}

CConstDocumentItem CDocument::GetItem(size_t index) const
{
	if (index >= m_documentItems.size())
	{
		throw std::runtime_error("Index out of range");
	}
	CConstDocumentItem itemCpy = *m_documentItems.at(index).get();
	return itemCpy;
}

CDocumentItem CDocument::GetItem(size_t index)
{
	if (index >= m_documentItems.size())
	{
		throw std::runtime_error("Index out of range");
	}
	CDocumentItem itemCpy = *m_documentItems.at(index).get();
	return itemCpy;
}

void CDocument::DeleteItem(size_t index)
{
	m_history.AddAndExecuteCommand(std::make_unique<CDeleteItemCommand>(m_documentItems, index));
}

std::string CDocument::GetTitle() const
{
	return m_title;
}

void CDocument::SetTitle(const std::string& title)
{
	m_history.AddAndExecuteCommand(std::make_unique<CChangeStringCommand>(m_title, title));
}

bool CDocument::CanUndo() const
{
	return m_history.CanUndo();
}

void CDocument::Undo()
{
	m_history.Undo();
}

bool CDocument::CanRedo() const
{
	return m_history.CanRedo();
}

void CDocument::Redo()
{
	m_history.Redo();
}

void CDocument::Save(const Path& path) const
{
	CHtmlConverter converter(*this);
	converter.Save(path);
}
