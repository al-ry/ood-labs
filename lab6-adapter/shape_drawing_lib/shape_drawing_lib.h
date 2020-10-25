#pragma once
#include "../graphics_lib/graphics_lib.h"

// Пространство имен библиотеки для рисования фигур (использует graphics_lib)
// Код библиотеки недоступен для изменения
namespace shape_drawing_lib
{
struct Point
{
	int x = 0 ;
	int y = 0;
};

// Интерфейс объектов, которые могут быть нарисованы на холсте из graphics_lib
class ICanvasDrawable
{
public:
	virtual void Draw(graphics_lib::ICanvas& canvas) const = 0;
	virtual ~ICanvasDrawable() = default;
};

class CTriangle : public ICanvasDrawable
{
public:
	CTriangle(const Point& p1, const Point& p2, const Point& p3, uint32_t color = 0x000000);
	void Draw(graphics_lib::ICanvas& canvas) const override;

private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
	uint32_t m_color;
};

class CRectangle : public ICanvasDrawable
{
public:
	CRectangle(const Point& leftTop, int width, int height, uint32_t color = 0x000000);

	void Draw(graphics_lib::ICanvas& canvas) const override;

private:
	Point m_leftTop;
	int m_width;
	int m_height;
	uint32_t m_color;
};

// Художник, способный рисовать ICanvasDrawable-объекты на ICanvas
class CCanvasPainter
{
public:
	CCanvasPainter(graphics_lib::ICanvas& canvas);
	void Draw(const ICanvasDrawable& drawable);

private:
	graphics_lib::ICanvas& m_canvas;
};
} // namespace shape_drawing_lib