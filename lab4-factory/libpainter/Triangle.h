#pragma once
#include "Shape.h"
#include "Point.h"

class CTriangle : public CShape
{
public:
	CTriangle(Color color, CPoint vertex1, CPoint vertex2, CPoint vertex3)
		: CShape(color)
		, m_vertex1(vertex1)
		, m_vertex2(vertex2)
		, m_vertex3(vertex3)
	{
	}

	CPoint GetVertex1()const
	{
		return m_vertex1;
	}
	CPoint GetVertex2()const
	{
		return m_vertex2;
	}
	CPoint GetVertex3()const
	{
		return m_vertex3;
	}
	void Draw(ICanvas& canvas) const override
	{
		canvas.SetColor(GetColor());
		canvas.DrawLine(GetVertex1(), GetVertex2());
		canvas.DrawLine(GetVertex2(), GetVertex3());
		canvas.DrawLine(GetVertex3(), GetVertex1());
	}

private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
};