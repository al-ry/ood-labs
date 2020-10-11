#pragma once
#include "Color.h"
#include "ICanvas.h"
class CShape
{
public:
	CShape(Color color);

	Color GetColor() const;
	virtual void Draw(ICanvas& canvas)const = 0;
	virtual ~CShape();

private:
	Color m_color;
};

