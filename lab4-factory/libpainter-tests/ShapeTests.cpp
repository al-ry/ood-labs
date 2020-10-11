#include "stdafx.h"
#include "../libpainter/Shape.h"
#include "../libpainter/Rectangle.h"
#include "../libpainter/Triangle.h"
#include "../libpainter/Ellipse.h"
#include "../libpainter/RegularPolygon.h"

struct Rectangle_
{
	CPoint leftTop = CPoint(2, 8);
	CRectangle rect = CRectangle(Color::Black, leftTop, 20, 10);
};


BOOST_FIXTURE_TEST_SUITE(Rectangle, Rectangle_)
	BOOST_AUTO_TEST_SUITE(by_default)
		BOOST_AUTO_TEST_CASE(has_black_color)
		{
			BOOST_CHECK(rect.GetColor() == Color::Black);
		}
		BOOST_AUTO_TEST_CASE(has_left_bottom_coordinate)
		{
			BOOST_CHECK(rect.GetLeftTop().x == leftTop.x);
			BOOST_CHECK(rect.GetLeftTop().y == leftTop.y);
		}
		BOOST_AUTO_TEST_CASE(has_right_bottom_coordinate)
		{
			CPoint result = rect.GetRightBottom(); 
			BOOST_CHECK(result.x == 22.);
			BOOST_CHECK(result.y == -2.);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()



struct Triangle_
{
	CPoint vertex1 = CPoint(0, 3);
	CPoint vertex2 = CPoint(0, 0);
	CPoint vertex3 = CPoint(3, 0);
	CTriangle triangle = CTriangle(Color::Pink, vertex1, vertex2, vertex3);
};

BOOST_FIXTURE_TEST_SUITE(Triangle, Triangle_)
	BOOST_AUTO_TEST_SUITE(by_default)
		BOOST_AUTO_TEST_CASE(has_pink_color)
		{
			BOOST_CHECK(triangle.GetColor() == Color::Pink);
		}
		BOOST_AUTO_TEST_CASE(has_correct_vertices)
		{
			BOOST_CHECK(triangle.GetVertex1() == vertex1);
			BOOST_CHECK(triangle.GetVertex2() == vertex2);
			BOOST_CHECK(triangle.GetVertex3() == vertex3);
		}

	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()


struct Ellipse_
{
	CPoint center = CPoint(5, 5);
	double vertR = 5;
	double horR = 10;
	CEllipse ellipse = CEllipse(Color::Blue, center, vertR, horR);
};

BOOST_FIXTURE_TEST_SUITE(Ellipse, Ellipse_)
	BOOST_AUTO_TEST_SUITE(by_default)
		BOOST_AUTO_TEST_CASE(has_blue_color)
		{
			BOOST_CHECK(ellipse.GetColor() == Color::Blue);
		}
		BOOST_AUTO_TEST_CASE(has_correct_center)
		{
			BOOST_CHECK(ellipse.GetCenter() == center);
		}

		BOOST_AUTO_TEST_CASE(has_vertical_radius)
		{
			BOOST_CHECK(ellipse.GetVecticalRadius() == vertR);
		}
		BOOST_AUTO_TEST_CASE(has_hor_radius)
		{
			BOOST_CHECK(ellipse.GetHorizontalRadius() == horR);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()


struct RegularPolygon_
{
	double radius = 5;
	int vertexCount = 6;
	CPoint center = CPoint(4, 3);
	CRegularPolygon regPol = CRegularPolygon(Color::Green, center, radius, vertexCount);
};

BOOST_FIXTURE_TEST_SUITE(RegularPolygon, RegularPolygon_)
	BOOST_AUTO_TEST_SUITE(by_default)
		BOOST_AUTO_TEST_CASE(has_green_color)
		{
			BOOST_CHECK(regPol.GetColor() == Color::Green);
		}
		BOOST_AUTO_TEST_CASE(can_get_center)
		{
			BOOST_CHECK(regPol.GetCenter() == center);
		}

		BOOST_AUTO_TEST_CASE(can_get_vertex_count)
		{
			BOOST_CHECK(regPol.GetVertexCount() == vertexCount);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()