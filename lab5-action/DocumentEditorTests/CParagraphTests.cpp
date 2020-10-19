#include "stdafx.h"
#include "../DocumentEditor/Paragraph.h"


struct Paragraph_
{
	std::string text = "paragraph";
	CParagraph paragraph;
	CHistory history;
	Paragraph_()
		: paragraph(text, history)
		, history()
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Test_CPragraph, Paragraph_)
	BOOST_AUTO_TEST_SUITE(by_default)
		BOOST_AUTO_TEST_CASE(can_obtain_paragraph_content)
		{
			BOOST_CHECK(paragraph.GetText() == "paragraph");
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
		BOOST_AUTO_TEST_CASE(can_undo)
		{
			BOOST_CHECK(paragraph.GetText() == textNew);
			BOOST_CHECK(history.CanUndo());
			history.Undo();
			BOOST_CHECK(paragraph.GetText() == "paragraph");
		}
		BOOST_AUTO_TEST_CASE(can_redo)
		{
			BOOST_CHECK(paragraph.GetText() == textNew);
			BOOST_CHECK(history.CanUndo());
			history.Undo();
			BOOST_CHECK(paragraph.GetText() == "paragraph");
			BOOST_CHECK(history.CanRedo());
			history.Redo();
			BOOST_CHECK_EQUAL(paragraph.GetText(), textNew);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()