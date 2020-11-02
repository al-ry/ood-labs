#pragma once
#include "IShape.h"
#include "CLeafFillStyle.h"
#include "CLeafOutlineStyle.h"
#include "IGroup.h"

class CShape : public IShape
{
public:
	CShape();

	OutlineStylePtr GetLineStyle() const override;

	StylePtr GetFillStyle() const override;

	IGroupPtr GetGroup() override;

	void Draw(ICanvas& canvas) const override;

protected:
	virtual void FillShape(ICanvas& canvas) const = 0;
	virtual void CircleShape(ICanvas& canvas) const = 0;

private:
	StylePtr m_fillStyle;
	OutlineStylePtr m_lineStyle;
};