#include "CCompoundFillStyle.h"

CCompoundFillStyle::CCompoundFillStyle(FillStyleEnumerator& enumerator)
	: m_enumerator(enumerator)
{
}

std::optional<bool> CCompoundFillStyle::IsEnabled()
{
	std::optional<bool> isEnabled;
	bool isInitialized = false;
	auto callback = [&](IStyle& style) {
		if (!isEnabled.has_value() && !isInitialized)
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

void CCompoundFillStyle::Enable(bool enable)
{
	m_enumerator([&](IStyle& style) {
		style.Enable(enable);
	});
}

std::optional<RGBAColor> CCompoundFillStyle::GetColor() const
{
	std::optional<RGBAColor> color;
	bool isColorInitialized = false;
	auto callback = [&](IStyle& style) {
		if (!color.has_value() && !isColorInitialized)
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

void CCompoundFillStyle::SetColor(const RGBAColor& color)
{
	m_enumerator([&](IStyle& style) {
		style.SetColor(color);
	});
}
