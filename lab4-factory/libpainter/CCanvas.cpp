#include "stdafx.h"
#include "CCanvas.h"

const double DEG2RAD = M_PI / 180;

CCanvas::CCanvas(GLFWwindow* window)
	: m_window(window)
	, m_color(RGB(0, 0, 0))
{
}

void CCanvas::SetColor(Color color)
{
	if (color == Color::Black)
	{
		m_color = RGB(0, 0, 0);
	}
	else if (color == Color::Blue)
	{
		m_color = RGB(0, 0, 255);
	}
	else if (color == Color::Green)
	{
		m_color = RGB(0, 255, 0);
	}
	else if (color == Color::Pink)
	{
		m_color = RGB(255, 192, 203);
	}
	else if (color == Color::Red)
	{
		m_color = RGB(255, 0, 0);
	}
	else if (color == Color::Yellow)
	{
		m_color = RGB(255, 255, 0);
	}
}

void CCanvas::DrawLine(const CPoint& from, const CPoint& to)
{
	glLineWidth(2);
	glColor3d(m_color.red, m_color.green, m_color.blue);

	glBegin(GL_LINES);
	glVertex2d(from.x, from.y);
	glVertex2d(to.x, to.y);
	glEnd();

	glEnable(GL_LINE_SMOOTH);
}

void CCanvas::DrawEllipse(const CPoint& center, double verticalRadius, double horizontalRadius)
{
	glColor3d(m_color.red, m_color.green, m_color.blue);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		double degInRad = i * M_PI / 180;
		glVertex2d((cos(degInRad) * horizontalRadius) + center.x, (sin(degInRad) * verticalRadius) + center.y);
	}
	glEnd();
	glEnable(GL_LINE_SMOOTH);
}
