#pragma once
#include "IStyle.h"

class CLeafFillStyle : public IStyle
{
public:
	CLeafFillStyle(bool isEnabled, const RGBAColor& color);


	std::optional<bool> IsEnabled() override;
	void Enable(bool enable) override;
	std::optional<RGBAColor> GetColor() const override;
	void SetColor(const RGBAColor& color) override;

private:
	RGBAColor m_color;
	std::optional<bool> m_isEnabled;
};

typedef std::shared_ptr<CLeafFillStyle> CLeafFillStylePtr;