#pragma once
#include "Shape.h"
#include "Point.h"

class CEllipse : public CShape
{
public:
	CEllipse(Color color, CPoint center, double verticalRadius, double horizontalRadius)
		: CShape(color)
		, m_center(center)
		, m_verticalRadius(verticalRadius)
		, m_horizontalRadius(horizontalRadius)
	{
	}

	CPoint GetCenter() const
	{
		return m_center;
	}
	double GetVecticalRadius() const
	{
		return m_verticalRadius;
	}
	double GetHorizontalRadius() const
	{
		return m_horizontalRadius;
	}

	void Draw(ICanvas& canvas) const override
	{
		canvas.SetColor(GetColor());
		canvas.DrawEllipse(GetCenter(), GetVecticalRadius(), GetHorizontalRadius());
	}

private:
	double m_verticalRadius;
	double m_horizontalRadius;
	CPoint m_center;
};