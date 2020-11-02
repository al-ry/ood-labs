#include "stdafx.h"
#include "../App/ObjectAdapter.h"
#include "../modern_graphics_lib/modern_graphics_lib.h"

using namespace modern_graphics_lib;

struct ModernGraphicsRendererAdapter_
{
	std::stringstream ss;
	CModernGraphicsRenderer renderer;
	CModernGraphicsRendererObjectAdapter rendererAdapter;
	ModernGraphicsRendererAdapter_()
		: renderer(ss)
		, rendererAdapter(renderer)
	{
	}
};


BOOST_FIXTURE_TEST_SUITE(ModernGraphicsRendererAdapter, ModernGraphicsRendererAdapter_)
	BOOST_AUTO_TEST_SUITE(when_DrawLine_before_call_DrawBegin)
		BOOST_AUTO_TEST_CASE(should_throw_exception)
		{
			BOOST_CHECK_THROW(rendererAdapter.LineTo(5, 5), std::logic_error);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(when_BeginDraw_twice)
		BOOST_AUTO_TEST_CASE(should_throw_exception)
		{
			renderer.BeginDraw();
			BOOST_CHECK_THROW(renderer.BeginDraw(), std::logic_error);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(when_call_EndDraw_before_BeginDraw)
		BOOST_AUTO_TEST_CASE(should_throw_exception)
		{
			BOOST_CHECK_THROW(renderer.EndDraw(), std::logic_error);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(when_draw_line)
		BOOST_AUTO_TEST_CASE(should_add_line_to_stream)
		{
			renderer.BeginDraw();
			rendererAdapter.MoveTo(5, 7);
			rendererAdapter.LineTo(2, 3);

			BOOST_CHECK_EQUAL(ss.str(), "<draw>\n  <line fromX=\"5\" fromY=\"7\" toX=\"2\" toY=\"3\">\n    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n  </line>\n");
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(when_change_color)
		BOOST_AUTO_TEST_CASE(should_change_color)
		{
			renderer.BeginDraw();
			rendererAdapter.SetColor(0xffffff);
			rendererAdapter.MoveTo(5, 7);
			rendererAdapter.LineTo(2, 3);

			BOOST_CHECK_EQUAL(ss.str(), "<draw>\n  <line fromX=\"5\" fromY=\"7\" toX=\"2\" toY=\"3\">\n    <color r=\"1\" g=\"1\" b=\"1\" a=\"1\" />\n  </line>\n");
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(when_change_capacity_after_color)
		BOOST_AUTO_TEST_CASE(should_change_capacity)
		{
			renderer.BeginDraw();
			rendererAdapter.SetColor(0x00ff00);
			rendererAdapter.MoveTo(5, 7);
			rendererAdapter.LineTo(2, 3);

			BOOST_CHECK_EQUAL(ss.str(), "<draw>\n  <line fromX=\"5\" fromY=\"7\" toX=\"2\" toY=\"3\">\n    <color r=\"0\" g=\"1\" b=\"0\" a=\"1\" />\n  </line>\n");
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(when_change_capacity_before_color)
		BOOST_AUTO_TEST_CASE(should_change_capacity)
		{
			renderer.BeginDraw();
			rendererAdapter.SetColor(0x00ff00);
			rendererAdapter.MoveTo(5, 7);
			rendererAdapter.LineTo(2, 3);

			BOOST_CHECK_EQUAL(ss.str(), "<draw>\n  <line fromX=\"5\" fromY=\"7\" toX=\"2\" toY=\"3\">\n    <color r=\"0\" g=\"1\" b=\"0\" a=\"1\" />\n  </line>\n");
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_CASE(can_end_drawing)
	{
		renderer.BeginDraw();
		rendererAdapter.SetColor(0x00ff00);
		rendererAdapter.MoveTo(5, 7);
		rendererAdapter.LineTo(2, 3);
		renderer.EndDraw();

		BOOST_CHECK_EQUAL(ss.str(), "<draw>\n  <line fromX=\"5\" fromY=\"7\" toX=\"2\" toY=\"3\">\n    <color r=\"0\" g=\"1\" b=\"0\" a=\"1\" />\n  </line>\n</draw>\n");
	}
BOOST_AUTO_TEST_SUITE_END()