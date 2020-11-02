#include "CEllipse.h"

CEllipse::CEllipse(CPoint center, double verticalRadius, double horizontalRadius)
	: m_center(center)
	, m_verticalRadius(verticalRadius)
	, m_horizontalRadius(horizontalRadius)
	, CShape()
{
}


RectD CEllipse::GetFrame() const
{
	auto leftTopX = m_center.x - m_horizontalRadius;
	auto leftTopY = m_center.y - m_verticalRadius;
	return RectD{ leftTopX, leftTopY, m_horizontalRadius * 2.f, m_verticalRadius * 2.f };
}

void CEllipse::SetFrame(const RectD& frame)
{
	m_horizontalRadius = frame.width / 2;
	m_verticalRadius = frame.height / 2;
	m_center.x = frame.left + frame.width / 2;
	m_center.y = frame.top + frame.height / 2;
}


CPoint CEllipse::GetCenter() const
{
	return m_center;
}

double CEllipse::GetVecticalRadius() const
{
	return m_verticalRadius;
}

double CEllipse::GetHorizontalRadius() const
{
	return m_horizontalRadius;
}

void CEllipse::CircleShape(ICanvas& canvas) const
{
	canvas.DrawEllipse(m_center, m_verticalRadius, m_horizontalRadius);
}

void CEllipse::FillShape(ICanvas& canvas) const
{
	canvas.FillEllipse(m_center, m_verticalRadius, m_horizontalRadius);
}
