#include "ResizeCommand.h"

CResizeCommand::CResizeCommand(int& targetHeight, int& targetWidth, int newHeight, int newWidth)
	: m_newHeight(newHeight)
	, m_newWidth(newWidth)
	, m_targetHeight(targetHeight)
	, m_targetWidth(targetWidth)
{
}

void CResizeCommand::DoExecute()
{
	std::swap(m_targetHeight, m_newHeight);
	std::swap(m_targetWidth, m_newWidth);
}

void CResizeCommand::DoUnexecute()
{
	std::swap(m_targetHeight, m_newHeight);
	std::swap(m_targetWidth, m_newWidth);
}
