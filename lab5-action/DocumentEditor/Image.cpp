#include "stdafx.h"
#include "Image.h"
#include "ResizeCommand.h"

const int MAX_IMAGE_SIZE = 10000;
const int MIN_IMAGE_SIZE = 1;
const int MAX_FILE_NAME_SIZE = 15;


bool CImage::IsCorrectImageSize(int height, int width)
{
	return (height < MIN_IMAGE_SIZE || width < MIN_IMAGE_SIZE || width > MAX_IMAGE_SIZE || height > MAX_IMAGE_SIZE);
}

CImage::CImage(const Path& path, int width, int height, CHistory& history)
	: m_history(history)
{
	if (IsCorrectImageSize(height, width))
	{
		throw std::runtime_error("Image size should be in range of [1; 100000].");
	} 
	m_height = height;
	m_width = width;

	if (!exists(path))
	{
		throw std::runtime_error("Path to file doesn't exist");
	}
	std::string tempFilePathStr = std::tmpnam(nullptr);
	tempFilePathStr += path.extension().generic_string();
	copy_file(path, tempFilePathStr);
	m_path = tempFilePathStr;
}

CImage::~CImage()
{
	std::filesystem::remove(m_path);
}

std::string CImage::GetPath() const
{
	return m_path;
}

int CImage::GetWidth() const
{
	return m_width;
}

int CImage::GetHeight() const
{
	return m_height;
}

void CImage::Resize(int width, int height)
{
	m_history.AddAndExecuteCommand(std::make_unique<CResizeCommand>(m_height, m_width, height, width));
}

