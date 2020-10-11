#include "stdafx.h"
#include "../libpainter/ICanvas.h"
#include <boost\test\tools\output_test_stream.hpp>
#include "MockCanvas.h"



struct Canvas_
{
	MockCanvas canvas;
	Color color = Color::Green;
	boost::test_tools::output_test_stream strm;
	Canvas_()
		: canvas(strm, color)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Canvas, Canvas_)
	BOOST_AUTO_TEST_SUITE(by_default)
		BOOST_AUTO_TEST_CASE(has_color)
		{
			canvas.SetColor(Color::Green);
			BOOST_CHECK(canvas.m_color == color);
		}
		BOOST_AUTO_TEST_CASE(can_change_color)
		{
			canvas.SetColor(Color::Red);
			BOOST_CHECK(canvas.m_color == Color::Red);
		}
		BOOST_AUTO_TEST_CASE(can_draw_line)
		{
			canvas.DrawLine(CPoint(), CPoint());
			BOOST_CHECK(strm.is_equal("DrawLine\n"));
		}
		BOOST_AUTO_TEST_CASE(can_draw_ellipse)
		{
			canvas.DrawEllipse(CPoint(), 5, 5);
			BOOST_CHECK(strm.is_equal("DrawEllipse\n"));
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()