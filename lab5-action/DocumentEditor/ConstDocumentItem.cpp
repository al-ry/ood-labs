#include "stdafx.h"
#include "ConstDocumentItem.h"

CConstDocumentItem::CConstDocumentItem(const IParagraphPtr& paragraph)
	: m_paragraph(paragraph)
{
}

CConstDocumentItem::CConstDocumentItem(const IImagePtr& image)
	: m_image(image)
{
}

std::shared_ptr<const IImage> CConstDocumentItem::GetImage() const
{
	return m_image;
}

std::shared_ptr<const IParagraph> CConstDocumentItem::GetParagraph() const
{
	return m_paragraph;
}