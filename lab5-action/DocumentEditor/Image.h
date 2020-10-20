#pragma once
#include "IImage.h"
#include "IDocument.h"
#include "History.h"
#include "ICommandSink.h"

class CImage: public IImage
{
public:
	CImage(const Path& path, int width, int height, ICommandSinkPtr && command);
	~CImage();
	std::string GetPath() const;
	int GetWidth() const;
	int GetHeight() const;
	void Resize(int width, int height);

private:
	static bool IsCorrectImageSize(int height, int width);
	ICommandSinkPtr m_commandSink;
	int m_height;
	int m_width;
	std::string m_path;
};