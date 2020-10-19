#include "stdafx.h"
#include "DocumentItem.h"


CDocumentItem::CDocumentItem(const IParagraphPtr& paragraph)
	: CConstDocumentItem(paragraph)
{
}

CDocumentItem::CDocumentItem(const IImagePtr& image)
	: CConstDocumentItem(image)
{
}

std::shared_ptr<IParagraph> CDocumentItem::GetParagraph()
{
	return m_paragraph;
}

std::shared_ptr<IImage> CDocumentItem::GetImage()
{
	return m_image;
}
