#include "CSlide.h"
#include <stdexcept>

CSlide::CSlide(double width, double height, const RGBAColor& backGroundColor)
	: m_width(width)
	, m_height(height)
	, m_backgroundColor(backGroundColor)
{
}

double CSlide::GetWidth() const
{
	return m_width;
}

double CSlide::GetHeight() const
{
	return m_height;
}

void CSlide::Draw(ICanvas& canvas) const
{
	for (auto& shape: m_shapes)
	{
		shape->Draw(canvas);
	}
}

size_t CSlide::GetShapesCount() const
{
	return m_shapes.size();
}

IShapePtr CSlide::GetShapeAtIndex(size_t index) const
{
	if (index >= m_shapes.size())
	{
		throw std::runtime_error("Index is out of range.");
	}
	return m_shapes.at(index);
}

void CSlide::InsertShape(const IShapePtr& shape, size_t index)
{
	if (index > m_shapes.size())
	{
		m_shapes.push_back(shape);
	}
	else
	{
		m_shapes.insert(m_shapes.begin() + index, shape);
	}
}

void CSlide::RemoveShapeAtIndex(size_t index)
{
	if (index >= m_shapes.size())
	{
		throw std::runtime_error("Index is out of range.");
	}
	m_shapes.erase(m_shapes.begin() + index);
}

RGBAColor CSlide::GetBackgroundColor() const
{
	return m_backgroundColor;
}

void CSlide::SetBackgroundColor(RGBAColor color)
{
	m_backgroundColor = color;
}
