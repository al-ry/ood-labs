#pragma once
#include "IStyle.h"

class IOutlineStyle : public IStyle
{
public:
	virtual std::optional<float> GetLineWidth() const = 0;
	virtual void SetLineWidth(float width) = 0;
};

typedef std::shared_ptr<IOutlineStyle> OutlineStylePtr;