#include "ClassAdapter.h"

using namespace modern_graphics_lib;

ModernGraphicsRendererClassAdapter::ModernGraphicsRendererClassAdapter(std::ostream& strm)
	: CModernGraphicsRenderer(strm)
	, m_fromPoint(0, 0)
	, m_color(0, 0, 0, 1)
{
}

void ModernGraphicsRendererClassAdapter::MoveTo(int x, int y)
{
	m_fromPoint = CPoint(x, y);
}

void ModernGraphicsRendererClassAdapter::LineTo(int x, int y)
{
	CModernGraphicsRenderer::DrawLine(m_fromPoint, CPoint(x, y), m_color);
}

void ModernGraphicsRendererClassAdapter::SetColor(uint32_t rgbColor)
{
	float r = ((rgbColor >> 16) & 0xff) / 255.0f;
	float g = ((rgbColor >> 8) & 0xff) / 255.0f;
	float b = ((rgbColor)&0xff) / 255.0f;

	m_color = modern_graphics_lib::CRGBAColor(r, g, b, m_color.a);
}

void ModernGraphicsRendererClassAdapter::SetCapacity(float capacity)
{
	m_color.a = capacity;
}
