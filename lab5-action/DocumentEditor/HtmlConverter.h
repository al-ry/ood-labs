#pragma once
#include "Document.h"



class CHtmlConverter
{
public:
	CHtmlConverter(const IDocument& document);
	void Save(const Path& storePath);

private:

	static std::string EncodeHtmlSymbols(std::string &str);

	std::string CreateBody(const Path& path);
	std::string CreateTitle(const std::string& title);
	std::string CreateParagraph(const std::string& paragraph);
	std::string CreateImage(const IImageConstPtr& image, const Path& path);

	const IDocument& m_document;
};