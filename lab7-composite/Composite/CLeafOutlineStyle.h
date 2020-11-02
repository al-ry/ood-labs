#pragma once
#include "IOutlineStyle.h"

class CLeafOutlineStyle: public IOutlineStyle
{
public:
	CLeafOutlineStyle(bool isEnabled, const RGBAColor& color, float lineWidth = 1.f);

	std::optional<bool> IsEnabled() override;
	void Enable(bool enable) override;

	std::optional<RGBAColor> GetColor() const override;
	void SetColor(const RGBAColor& color) override;

	std::optional<float> GetLineWidth() const override;
	void SetLineWidth(float lineWidth) override;


private:
	std::optional<bool> m_isEnabled;
	float m_lineWidth;
	RGBAColor m_color;
};
