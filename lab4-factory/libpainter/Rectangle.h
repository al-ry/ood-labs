#pragma once
#include "Color.h"
#include "Shape.h"
#include "Point.h"

class CRectangle : public CShape
{
public:
	CRectangle(Color color, const CPoint& leftTop, double width, double height)
		: CShape(color)
		, m_leftTop(leftTop)
		, m_width(width)
		, m_height(height)
	{
	}

	CPoint GetLeftTop() const
	{
		return m_leftTop;
	}
	CPoint GetRightBottom() const
	{
		return CPoint(m_leftTop.x + m_width, m_leftTop.y - m_height);
	}
	void Draw(ICanvas& canvas) const override
	{
		canvas.SetColor(GetColor());
		CPoint rightTop = { GetLeftTop().x + m_width, GetLeftTop().y };
		CPoint leftBottom = { GetLeftTop().x, GetLeftTop().y - m_height };
		canvas.DrawLine(GetLeftTop(), rightTop);
		canvas.DrawLine(rightTop, GetRightBottom());
		canvas.DrawLine(GetRightBottom(), leftBottom);
		canvas.DrawLine(leftBottom, GetLeftTop());
	}

private:
	CPoint m_leftTop;
	double m_width;
	double m_height;
};
