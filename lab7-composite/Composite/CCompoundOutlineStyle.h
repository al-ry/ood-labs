#pragma once
#include "IOutlineStyle.h"
#include <functional>

typedef std::function<void(std::function<void(IOutlineStyle&)>)> OutlineStyleEnumerator;

class CCompoundOutlineStyle : public IOutlineStyle
{
public:
	CCompoundOutlineStyle(OutlineStyleEnumerator & enumerator);

	std::optional<bool> IsEnabled() override;
	void Enable(bool enable) override;
	std::optional<RGBAColor> GetColor() const override;
	void SetColor(const RGBAColor& color) override;
	std::optional<float> GetLineWidth() const override;
	void SetLineWidth(float width) override;

private:
	OutlineStyleEnumerator m_enumerator;
};