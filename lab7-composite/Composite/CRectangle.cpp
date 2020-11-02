#include "CRectangle.h"

CRectangle::CRectangle(const CPoint& leftTop, double width, double height)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
	, CShape()
{
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}
CPoint CRectangle::GetRightBottom() const
{
	return CPoint(m_leftTop.x + m_width, m_leftTop.y - m_height);
}

RectD CRectangle::GetFrame() const
{
	return RectD{ m_leftTop.y, m_leftTop.y, m_width, m_height };
}

void CRectangle::SetFrame(const RectD& frame)
{
	m_leftTop = CPoint(frame.left, frame.top);
	m_width = frame.width;
	m_height = frame.height;
}


void CRectangle::FillShape(ICanvas& canvas) const
{
	CPoint rightTop = { GetLeftTop().x + m_width, GetLeftTop().y };
	CPoint leftBottom = { GetLeftTop().x, GetLeftTop().y - m_height };
	std::vector<CPoint> vertices = {
		GetLeftTop(),
		rightTop,
		GetRightBottom(),
		leftBottom,
	};
	canvas.FillConvexPolygon(vertices);
}

void CRectangle::CircleShape(ICanvas& canvas) const
{
	CPoint rightTop = { GetLeftTop().x + m_width, GetLeftTop().y };
	CPoint leftBottom = { GetLeftTop().x, GetLeftTop().y - m_height };
	canvas.DrawLine(GetLeftTop(), rightTop);
	canvas.DrawLine(rightTop, GetRightBottom());
	canvas.DrawLine(GetRightBottom(), leftBottom);
	canvas.DrawLine(leftBottom, GetLeftTop());
}

