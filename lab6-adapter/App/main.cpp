#include "../shape_drawing_lib/shape_drawing_lib.h"
#include "../modern_graphics_lib/modern_graphics_lib.h"
#include <iostream>
#include <string>
#include "ObjectAdapter.h"
#include "ClassAdapter.h"

// Пространство имен приложения (доступно для модификации)
namespace app
{
void PaintPicture(shape_drawing_lib::CCanvasPainter& painter)
{
	using namespace shape_drawing_lib;

	CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 0x00ff00);
	CRectangle rectangle({ 30, 40 }, 18, 24);

	std::cout << "triangle: \n";
	painter.Draw(triangle);
	std::cout << "rectangle: \n";
	painter.Draw(rectangle);
}

void PaintPictureOnCanvas()
{
	using namespace shape_drawing_lib;
	graphics_lib::CCanvas simpleCanvas;
	CCanvasPainter painter(simpleCanvas);
	PaintPicture(painter);
}
void PaintPictureOnModernGraphicsRendererUsingObjectAdapter()
{
	using namespace modern_graphics_lib;

	CModernGraphicsRenderer renderer(std::cout);
	CModernGraphicsRendererObjectAdapter rendererAdapter(renderer);
	renderer.BeginDraw();
	shape_drawing_lib::CCanvasPainter painter(rendererAdapter);
	PaintPicture(painter);
}
void PaintPictureOnModernGraphicsRendererUsingClassAdapter()
{
	using namespace modern_graphics_lib;
	ModernGraphicsRendererClassAdapter rendererClassAdapter(std::cout);
	rendererClassAdapter.SetOpacity(0.5);
	rendererClassAdapter.BeginDraw();
	shape_drawing_lib::CCanvasPainter painter(rendererClassAdapter);
	PaintPicture(painter);
}

} // namespace app

int main()
{
	std::cout << "Should we use new API (y)?";
	std::string userInput;
	if (std::getline(std::cin, userInput) && (userInput == "y" || userInput == "Y"))
	{
		std::cout << "Rendering via object adapter impl:\n";
		app::PaintPictureOnModernGraphicsRendererUsingObjectAdapter();
		std::cout << "\n\n\n-----------------------------------------\n\n\n";
		std::cout << "Rendering via class adapter impl:\n";
		app::PaintPictureOnModernGraphicsRendererUsingClassAdapter();
	}
	else
	{
		app::PaintPictureOnCanvas();
	}
	return 0;
}