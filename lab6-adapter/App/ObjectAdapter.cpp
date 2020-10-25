#include "ObjectAdapter.h"
using namespace modern_graphics_lib;

CModernGraphicsRendererObjectAdapter::CModernGraphicsRendererObjectAdapter(CModernGraphicsRenderer& renderer)
	: m_renderer(renderer)
	, m_fromPoint(0, 0)
	, m_color(0, 0, 0, 1)
{
}

void CModernGraphicsRendererObjectAdapter::MoveTo(int x, int y)
{
	m_fromPoint = CPoint(x, y);
}

void CModernGraphicsRendererObjectAdapter::LineTo(int x, int y)
{
	m_renderer.DrawLine(m_fromPoint, CPoint(x, y), m_color);
}

void CModernGraphicsRendererObjectAdapter::SetColor(uint32_t rgbColor)
{
	float r = ((rgbColor >> 16) & 0xff) / 255.0f;
	float g = ((rgbColor >> 8) & 0xff) / 255.0f;
	float b = ((rgbColor) & 0xff) / 255.0f;

	m_color = modern_graphics_lib::CRGBAColor(r, g, b, m_color.a);
}

void CModernGraphicsRendererObjectAdapter::SetCapacity(float capacity)
{
	m_color.a = capacity;
}