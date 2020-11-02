#pragma once

#include "CShape.h"


class CRectangle : public CShape
{
public:
	CRectangle(const CPoint& leftTop, double width, double height);

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;

	RectD GetFrame() const override;
	void SetFrame(const RectD& frame) override;

protected:
	void FillShape(ICanvas& canvas) const override final;
	void CircleShape(ICanvas& canvas) const override final;

private:
	CPoint m_leftTop;
	double m_width;
	double m_height;
};