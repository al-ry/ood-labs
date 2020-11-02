#pragma once
#include "ISlide.h"


class CSlide: public ISlide
{
public:
	CSlide(double width, double height, const RGBAColor& backGroundColor = { 0, 0, 0, 1 });

	double GetWidth() const override;
	double GetHeight() const override;
	void Draw(ICanvas& canvas) const override;

	size_t GetShapesCount() const;
	IShapePtr GetShapeAtIndex(size_t index) const;
	void InsertShape(const IShapePtr& shape, size_t index = std::numeric_limits<size_t>::max());
	void RemoveShapeAtIndex(size_t index);


	RGBAColor GetBackgroundColor() const override;
	void SetBackgroundColor(RGBAColor color) override;

private:
	double m_width;
	double m_height;
	RGBAColor m_backgroundColor;
	std::vector<IShapePtr> m_shapes;
};