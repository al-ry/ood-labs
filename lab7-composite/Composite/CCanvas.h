#pragma once
#include "ICanvas.h"
#include "CPoint.h"
#include "../glfwlib/include/GLFW/glfw3.h"
#include "IStyle.h"

class CCanvas : public ICanvas
{
public:
	CCanvas(GLFWwindow* window);
	void DrawLine(const CPoint& from, const CPoint& to) override;
	void DrawEllipse(const CPoint& center, double verticalRadius, double horizontalRadius) override;
	void FillConvexPolygon(std::vector<CPoint> vertices) override;
	void FillEllipse(const CPoint& center, double verticalRadius, double horizontalRadius) override;
	void SetLineWidth(float lineWidth) override; 
	void SetLineColor(const RGBAColor& color) override;
	void SetFillColor(const RGBAColor& color) override;

private:
	GLFWwindow* m_window;
	RGBAColor m_outlineColor;
	RGBAColor m_fillColor;
	float m_lineWidth = 1.f;

};