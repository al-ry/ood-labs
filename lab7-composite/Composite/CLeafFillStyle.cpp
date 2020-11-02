#include "CLeafFillStyle.h"

CLeafFillStyle::CLeafFillStyle(bool isEnabled, const RGBAColor& color)
	: m_color(color)
	, m_isEnabled(isEnabled)
{
}

std::optional<bool> CLeafFillStyle::IsEnabled()
{
	return m_isEnabled;
}

void CLeafFillStyle::Enable(bool enable)
{
	m_isEnabled = enable;
}

std::optional<RGBAColor> CLeafFillStyle::GetColor() const
{
	return m_color;
}

void CLeafFillStyle::SetColor(const RGBAColor& color)
{
	m_color = RGBAColor(color.r, color.g, color.b, color.a);
}
