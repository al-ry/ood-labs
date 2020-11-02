#pragma once
#include "CShape.h"

class CTriangle : public CShape
{
public:
	CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3);

	RectD GetFrame() const override;

	void SetFrame(const RectD& frame) override;

	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

protected:
	void FillShape(ICanvas& canvas) const override final;
	void CircleShape(ICanvas& canvas) const override final;

private:
	static void RecalculatePointPosition(CPoint& point, const RectD& newFrame,const RectD& oldFrame);

	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
};