#include "pch.h"
#include "shape_drawing_lib.h"

// TODO: This is an example of a library function

shape_drawing_lib::CTriangle::CTriangle(const Point& p1, const Point& p2, const Point& p3, uint32_t color)
	: m_vertex1(p1)
	, m_vertex2(p2)
	, m_vertex3(p3)
	, m_color(color)
{
}

void shape_drawing_lib::CTriangle::Draw(graphics_lib::ICanvas& canvas) const
{
	canvas.SetColor(m_color);
	canvas.MoveTo(m_vertex1.x, m_vertex1.y);
	canvas.LineTo(m_vertex2.x, m_vertex2.y);
	canvas.MoveTo(m_vertex2.x, m_vertex2.y);
	canvas.LineTo(m_vertex3.y, m_vertex3.y);
	canvas.MoveTo(m_vertex3.x, m_vertex3.y);
	canvas.LineTo(m_vertex1.x, m_vertex1.y);
}

shape_drawing_lib::CRectangle::CRectangle(const Point& leftTop, int width, int height, uint32_t color)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
	, m_color(color)
{
}

void shape_drawing_lib::CRectangle::Draw(graphics_lib::ICanvas& canvas) const
{
	canvas.SetColor(m_color);
	canvas.MoveTo(m_leftTop.x, m_leftTop.y);
	canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);
	canvas.MoveTo(m_leftTop.x + m_width, m_leftTop.y);
	canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y - m_height);
	canvas.MoveTo(m_leftTop.x, m_leftTop.y);
	canvas.LineTo(m_leftTop.x, m_leftTop.y - m_height);
}

shape_drawing_lib::CCanvasPainter::CCanvasPainter(graphics_lib::ICanvas& canvas)
	: m_canvas(canvas)
{
}

void shape_drawing_lib::CCanvasPainter::Draw(const ICanvasDrawable& drawable)
{
	drawable.Draw(m_canvas);
}
