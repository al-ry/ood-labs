#pragma once
#include "IDrawable.h"
#include "IShape.h"
#include "IGroup.h"
class ISlide : public IDrawable
{
public:
	virtual double GetWidth() const = 0;
	virtual double GetHeight() const = 0;

	virtual RGBAColor GetBackgroundColor() const = 0;
	virtual void SetBackgroundColor(RGBAColor color) = 0;
};