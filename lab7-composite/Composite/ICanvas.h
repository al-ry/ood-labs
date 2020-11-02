#pragma once
#include <vector>
#include "CPoint.h"
#include "IStyle.h"

class ICanvas
{
public:
	virtual void DrawLine(const CPoint& from, const CPoint& to) = 0;
	virtual void DrawEllipse(const CPoint& center, double verticalRadius, double horizontalRadius) = 0;
	virtual void FillConvexPolygon(std::vector<CPoint> vertices) = 0;
	virtual void FillEllipse(const CPoint& center, double verticalRadius, double horizontalRadius) = 0;
	virtual void SetLineWidth(float lineWidth) = 0;
	virtual void SetLineColor(const RGBAColor& color) = 0;
	virtual void SetFillColor(const RGBAColor& color) = 0;

	virtual ~ICanvas() = default;
};