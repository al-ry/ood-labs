#include "stdafx.h"
#include "../DocumentEditor/Paragraph.h"
#include "MockAdapter.h"

struct Paragraph_
{
	std::stringstream ss;
	std::unique_ptr<MockAdapter> adapter = std::make_unique<MockAdapter>(ss);
	CParagraph paragraph = CParagraph("paragraph", std::move(adapter));
};

BOOST_FIXTURE_TEST_SUITE(Test_CPragraph, Paragraph_)
	BOOST_AUTO_TEST_SUITE(by_default)
		BOOST_AUTO_TEST_CASE(can_obtain_paragraph_content)
		{
			BOOST_CHECK_EQUAL(paragraph.GetText(), "paragraph");
		}
	BOOST_AUTO_TEST_SUITE_END()
	struct AfterChangingText_ : Paragraph_
	{
		std::string textNew = "new paragraph";
		AfterChangingText_()
		{
			paragraph.SetText(textNew);
		}

	};
	BOOST_FIXTURE_TEST_SUITE(AfterChangingText, AfterChangingText_)

		BOOST_AUTO_TEST_CASE(delegates_adding_command_to_adapter)
		{
			BOOST_CHECK(ss.str() == "Command Added\n");
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()