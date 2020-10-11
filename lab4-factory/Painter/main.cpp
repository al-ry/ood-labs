#include "stdafx.h"
#include "../glfwlib/include/GLFW/glfw3.h"
#include "../libpainter/CCanvas.h"
#include "../libpainter/ShapeFactory.h"
#include "../libpainter/Designer.h"
#include "../libpainter/Painter.h"

void PrintHint()
{
	std::cout << "Format:\n"
			  << "\t<regular_polygon> <color> <center x> <center y> <radius> <vertex count>\n"
			  << "\t<triangle> <color> <vertex1 x> <vertex1 y> <vertex2 x> <vertex2 y> <vertex3 x> <vertex3 y>\n"
			  << "\t<rectangle> <color> <left top x> <left top y> <width> <height>\n"
			  << "\t<ellipse> <color> <center x> <center y> <vertical radius> <horizontal radius>\n";
	std::cout << "<color>:\n"
			  << "\tblack\n"
			  << "\tblue\n"
			  << "\tgreen\n"
			  << "\tpink\n"
			  << "\tyellow\n"
			  << "\tred\n";
	std::cout << "radius is float number\n";
	std::cout << "x,y are float numbers\n";
	std::cout << "<vertex count> is interger\n";
	std::cout << "To Teminate input enter EOLN\n";
	std::cout << "> Enter a shape: \n";
}

int main()
{
	PrintHint();
	CShapeFactory factory;
	CDesigner designer(factory);
	CPictureDraft draft = designer.CreateDraft(std::cin);
	CPainter painter;
	GLFWwindow* window{};
	if (!glfwInit())
		return 1;
	window = glfwCreateWindow(640, 640, "shapes", NULL, NULL);
	if (!window)
	{
		return 1;
	}
	CCanvas canvas(window);

	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		painter.DrawPicture(draft, canvas);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
