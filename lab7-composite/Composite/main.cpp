#include "CRectangle.h"
#include <include\GLFW\glfw3.h>
#include "CCanvas.h"
#include "CLeafOutlineStyle.h"
#include "CEllipse.h"
#include "CTriangle.h"
#include "CGroup.h"
#include "ISlide.h"
#include "CSlide.h"


void DrawSlideOnCanvas(const ISlide& slide)
{
	GLFWwindow* window{};
	if (!glfwInit())
		return;
	window = glfwCreateWindow((int)slide.GetWidth(), (int)slide.GetHeight(), "Slide", NULL, NULL);
	if (!window)
	{
		return;
	}
	CCanvas canvas(window);

	glfwMakeContextCurrent(window);
	auto windowColor = slide.GetBackgroundColor();
	glClearColor(windowColor.r, windowColor.g, windowColor.b, windowColor.a);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		slide.Draw(canvas);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
}

IShapePtr CreateRoad()
{
	IShapePtr road = std::make_shared<CRectangle>(CPoint(-1, -0.6), 2, 2);
	road->GetFillStyle()->SetColor(RGBAColor(0.46f, 0.49f, 0.49f, 1.f));
	road->GetFillStyle()->Enable(true);
	road->GetLineStyle()->Enable(false);
	return road;
}

IShapePtr CreateSun()
{
	IShapePtr sun = std::make_shared<CEllipse>(CPoint(0.8, 0.8), 0.15, 0.15);
	sun->GetFillStyle()->SetColor(RGBAColor(255, 255, 0, 1));
	sun->GetFillStyle()->Enable(true);
	sun->GetLineStyle()->Enable(false);
	return sun;
}

IGroupPtr CreateTree()
{
	IShapePtr trunk = std::make_unique<CRectangle>(CPoint(0.4, 0.03), 0.02, 0.4);
	trunk->GetFillStyle()->Enable(true);
	trunk->GetLineStyle()->Enable(false);
	trunk->GetFillStyle()->SetColor(RGBAColor(0.4f, 0.26f, 0.13f, 0.f));

	IShapePtr topBranch = std::make_shared<CTriangle>(CPoint(0.32, -0.1), CPoint(0.4, 0.1), CPoint(0.5, -0.1));
	topBranch->GetLineStyle()->Enable(false);
	topBranch->GetFillStyle()->Enable(true);
	topBranch->GetFillStyle()->SetColor(RGBAColor(0, 1, 0, 1));
	IGroupPtr tree = std::make_unique<CGroup>();
	tree->InsertShape(trunk);
	tree->InsertShape(topBranch);

	return tree;
}


IGroupPtr CreateCar()
{
	IShapePtr roof = std::make_shared<CRectangle>(CPoint(-0.18, -0.3), 0.2, 0.2);
	roof->GetFillStyle()->Enable(true);
	roof->GetFillStyle()->SetColor(RGBAColor(1, 0, 0, 1));
	IShapePtr body = std::make_shared<CRectangle>(CPoint(-0.3, -0.5), 0.45, 0.2);
	IShapePtr wheel1 = std::make_shared<CEllipse>(CPoint(-0.2, -0.7), 0.06, 0.06);
	wheel1->GetFillStyle()->Enable(true);
	wheel1->GetFillStyle()->SetColor(RGBAColor(0, 0, 0, 1));
	IShapePtr wheel2 = std::make_shared<CEllipse>(CPoint(0.05, -0.7), 0.06, 0.06);
	wheel2->GetFillStyle()->Enable(true);
	wheel2->GetFillStyle()->SetColor(RGBAColor(0, 0, 0, 1));
	body->GetFillStyle()->Enable(true);
	body->GetFillStyle()->SetColor(RGBAColor(1, 0, 0, 1));
	IGroupPtr car = std::make_shared<CGroup>();
	car->InsertShape(body);
	car->InsertShape(wheel1);
	car->InsertShape(wheel2);
	car->InsertShape(roof);
	return car;
}

int main()
{
	CSlide slide(680, 680, RGBAColor(0.103f, 0.128f, 0.159f, 1.f));

	auto road = CreateRoad();
	auto car = CreateCar();

	auto sun = CreateSun();
	auto tree1 = CreateTree();
	auto tree2 = CreateTree();
	tree2->SetFrame(RectD{ -0.5, 0, tree1->GetFrame().width, tree1->GetFrame().height});
	

	car->SetFrame(RectD{ -0.5, 0, tree1->GetFrame().width, tree1->GetFrame().height });
	slide.InsertShape(road);
	slide.InsertShape(sun);
	slide.InsertShape(tree1);
	slide.InsertShape(tree2);
	slide.InsertShape(car);

	DrawSlideOnCanvas(slide);

	return 0;
}