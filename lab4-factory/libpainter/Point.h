#pragma once

class CPoint
{
public:
	CPoint(double x, double y)
	{
		this->x = x;
		this->y = y;
	}
	CPoint()
	{
	}
	double x = 0;
	double y = 0;

	bool operator==(const CPoint& point) const
	{
		return ((x == point.x) && (y == point.y));
	}

	bool operator!=(const CPoint& point) const
	{
		return !(*this == point);
	}
};
