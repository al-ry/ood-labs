#pragma once
#include "IStyle.h"
#include <functional>

typedef std::function<void(std::function<void(IStyle&)>)> FillStyleEnumerator;

class CCompoundFillStyle: public IStyle
{
public:
	CCompoundFillStyle(FillStyleEnumerator& enumerator);

	std::optional<bool> IsEnabled() override;
	void Enable(bool enable) override;

	std::optional<RGBAColor> GetColor() const override;
	void SetColor(const RGBAColor& color) override;
private:

	FillStyleEnumerator m_enumerator;
};