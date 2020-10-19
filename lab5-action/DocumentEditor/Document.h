#pragma once
#include "IDocument.h"
#include "History.h"


class CDocument: public IDocument
{
public:
	std::shared_ptr<IParagraph> InsertParagraph(const std::string& text,
		optional<size_t> position = none) override;


	std::shared_ptr<IImage> InsertImage(const Path& path, int width, int height,
		optional<size_t> position = none) override;

	size_t GetItemsCount() const override;

	CConstDocumentItem GetItem(size_t index) const override;
	CDocumentItem GetItem(size_t index) override;

	void DeleteItem(size_t index) override;

	std::string GetTitle() const;
	void SetTitle(const std::string& title) override;

	
	bool CanUndo() const override;

	void Undo() override;

	bool CanRedo() const override;
	void Redo() override;

	void Save(const Path& path) const override;

public: 
	std::string m_title;
	std::vector<DocumentItemPtr> m_documentItems;
	CHistory m_history;
};