#include "CCanvas.h"
#define _USE_MATH_DEFINES
#include <math.h>

CCanvas::CCanvas(GLFWwindow* window)
	: m_window(window)
{
}

void CCanvas::DrawLine(const CPoint& from, const CPoint& to)
{
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(m_lineWidth);

	glColor4d(m_outlineColor.r, m_outlineColor.g, m_outlineColor.b, m_outlineColor.a);

	glBegin(GL_LINES);
	glVertex2d(from.x, from.y);
	glVertex2d(to.x, to.y);
	glEnd();
}

void CCanvas::DrawEllipse(const CPoint& center, double verticalRadius, double horizontalRadius)
{
	glEnable(GL_LINE_SMOOTH);
	glColor4d(m_outlineColor.r, m_outlineColor.g, m_outlineColor.b, m_outlineColor.a);
	glLineWidth(m_lineWidth);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		double degInRad = i * M_PI / 180;
		glVertex2d((cos(degInRad) * horizontalRadius) + center.x, (sin(degInRad) * verticalRadius) + center.y);
	}
	glEnd();
}

void CCanvas::FillConvexPolygon(std::vector<CPoint> vertices)
{
	glColor4d(m_fillColor.r, m_fillColor.g, m_fillColor.b, m_fillColor.a);
	glBegin(GL_POLYGON);
	for (auto& vertex : vertices)
	{
		glVertex2d(vertex.x, vertex.y);
	}
	glEnd();
}

void CCanvas::FillEllipse(const CPoint& center, double verticalRadius, double horizontalRadius)
{
	glColor4d(m_fillColor.r, m_fillColor.g, m_fillColor.b, m_fillColor.a);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		double degInRad = i * M_PI / 180;
		glVertex2d((cos(degInRad) * horizontalRadius) + center.x, (sin(degInRad) * verticalRadius) + center.y);
	}
	glEnd();
}

void CCanvas::SetLineWidth(float lineWidth)
{
	m_lineWidth = lineWidth;
}

void CCanvas::SetLineColor(const RGBAColor& color)
{
	m_outlineColor = color;
}

void CCanvas::SetFillColor(const RGBAColor& color)
{
	m_fillColor = color;
}
