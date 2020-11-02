#include "CCompoundOutlineStyle.h"

CCompoundOutlineStyle::CCompoundOutlineStyle(OutlineStyleEnumerator& enumerator)
	: m_enumerator(enumerator)
{
}

std::optional<bool> CCompoundOutlineStyle::IsEnabled()
{
	std::optional<bool> isEnabled;
	bool isInitialized = false;
	auto callback = [&](IOutlineStyle& style) {
		if (!isInitialized)
		{
			isEnabled = style.IsEnabled();
			isInitialized = true;
		}
		else if (isEnabled != style.IsEnabled())
		{
			isEnabled = std::nullopt;
		}
	};
	m_enumerator(callback);
	return isEnabled;
}

void CCompoundOutlineStyle::Enable(bool enable)
{
	m_enumerator([&](IOutlineStyle& style) {
		style.Enable(enable);
	});
}

std::optional<RGBAColor> CCompoundOutlineStyle::GetColor() const
{
	std::optional<RGBAColor> color;
	bool isColorInitialized = false;
	auto callback = [&](IOutlineStyle& style) {
		if (!isColorInitialized)
		{
			color = style.GetColor();
			isColorInitialized = true;
		}
		else if (color != style.GetColor())
		{
			color = std::nullopt;
		}
	};

	m_enumerator(callback);

	return color;
}

void CCompoundOutlineStyle::SetColor(const RGBAColor& color)
{
	m_enumerator([&](IOutlineStyle& style) {
		style.SetColor(color);
	});
}

std::optional<float> CCompoundOutlineStyle::GetLineWidth() const
{
	std::optional<float> width = std::nullopt;
	bool isWidthInitialized = false;
	auto callback = [&](IOutlineStyle& style) {
		if (!isWidthInitialized)
		{
			width = style.GetLineWidth();
			isWidthInitialized = true;
		}
		else if (width != style.GetLineWidth())
		{
			width = std::nullopt;
		}
	};

	m_enumerator(callback);

	return width;
}

void CCompoundOutlineStyle::SetLineWidth(float width)
{
	m_enumerator([&](IOutlineStyle& style) {
		style.SetLineWidth(width);
	});
}
