#include "stdafx.h"
#include "../DocumentEditor/Image.h"

struct Image_
{
	int width = 400;
	int height = 200;
	Path path = Path("../DocumentEditorTests/test_img/boost.png");
	CImage image;
	CHistory history;
	Image_()
		: image(path, width, height, history)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Test_CImage, Image_)
	BOOST_AUTO_TEST_SUITE(by_default)
		BOOST_AUTO_TEST_CASE(can_get_height)
		{
			BOOST_CHECK_EQUAL(image.GetHeight(), height);
		}
		BOOST_AUTO_TEST_CASE(can_get_width)
		{
			BOOST_CHECK_EQUAL(image.GetWidth(), width);
		}
	BOOST_AUTO_TEST_SUITE_END()
	struct AfterChangingImageSize_ : Image_
	{
		int newWidth = 500;
		int newHeight = 250;
		AfterChangingImageSize_()
		{
			image.Resize(newWidth, newHeight);
		}
	};
	BOOST_FIXTURE_TEST_SUITE(AfterChangingImageSize, AfterChangingImageSize_)
		BOOST_AUTO_TEST_CASE(has_new_size)
		{
			BOOST_CHECK(image.GetHeight() == newHeight);
			BOOST_CHECK(image.GetWidth() == newWidth);
		}
		BOOST_AUTO_TEST_CASE(can_undo)
		{
			BOOST_CHECK(history.CanUndo());
			history.Undo();
			BOOST_CHECK_EQUAL(image.GetHeight(), height);
			BOOST_CHECK_EQUAL(image.GetWidth(), width);
		}
		BOOST_AUTO_TEST_CASE(can_redo)
		{
			BOOST_CHECK(history.CanUndo());
			history.Undo();
			BOOST_CHECK_EQUAL(image.GetHeight(), height);
			BOOST_CHECK_EQUAL(image.GetWidth(), width);
			BOOST_CHECK(history.CanRedo());
			history.Redo();
			BOOST_CHECK_EQUAL(image.GetHeight(), newHeight);
			BOOST_CHECK_EQUAL(image.GetWidth(), newWidth);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()