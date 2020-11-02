#pragma once
#include "CShape.h"

class CEllipse : public CShape
{
public:
	CEllipse(CPoint center, double verticalRadius, double horizontalRadius);
	RectD GetFrame() const override;
	void SetFrame(const RectD& frame) override;
	CPoint GetCenter() const;

	double GetVecticalRadius() const;
	double GetHorizontalRadius() const;


protected:
	void CircleShape(ICanvas& canvas) const override final;
	void FillShape(ICanvas& canvas) const override final;

private:
	double m_verticalRadius;
	double m_horizontalRadius;
	CPoint m_center;
};