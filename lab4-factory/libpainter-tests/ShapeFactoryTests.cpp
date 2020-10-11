#include "stdafx.h"
#include "../libpainter/ShapeFactory.h"
#include "../libpainter/Triangle.h"
#include "../libpainter/RegularPolygon.h"
#include "../libpainter/Ellipse.h"
#include "../libpainter/Rectangle.h"

struct ShapesFactory_
{
	CShapeFactory factory;
};

BOOST_FIXTURE_TEST_SUITE(ShapesFactory, ShapesFactory_)
	BOOST_AUTO_TEST_SUITE(when_incorrect_type_of_shape)
		BOOST_AUTO_TEST_CASE(should_throw_exception)
		{
			BOOST_CHECK_THROW(std::unique_ptr<CShape> shape = factory.CreateShape("circle black 5"), std::runtime_error);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(Test_regular_polygon)
		BOOST_AUTO_TEST_SUITE(when_creating_regular_polygon)
			BOOST_AUTO_TEST_CASE(should_create_regular_polygon)
			{

				std::unique_ptr<CShape> shape = factory.CreateShape("regular_polygon black 5 5 10 6");
				CRegularPolygon regPol = dynamic_cast<CRegularPolygon&>(*shape.get());

				BOOST_CHECK(regPol.GetCenter() == CPoint(5, 5));
				BOOST_CHECK(regPol.GetColor() == Color::Black);
				BOOST_CHECK(regPol.GetRadius() == 10);
				BOOST_CHECK(regPol.GetVertexCount() == 6);
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(when_creating_with_incorrect_numbers_of_parametrs)
			BOOST_AUTO_TEST_CASE(should_throw_exception)
			{
				BOOST_CHECK_THROW(factory.CreateShape("regular_polygon black 5 5"), std::runtime_error);
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(when_creating_with_incorrect_color)
			BOOST_AUTO_TEST_CASE(should_throw_exception)
			{
				BOOST_CHECK_THROW(factory.CreateShape("regular_polygon navy 5 5 10 6"), std::runtime_error);
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(when_creating_with_incorrect_parameter_type)
			BOOST_AUTO_TEST_CASE(should_throw_exception)
			{
				BOOST_CHECK_THROW(factory.CreateShape("regular_polygon black 5 qq 10 6"), std::invalid_argument);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(Test_ellipse)
		BOOST_AUTO_TEST_SUITE(when_creating_ellipse)
			BOOST_AUTO_TEST_CASE(should_create_ellipse)
			{
				std::unique_ptr<CShape> shape = factory.CreateShape("ellipse pink 8 8 10 6");
				CEllipse ellipse = dynamic_cast<CEllipse&>(*shape.get());

				BOOST_CHECK(ellipse.GetCenter() == CPoint(8, 8));
				BOOST_CHECK(ellipse.GetColor() == Color::Pink);
				BOOST_CHECK(ellipse.GetVecticalRadius() == 10);
				BOOST_CHECK(ellipse.GetHorizontalRadius() == 6);
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(when_creating_with_incorrect_numbers_of_parametrs)
			BOOST_AUTO_TEST_CASE(should_throw_exception)
			{
				BOOST_CHECK_THROW(factory.CreateShape("ellipse 8 8 10 6"), std::runtime_error);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Test_rectangle)
		BOOST_AUTO_TEST_SUITE(when_creating_rectagle)
			BOOST_AUTO_TEST_CASE(should_create_rectangle)
			{
				std::unique_ptr<CShape> shape = factory.CreateShape("rectangle yellow 8 8 10.8 5.5");
				CRectangle rect = dynamic_cast<CRectangle&>(*shape.get());

				BOOST_CHECK(rect.GetLeftTop() == CPoint(8, 8));
				BOOST_CHECK(rect.GetColor() == Color::Yellow);
				BOOST_CHECK(rect.GetRightBottom().x == 8 + 10.8);
				BOOST_CHECK_EQUAL(rect.GetRightBottom().y, 8 - 5.5);
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(when_creating_with_incorrect_numbers_of_parametrs)
			BOOST_AUTO_TEST_CASE(should_throw_exception)
			{
				BOOST_CHECK_THROW(factory.CreateShape("rectangle green 8 10 6"), std::runtime_error);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(Test_triangle)
		BOOST_AUTO_TEST_SUITE(when_creating_triangle)
			BOOST_AUTO_TEST_CASE(should_create_triangle)
			{
				std::unique_ptr<CShape> shape = factory.CreateShape("triangle yellow 8.2 5.1 10.8 5.5 9 2");
				CTriangle rect = dynamic_cast<CTriangle&>(*shape.get());

				BOOST_CHECK(rect.GetColor() == Color::Yellow);
				BOOST_CHECK(rect.GetVertex1() == CPoint(8.2, 5.1));
				BOOST_CHECK(rect.GetVertex2() == CPoint(10.8, 5.5));
				BOOST_CHECK(rect.GetVertex3() == CPoint(9, 2));
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(when_creating_with_incorrect_numbers_of_parametrs)
			BOOST_AUTO_TEST_CASE(should_throw_exception)
			{
				BOOST_CHECK_THROW(factory.CreateShape("triangle yellow 8.2 5.1 10.8 5.5 4 4 4 4"), std::runtime_error);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()