// modern_graphics_lib.cpp : Defines the functions for the static library.
//

#include "framework.h"
#include "pch.h"
#include "modern_graphics_lib.h"

modern_graphics_lib::CModernGraphicsRenderer::CModernGraphicsRenderer(std::ostream& strm)
	: m_out(strm)
{
}

modern_graphics_lib::CModernGraphicsRenderer::~CModernGraphicsRenderer()
{
	if (m_drawing) // «авершаем рисование, если оно было начато
	{
		EndDraw();
	}
}

void modern_graphics_lib::CModernGraphicsRenderer::BeginDraw()
{
	if (m_drawing)
	{
		throw std::logic_error("Drawing has already begun");
	}
	m_out << "<draw>" << std::endl;
	m_drawing = true;
}

void modern_graphics_lib::CModernGraphicsRenderer::DrawLine(const CPoint& start, const CPoint& end, const CRGBAColor& color)
{
	if (!m_drawing)
	{
		throw std::logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
	}
	m_out << boost::format(R"(  <line fromX="%1%" fromY="%2%" toX="%3%" toY="%4%">)") % start.x % start.y % end.x % end.y
		  << std::endl
		  << boost::format(R"(    <color r="%1%" g="%2%" b="%3%" a="%4%" />)") % color.r % color.g % color.b % color.a
		  << std::endl
		  << boost::format(R"(  </line>)")
		  << std::endl;
}

void modern_graphics_lib::CModernGraphicsRenderer::EndDraw()
{
	if (!m_drawing)
	{
		throw std::logic_error("Drawing has not been started");
	}
	m_out << "</draw>" << std::endl;
	m_drawing = false;
}
