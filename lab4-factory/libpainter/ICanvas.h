#pragma once
#include "Color.h"
#include "Point.h"
#include "../glfwlib/include/GLFW/glfw3.h"

class ICanvas
{
public:
	virtual void SetColor(Color color) = 0;
	virtual void DrawLine(const CPoint& from, const CPoint& to) = 0;
	virtual void DrawEllipse(const CPoint& center, double verticalRadius, double horizontalRadius) = 0;

	virtual ~ICanvas() = default;
};

