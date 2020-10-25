#include "stdafx.h"
#include "../modern_graphics_lib/modern_graphics_lib.h"
#include "../App/ClassAdapter.h"

using namespace modern_graphics_lib;

struct ModernGraphicsRendererClassAdapter_
{
	std::stringstream ss;
	ModernGraphicsRendererClassAdapter rendererClassAdapter;
	ModernGraphicsRendererClassAdapter_()
		: rendererClassAdapter(ss)
	{
	}
};


BOOST_FIXTURE_TEST_SUITE(ModernGraphicsRendererClassAdapter_tests, ModernGraphicsRendererClassAdapter_)
	BOOST_AUTO_TEST_SUITE(when_draw_line)
		BOOST_AUTO_TEST_CASE(should_add_line_to_stream)
		{
			rendererClassAdapter.BeginDraw();
			rendererClassAdapter.MoveTo(5, 7);
			rendererClassAdapter.LineTo(2, 3);

			BOOST_CHECK_EQUAL(ss.str(), "<draw>\n  <line fromX=\"5\" fromY=\"7\" toX=\"2\" toY=\"3\">\n    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n  </line>\n");
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(when_change_color)
		BOOST_AUTO_TEST_CASE(should_change_color)
		{
			rendererClassAdapter.BeginDraw();
			rendererClassAdapter.SetColor(0xffffff);
			rendererClassAdapter.MoveTo(5, 7);
			rendererClassAdapter.LineTo(2, 3);

			BOOST_CHECK_EQUAL(ss.str(), "<draw>\n  <line fromX=\"5\" fromY=\"7\" toX=\"2\" toY=\"3\">\n    <color r=\"1\" g=\"1\" b=\"1\" a=\"1\" />\n  </line>\n");
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(when_change_capacity_after_color)
		BOOST_AUTO_TEST_CASE(should_change_capacity)
		{
			rendererClassAdapter.BeginDraw();
			rendererClassAdapter.SetColor(0x00ff00);
			rendererClassAdapter.SetCapacity(0.5);
			rendererClassAdapter.MoveTo(5, 7);
			rendererClassAdapter.LineTo(2, 3);

			BOOST_CHECK_EQUAL(ss.str(), "<draw>\n  <line fromX=\"5\" fromY=\"7\" toX=\"2\" toY=\"3\">\n    <color r=\"0\" g=\"1\" b=\"0\" a=\"0.5\" />\n  </line>\n");
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(when_change_capacity_before_color)
		BOOST_AUTO_TEST_CASE(should_change_capacity)
		{
			rendererClassAdapter.BeginDraw();
			rendererClassAdapter.SetCapacity(0.5);
			rendererClassAdapter.SetColor(0x00ff00);
			rendererClassAdapter.MoveTo(5, 7);
			rendererClassAdapter.LineTo(2, 3);

			BOOST_CHECK_EQUAL(ss.str(), "<draw>\n  <line fromX=\"5\" fromY=\"7\" toX=\"2\" toY=\"3\">\n    <color r=\"0\" g=\"1\" b=\"0\" a=\"0.5\" />\n  </line>\n");
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_CASE(can_end_drawing)
	{
		rendererClassAdapter.BeginDraw();
		rendererClassAdapter.SetColor(0x00ff00);
		rendererClassAdapter.SetCapacity(0.5);
		rendererClassAdapter.MoveTo(5, 7);
		rendererClassAdapter.LineTo(2, 3);
		rendererClassAdapter.EndDraw();

		BOOST_CHECK_EQUAL(ss.str(), "<draw>\n  <line fromX=\"5\" fromY=\"7\" toX=\"2\" toY=\"3\">\n    <color r=\"0\" g=\"1\" b=\"0\" a=\"0.5\" />\n  </line>\n</draw>\n");
	}
BOOST_AUTO_TEST_SUITE_END()