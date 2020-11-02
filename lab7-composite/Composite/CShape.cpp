#include "CShape.h"

CShape::CShape()
{
	m_fillStyle = std::make_shared<CLeafFillStyle>(false, RGBAColor(0, 0, 0, 1));
	m_lineStyle = std::make_shared<CLeafOutlineStyle>(true, RGBAColor(255, 255, 255, 1));
}

OutlineStylePtr CShape::GetLineStyle() const
{
	return m_lineStyle;
}

StylePtr CShape::GetFillStyle() const
{
	return m_fillStyle;
}

IGroupPtr CShape::GetGroup()
{
	return nullptr;
}

void CShape::Draw(ICanvas& canvas) const
{
	if (m_lineStyle->IsEnabled().value())
	{
		canvas.SetLineColor(m_lineStyle->GetColor().value());
		canvas.SetLineWidth(*m_lineStyle->GetLineWidth());
		CircleShape(canvas);
	}
	if (m_fillStyle->IsEnabled().value())
	{
		canvas.SetFillColor(m_fillStyle->GetColor().value());
		FillShape(canvas);
	}
}
