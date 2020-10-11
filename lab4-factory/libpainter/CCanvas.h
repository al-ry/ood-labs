#pragma once
#include "ICanvas.h"

struct RGB
{
	RGB(double r, double g, double b)
		: red(r)
		, green(g)
		, blue(b)
	{
	}
	double red;
	double green;
	double blue;
};

class CCanvas : public ICanvas
{
public:
	CCanvas(GLFWwindow* window);
	void SetColor(Color color);
	void DrawLine(const CPoint& from, const CPoint& to);
	void DrawEllipse(const CPoint& center, double verticalRadius, double horizontalRadius);

private:
	GLFWwindow* m_window;
	RGB m_color;
};