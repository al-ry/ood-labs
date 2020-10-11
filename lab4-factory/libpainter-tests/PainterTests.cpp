#include "stdafx.h"
#include "../libpainter/IPainter.h"
#include "../libpainter/Painter.h"
#include "MockCanvas.h"
#include <boost\test\tools\output_test_stream.hpp>
#include "MockShape.h"
#include "../libpainter/Ellipse.h"
#include "../libpainter/Triangle.h"


struct Painter_
{
	boost::test_tools::output_test_stream strm;
	MockCanvas canvas;
	CPictureDraft draft;
	CPainter painter;
	Painter_()
		: canvas(strm, Color::Black)
		, draft()
		, painter()
	{
		draft.AddShape(std::make_unique<CMockShape>("mockShape"));
		draft.AddShape(std::make_unique<CEllipse>(Color::Red, CPoint(0, 0), 5, 5));
		draft.AddShape(std::make_unique<CTriangle>(Color::Yellow, CPoint(0,0), CPoint(0,0), CPoint(0,0)));
	}
};

BOOST_FIXTURE_TEST_SUITE(Painter, Painter_)
	BOOST_AUTO_TEST_SUITE(when_draw_picture)
		BOOST_AUTO_TEST_CASE(should_draw_draft_in_appropiate_order)
		{
			painter.DrawPicture(draft, canvas);

			BOOST_CHECK(strm.is_equal("DrawLine\nDrawEllipse\nDrawLine\nDrawLine\nDrawLine\n"));
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
