#include "CLeafOutlineStyle.h"
#include "IStyle.h"

CLeafOutlineStyle::CLeafOutlineStyle(bool isEnabled, const RGBAColor& color, float lineWidth)
	: m_color(color)
	, m_lineWidth(lineWidth)
	, m_isEnabled(isEnabled)
{
}


std::optional<bool> CLeafOutlineStyle::IsEnabled()
{
	return m_isEnabled;
}

void CLeafOutlineStyle::Enable(bool enable)
{
	m_isEnabled = enable;
}

std::optional<RGBAColor> CLeafOutlineStyle::GetColor() const
{
	return m_color;
}

void CLeafOutlineStyle::SetColor(const RGBAColor& color)
{
	m_color = RGBAColor(color.r, color.g, color.b, color.a);
}

std::optional<float> CLeafOutlineStyle::GetLineWidth() const
{
	return m_lineWidth;
}

void CLeafOutlineStyle::SetLineWidth(float lineWidth)
{
	m_lineWidth = lineWidth;
}
