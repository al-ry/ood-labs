#pragma once
#include "IParagraph.h"
#include "IImage.h"

class CConstDocumentItem
{
public:
	CConstDocumentItem(const IParagraphPtr& paragraph);
	CConstDocumentItem(const IImagePtr& image);
	// ���������� ��������� �� ����������� �����������, ���� nullptr,
	// ���� ������� �� �������� ������������
	std::shared_ptr<const IImage> GetImage() const;
	// ���������� ��������� �� ����������� ��������, ���� nullptr, ���� ������� �� �������� ����������
	std::shared_ptr<const IParagraph> GetParagraph() const;
	virtual ~CConstDocumentItem() = default;

protected:
	IImagePtr m_image;
	IParagraphPtr m_paragraph;
};



