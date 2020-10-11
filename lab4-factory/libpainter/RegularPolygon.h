#pragma once
#include "stdafx.h"
#include "Shape.h"
#include "Point.h"


class CRegularPolygon : public CShape
{
public:
	CRegularPolygon(Color color, CPoint center, double radius, int vertexCount)
		: CShape(color)
		, m_center(center)
		, m_radius(radius)
		, m_vertexCount(vertexCount)
	{
	}

	CPoint GetCenter() const
	{
		return m_center;
	}
	double GetRadius() const
	{
		return m_radius;
	}
	int GetVertexCount() const
	{
		return m_vertexCount;
	}
	void Draw(ICanvas& canvas) const override
	{
		canvas.SetColor(GetColor());
		double angle = 2 * M_PI / m_vertexCount;
		std::vector<CPoint> vertices;
		for (int i = 0; i < m_vertexCount; i++)
		{
			vertices.push_back(CPoint(m_center.x + m_radius * cos(angle * i), m_center.y + m_radius * sin(angle * i)));
		}
		for (size_t i = 0; i < vertices.size() - 1; i++)
		{
			canvas.DrawLine(vertices[i], vertices[i + 1]);
		}
		canvas.DrawLine(vertices[vertices.size() - 1], vertices[0]);
	}

private:
	int m_vertexCount;
	double m_radius;
	CPoint m_center;
};