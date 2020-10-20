#include "stdafx.h"
#include "../DocumentEditor/Image.h"
#include "MockAdapter.h"
struct Image_
{
	std::stringstream ss;
	std::unique_ptr<MockAdapter> adapter = std::make_unique<MockAdapter>(ss);
	int width = 400;
	int height = 200;
	Path path = Path("../DocumentEditorTests/test_img/boost.png");
	CImage image;
	Image_()
		: image(path, width, height, std::move(adapter))
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
		BOOST_AUTO_TEST_CASE(delegates_adding_command_to_adapter)
		{
			BOOST_CHECK(ss.str() == "Command Added\n");
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()