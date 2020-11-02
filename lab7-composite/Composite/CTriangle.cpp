#include "CTriangle.h"
#include <algorithm>
CTriangle::CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
}

RectD CTriangle::GetFrame() const
{
	double minX = std::min({ m_vertex1.x, m_vertex2.x, m_vertex3.x });
	double maxX = std::max({ m_vertex1.x, m_vertex2.x, m_vertex3.x });

	double minY = std::min({ m_vertex1.y, m_vertex2.y, m_vertex3.y });
	double maxY = std::max({ m_vertex1.y, m_vertex2.y, m_vertex3.y });

	return RectD({minX, minY, maxX - minX, maxY - minY});
}

void CTriangle::SetFrame(const RectD& frame)
{
	auto oldFrame = GetFrame();
	RecalculatePointPosition(m_vertex1, frame, oldFrame);
	RecalculatePointPosition(m_vertex2, frame, oldFrame);
	RecalculatePointPosition(m_vertex3, frame, oldFrame);
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

void CTriangle::FillShape(ICanvas& canvas) const
{
	std::vector<CPoint> triangleVertices = {
		GetVertex1(),
		GetVertex2(),
		GetVertex3()
	};
	canvas.FillConvexPolygon(triangleVertices);
}

void CTriangle::CircleShape(ICanvas& canvas) const
{
	std::vector<CPoint> triangleVertices = {
		GetVertex1(),
		GetVertex2(),
		GetVertex3()
	};
	canvas.DrawLine(GetVertex1(), GetVertex2());
	canvas.DrawLine(GetVertex2(), GetVertex3());
	canvas.DrawLine(GetVertex3(), GetVertex1());
}


void CTriangle::RecalculatePointPosition(CPoint& point, const RectD& newFrame, const RectD& oldFrame)
{
	double scaleX = (point.x - oldFrame.left) / oldFrame.width;
	double scaleY = (point.y - oldFrame.top) / oldFrame.height;
	point = CPoint(newFrame.left + newFrame.width * scaleX, newFrame.top + newFrame.height * scaleY);
}
