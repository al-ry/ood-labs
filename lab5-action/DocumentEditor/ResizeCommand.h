#pragma once
#include "AbstractCommand.h"
#include <string>

class CResizeCommand : public CAbstractCommand
{
public: 
	CResizeCommand(int& targetHeight, int& targetWidth,
		int newHeight, int newWidth);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	int m_newHeight;
	int& m_targetHeight;
	int m_newWidth;
	int& m_targetWidth;
};