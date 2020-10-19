#include "stdafx.h"
#include "../DocumentEditor/Document.h"

struct Document_
{
	CDocument document;
};

BOOST_FIXTURE_TEST_SUITE(Test_CDocument, Document_)
	BOOST_AUTO_TEST_SUITE(by_default)
		BOOST_AUTO_TEST_CASE(has_empty_title)
		{
			BOOST_CHECK(document.GetTitle() == "");
		}
		BOOST_AUTO_TEST_CASE(cant_redo)
		{
			BOOST_CHECK(!document.CanRedo());
		}
		BOOST_AUTO_TEST_CASE(cant_undo)
		{
			BOOST_CHECK(!document.CanUndo());
		}
		BOOST_AUTO_TEST_CASE(has_0_items)
		{
			BOOST_CHECK(document.GetItemsCount() == 0);
		}
		BOOST_AUTO_TEST_CASE(cant_get_item_from_empty_document)
		{
			BOOST_CHECK_THROW(document.GetItem(0), std::runtime_error);
		}
		BOOST_AUTO_TEST_CASE(cant_insert_item_to_inaccessible_position)
		{
			BOOST_CHECK_THROW(document.InsertParagraph("cant insert", 200), std::runtime_error);
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct AfterSettingTitle_: Document_
	{
		std::string title = "index";
		AfterSettingTitle_()
		{	
			document.SetTitle(title);
		}
	};
	BOOST_FIXTURE_TEST_SUITE(Title_tests, AfterSettingTitle_)
		BOOST_AUTO_TEST_SUITE(when_change_title)
			BOOST_AUTO_TEST_CASE(can_get_new_title)
			{
				BOOST_CHECK(document.GetTitle() == title);
			}
			BOOST_AUTO_TEST_CASE(can_undo)
			{
				BOOST_CHECK(document.CanUndo());
				document.Undo();
				BOOST_CHECK(document.GetTitle() == "");
			}
			BOOST_AUTO_TEST_CASE(can_redo_after_undo)
			{
				BOOST_CHECK(document.CanUndo());
				document.Undo();
				BOOST_CHECK(document.CanRedo());
				document.Redo();
				BOOST_CHECK(document.GetTitle() == "index");
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()

	struct  AfterInsertingParagraph_: Document_
	{
		std::string text = "text";
		AfterInsertingParagraph_()
		{
			document.InsertParagraph(text);
		};
	};
	BOOST_AUTO_TEST_SUITE(Test_InsertParagraph_command)
		BOOST_AUTO_TEST_SUITE(when_inserting_from_invalid_position)
			BOOST_AUTO_TEST_CASE(should_throw_exception)
			{
				BOOST_CHECK_THROW(document.InsertParagraph("invalid", 500), std::runtime_error);
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_FIXTURE_TEST_SUITE(After_insering_pararaph, AfterInsertingParagraph_)
			BOOST_AUTO_TEST_CASE(should_increase_size)
			{
				BOOST_CHECK(document.GetItemsCount() == 1);
			}
			BOOST_AUTO_TEST_CASE(can_get_paragraph)
			{
				auto item = document.GetItem(0);
				BOOST_CHECK(item.GetParagraph()->GetText() == text);
			}
			BOOST_AUTO_TEST_CASE(can_undo_inserted_paragraph)
			{
				BOOST_CHECK(document.CanUndo());
				document.Undo();
				BOOST_CHECK(document.GetItemsCount() == 0);
				BOOST_CHECK_THROW(document.GetItem(0), std::runtime_error);			
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()

	struct AfterInsertingImage_ : Document_
	{
		Path path = Path("../DocumentEditorTests/test_img/boost.png");
		int width = 200;
		int height = 100;
		AfterInsertingImage_()
		{
			document.InsertImage(path, width, height);
		};
	};
	BOOST_AUTO_TEST_SUITE(Test_InsertImage_command)
		BOOST_FIXTURE_TEST_SUITE(After_insering_image, AfterInsertingImage_)
			BOOST_AUTO_TEST_CASE(should_increase_size)
			{
				BOOST_CHECK(document.GetItemsCount() == 1);
			}
			BOOST_AUTO_TEST_CASE(can_get_image)
			{
				auto item = document.GetItem(0);
				BOOST_CHECK(item.GetImage()->GetHeight() == height);
				BOOST_CHECK(item.GetImage()->GetWidth() == width);

			}
			BOOST_AUTO_TEST_CASE(can_undo_inserted_image)
			{
				BOOST_CHECK(document.CanUndo());
				document.Undo();
				BOOST_CHECK(document.GetItemsCount() == 0);
				BOOST_CHECK_THROW(document.GetItem(0), std::runtime_error);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()

	struct AfterInsertingFewItems_ : Document_
	{
		Path path = Path("../DocumentEditorTests/test_img/boost.png");
		IParagraphPtr p1 = document.InsertParagraph("text1");
		IParagraph& p1Ref = *p1;
		IImagePtr im1 = document.InsertImage(path, 200, 300, 0);
		IImage& im1Ref = *im1;
		IParagraphPtr p2 = document.InsertParagraph("text2", 1);
		IParagraph& p2Ref = *p2;
		AfterInsertingFewItems_()
		{
		};
	};

	BOOST_FIXTURE_TEST_SUITE(AfterInsertingFewItems, AfterInsertingFewItems_)
		BOOST_AUTO_TEST_CASE(stored_in_appropiate_order)
		{
			BOOST_CHECK(std::addressof(*document.GetItem(0).GetImage()) == std::addressof(im1Ref));
			BOOST_CHECK(std::addressof(*document.GetItem(1).GetParagraph()) == std::addressof(p2Ref));
			BOOST_CHECK(std::addressof(*document.GetItem(2).GetParagraph()) == std::addressof(p1Ref));
		}
		BOOST_AUTO_TEST_CASE(can_undo)
		{
			BOOST_CHECK(document.CanUndo());
			document.Undo();
			BOOST_CHECK(document.GetItem(0).GetImage()->GetHeight() == 300);
			BOOST_CHECK(std::addressof(*document.GetItem(1).GetParagraph()) == std::addressof(p1Ref));
			document.Undo();
			BOOST_CHECK(std::addressof(*document.GetItem(0).GetParagraph()) == std::addressof(p1Ref));
			BOOST_CHECK_THROW(document.GetItem(1).GetParagraph()->GetText(), std::runtime_error);
		}
		BOOST_AUTO_TEST_CASE(can_redo)
		{
			BOOST_CHECK(document.CanUndo());
			document.Undo();
			BOOST_CHECK(std::addressof(*document.GetItem(0).GetImage()) == std::addressof(im1Ref));
			BOOST_CHECK(std::addressof(*document.GetItem(1).GetParagraph()) == std::addressof(p1Ref));
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct After2Undo_ : AfterInsertingFewItems_
	{
		After2Undo_()
		{
			document.Undo();
			document.Undo();
		};
	};
	BOOST_FIXTURE_TEST_SUITE(After2Undo, After2Undo_)
		BOOST_AUTO_TEST_CASE(can_redo)
		{
			BOOST_CHECK(document.GetItemsCount() == 1);
			document.Redo();
			BOOST_CHECK(document.GetItemsCount() == 2);
			BOOST_CHECK(std::addressof(*document.GetItem(0).GetImage()) == std::addressof(im1Ref));
			BOOST_CHECK(std::addressof(*document.GetItem(1).GetParagraph()) == std::addressof(p1Ref));
			document.Redo();
			BOOST_CHECK(document.GetItemsCount() == 3);
			BOOST_CHECK(std::addressof(*document.GetItem(2).GetParagraph()) == std::addressof(p1Ref));
		}
		BOOST_AUTO_TEST_SUITE(when_insert_new_items)
			BOOST_AUTO_TEST_CASE(should_delete_2_previous_command_from_history)
			{
				IParagraphPtr newP = document.InsertParagraph("new");
				IParagraph& newPRef = *newP;
				BOOST_CHECK(std::addressof(*document.GetItem(1).GetParagraph()) == std::addressof(newPRef));
				BOOST_CHECK(document.CanUndo());
				document.Undo();
				document.Undo();
				BOOST_CHECK(!document.CanUndo());
				document.Redo();
				BOOST_CHECK(std::addressof(*document.GetItem(0).GetParagraph()) == std::addressof(p1Ref));
				document.Redo();
				BOOST_CHECK(std::addressof(*document.GetItem(1).GetParagraph()) == std::addressof(newPRef));
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Test_DeleteItem_command)

		struct AfterDeletingItemFromBack_ : AfterInsertingFewItems_
		{
			AfterDeletingItemFromBack_()
			{
				document.DeleteItem(2);
			}
		};
		BOOST_AUTO_TEST_SUITE(when_delete_from_out_of_range_index)
			BOOST_AUTO_TEST_CASE(should_throw_exception)
			{
				BOOST_CHECK_THROW(document.DeleteItem(500), std::runtime_error);
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_FIXTURE_TEST_SUITE(AfterDeletingItemFromBack, AfterDeletingItemFromBack_)
			BOOST_AUTO_TEST_CASE(should_decrease_items_size)
			{
				BOOST_CHECK(document.GetItemsCount() == 2);
				BOOST_CHECK_THROW(document.GetItem(2), std::runtime_error);
			}
			BOOST_AUTO_TEST_SUITE(when_undo)
				BOOST_AUTO_TEST_CASE(should_return_size_and_item_back)
				{
					BOOST_CHECK(document.CanUndo());
					document.Undo();
					BOOST_CHECK_EQUAL(document.GetItemsCount(), 3);
					BOOST_CHECK(std::addressof(*document.GetItem(2).GetParagraph()) == std::addressof(p1Ref));
				}
			BOOST_AUTO_TEST_SUITE_END()
			BOOST_AUTO_TEST_SUITE(when_redo)
				BOOST_AUTO_TEST_CASE(should_delete_item_again)
				{
					document.Undo();
					document.Redo();
					BOOST_CHECK(document.GetItemsCount() == 2);
					BOOST_CHECK_THROW(document.GetItem(2), std::runtime_error);
				}
			BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE_END() 

		struct AfterDeletingItemFromBegin_ : AfterInsertingFewItems_
		{
			AfterDeletingItemFromBegin_()
			{
				document.DeleteItem(0);
			}
		};
		BOOST_FIXTURE_TEST_SUITE(AfterDeletingItemFromBegin, AfterDeletingItemFromBegin_)
			BOOST_AUTO_TEST_CASE(should_decrease_items_size)
			{
				BOOST_CHECK(document.GetItemsCount() == 2);
				BOOST_CHECK(std::addressof(*document.GetItem(0).GetImage()) != std::addressof(im1Ref));
			}
			BOOST_AUTO_TEST_SUITE(when_undo)
				BOOST_AUTO_TEST_CASE(should_return_size_and_item_back)
				{
					BOOST_CHECK(document.CanUndo());
					document.Undo();
					BOOST_CHECK(std::addressof(*document.GetItem(0).GetImage()) == std::addressof(im1Ref));
					BOOST_CHECK_EQUAL(document.GetItemsCount(), 3);
				}
			BOOST_AUTO_TEST_SUITE_END()
			BOOST_AUTO_TEST_SUITE(when_redo)
				BOOST_AUTO_TEST_CASE(should_delete_item_again)
				{
					document.Undo();
					document.Redo();
					BOOST_CHECK(document.GetItemsCount() == 2);
					BOOST_CHECK_THROW(document.GetItem(2), std::runtime_error);
				}
			BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE_END() 
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()