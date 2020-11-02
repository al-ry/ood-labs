#pragma once

class CPoint
{
public:
	CPoint(double x, double y)
	{
		this->x = x;
		this->y = y;
	}
	CPoint() = default;
	double x = 0;
	double y = 0;
};