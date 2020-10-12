#pragma once
#include "stdafx.h"
#include "../libpainter/Designer.h"
#include "../libpainter/PictureDraft.h"
#include "Shape.h"

class CPainter
{
public:
	CPainter() = default;
	void DrawPicture(const CPictureDraft& draft, ICanvas& canvas) const
	{
		for (auto it = draft.begin(); it != draft.end(); it++)
		{
			const CShape& shape = *it;
			shape.Draw(canvas);
		}
	}
};
