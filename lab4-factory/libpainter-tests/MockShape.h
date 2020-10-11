#pragma once
#include "stdafx.h"
#include "../libpainter/Designer.h"
#include "../libpainter/PictureDraft.h"
#include "../libpainter/IShapeFactory.h"

class CMockShape : public CShape
{
public:
	CMockShape(const std::string& descr)
		: descr(descr)
		, CShape(Color::Black)
	{
	}
	void Draw(ICanvas& canvas) const override
	{
		canvas.SetColor(Color::Red);
		canvas.DrawLine(CPoint(), CPoint());
	}
	std::string descr;
};