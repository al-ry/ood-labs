#include "stdafx.h"
#include "HtmlConverter.h"
#include <boost/algorithm/string/replace.hpp>
const std::string IMAGES_DIRECTORY = "images";

const std::map<std::string, std::string> HTML_SYMBOLS = {
	{ "<", "&lt;" },
	{ ">", "&gt;" },
	{ "'", "&apos;" },
	{ "&", "&amp;" },
	{ "\"", "&quot;" },
};

CHtmlConverter::CHtmlConverter(const IDocument& document)
	: m_document(document)
{
}

void CHtmlConverter::Save(const Path& storePath)
{
	if (storePath.empty())
	{
		throw std::runtime_error("Path cannot be empty");
	}

	std::ofstream file(storePath.generic_string());
	if (!file.is_open())
	{
		throw std::runtime_error("Cannot opern file: " + storePath.generic_string());
	}

	 file << "<!DOCTYPE html>\n<html>\n<head>\n\t<title>"
		 << CreateTitle(m_document.GetTitle())
		 << "</title>\n</head>\n"
		 << "<body>\n"
		 << CreateBody(storePath) << "</body>\n</html>";
}

std::string CHtmlConverter::EncodeHtmlSymbols(std::string &str)
{
	for (auto symbol: HTML_SYMBOLS)
	{
		boost::replace_all(str, symbol.first, symbol.second);
	}

	return std::string(str);
}

std::string CHtmlConverter::CreateBody(const Path& path)
{
	std::string body;
	for (size_t i = 0; i < m_document.GetItemsCount(); i++)
	{
		auto item = m_document.GetItem(i);
		if (item.GetParagraph())
		{
			body += CreateParagraph(item.GetParagraph()->GetText());
		}
		else if (item.GetImage())
		{
			body += CreateImage(item.GetImage(), path);
		}
	}
	return body;
}

std::string CHtmlConverter::CreateTitle(const std::string& title)
{
	std::string cpyStr = title;
	return EncodeHtmlSymbols(cpyStr);
}

std::string CHtmlConverter::CreateParagraph(const std::string& paragraph)
{
	std::string cpyParagraph = paragraph;
	return "\t<p>" + EncodeHtmlSymbols(cpyParagraph) + "</p>\n";
}

std::string CHtmlConverter::CreateImage(const IImageConstPtr& image, const Path& path)
{
	auto imgPath = Path(IMAGES_DIRECTORY);
	auto relativePath = imgPath / Path(image->GetPath()).filename();
	std::filesystem::create_directories(path.parent_path() / imgPath);
	std::filesystem::copy_file(image->GetPath(), path.parent_path() / relativePath, std::filesystem::copy_options::update_existing);
	std::string relativePathStr = relativePath.generic_string();
	return "\t<img src='" + EncodeHtmlSymbols(relativePathStr) + "' height=" + std::to_string(image->GetHeight()) + " width=" + std::to_string(image->GetWidth()) + ">\n";
}
