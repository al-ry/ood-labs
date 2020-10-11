#pragma once
#include "stdafx.h"
#include "../libpainter/Designer.h"
#include "IPainter.h"

class CPainter : public IPainter
{
public:
	CPainter() = default;
	void DrawPicture(const CPictureDraft& draft, ICanvas& canvas) const override
	{
		for (auto it = draft.begin(); it != draft.end(); it++)
		{
			const CShape& shape = *it;
			shape.Draw(canvas);
		}
	}
};
