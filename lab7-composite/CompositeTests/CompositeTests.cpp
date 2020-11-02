#include "stdafx.h"
#include "../Composite/CGroup.h"
#include "../Composite/IShape.h"
#include "../Composite/CShape.h"
#include "../Composite/CEllipse.h"
#include "../Composite/CTriangle.h"
#include "../Composite/CRectangle.h"

class MockShapeGroup : public CGroup
{
public:
	MockShapeGroup(const std::string& str)
		: shape(str)
	{
	}
	std::string shape;
};

struct Group_
{
	IGroupPtr group = std::make_shared<CGroup>();
	IGroup& groupRef = *group.get();
};

BOOST_FIXTURE_TEST_SUITE(Group_tests, Group_)
	BOOST_AUTO_TEST_SUITE(by_default)
		BOOST_AUTO_TEST_CASE(has_zero_size)
		{
			BOOST_CHECK(group->GetShapesCount() == 0);
		}
		BOOST_AUTO_TEST_CASE(can_get_group)
		{
			auto groupPtr = group->GetGroup();
			BOOST_CHECK(groupPtr != nullptr);
			BOOST_CHECK_EQUAL(std::addressof(*groupPtr->GetGroup().get()), std::addressof(groupRef));
		}
		BOOST_AUTO_TEST_CASE(group_is_a_compound_shape)
		{
			IShapePtr shapePtr = std::make_shared<MockShapeGroup>("compound shape");
			auto asMockShape = dynamic_cast<const MockShapeGroup*>(shapePtr.get());
			BOOST_CHECK(asMockShape->shape == "compound shape");
		}
		BOOST_AUTO_TEST_CASE(can_insert_shape_at_the_end)
		{
			auto IShapePtr = std::make_shared<MockShapeGroup>("mock");
			group->InsertShape(IShapePtr);
			BOOST_CHECK(group->GetShapesCount() == 1);
		}
		BOOST_AUTO_TEST_CASE(cannot_get_frame)
		{
			BOOST_CHECK_THROW(group->GetFrame(), std::runtime_error);
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct when_insertin_shapes_to_group_ : Group_
	{
		when_insertin_shapes_to_group_()
		{
			group->InsertShape(std::make_shared<MockShapeGroup>("triangle"));
			group->InsertShape(std::make_shared<MockShapeGroup>("ellipse"));
			group->InsertShape(std::make_shared<MockShapeGroup>("circle"));
			group->InsertShape(std::make_shared<MockShapeGroup>("rectangle"));
		}
	};
	BOOST_FIXTURE_TEST_SUITE(when_insertin_shapes_to_group, when_insertin_shapes_to_group_)
		BOOST_AUTO_TEST_CASE(should_increase_size)
		{
			BOOST_CHECK(group->GetShapesCount() == 4);
		}		
		BOOST_AUTO_TEST_CASE(can_get_shape_from_any_postition)
		{
			auto shape1 = group->GetShapeAtIndex(0);
			auto triangle = dynamic_cast<const MockShapeGroup*>(shape1.get());
			BOOST_CHECK(triangle->shape == "triangle");
			auto shape2 = group->GetShapeAtIndex(1);
			auto ellipse = dynamic_cast<const MockShapeGroup*>(shape2.get());
			BOOST_CHECK(ellipse->shape == "ellipse");
			auto shape3 = group->GetShapeAtIndex(2);
			auto circle = dynamic_cast<const MockShapeGroup*>(shape3.get());
			BOOST_CHECK(circle->shape == "circle");
			auto shape4 = group->GetShapeAtIndex(3);
			auto rectangle = dynamic_cast<const MockShapeGroup*>(shape4.get());
			BOOST_CHECK(rectangle->shape == "rectangle");
		}
		BOOST_AUTO_TEST_CASE(cannot_get_shape_from_out_of_range_position)
		{
			BOOST_CHECK_THROW(group->GetShapeAtIndex(50), std::runtime_error);
		}
		BOOST_AUTO_TEST_CASE(can_erase_shape_from_specified_position)
		{
			size_t prevSize = group->GetShapesCount();
			group->RemoveShapeAtIndex(2);
			BOOST_CHECK(group->GetShapesCount() == --prevSize);
		}
		BOOST_AUTO_TEST_CASE(cannot_erase_shape_from_out_of_range_position)
		{
			BOOST_CHECK_THROW(group->RemoveShapeAtIndex(8), std::runtime_error);
		}


	BOOST_AUTO_TEST_SUITE_END()

	struct when_group_with_real_shapes_
	{
		IGroupPtr group = std::make_shared<CGroup>();

		IShapePtr ellipse = std::make_shared<CEllipse>(CPoint(3, 2), 2, 3);
		IShapePtr triangle = std::make_shared<CTriangle>(CPoint(0, 0), CPoint(3, 4), CPoint(3, 0));
		IShapePtr rectangle = std::make_shared<CRectangle>(CPoint(0,0), 5, 8);
		when_group_with_real_shapes_()
		{
			group->InsertShape(ellipse);
			group->InsertShape(triangle);
			group->InsertShape(rectangle);
		}
	};

	BOOST_FIXTURE_TEST_SUITE(when_group_with_real_shapes, when_group_with_real_shapes_)
		BOOST_AUTO_TEST_CASE(can_get_group_frame)
		{
			auto frame = group->GetFrame();
			RectD result = { 0, 0, 6, 8 };
			BOOST_CHECK_EQUAL(frame.left, result.left);
			BOOST_CHECK_EQUAL(frame.top, result.top);
			BOOST_CHECK_EQUAL(frame.width, result.width);
			BOOST_CHECK_EQUAL(frame.height, result.height);
		}

		BOOST_AUTO_TEST_SUITE(when_increase_frame_x2_and_offset_frame_to_X2_Y2)
			BOOST_AUTO_TEST_CASE(should_change_frame_of_all_shapes_x2)
			{
				group->SetFrame(RectD{ 2, 2, 12, 16 });
				auto ellipseFrame = group->GetShapeAtIndex(0)->GetFrame();
				BOOST_CHECK_EQUAL(ellipseFrame.left, 2);
				BOOST_CHECK_EQUAL(ellipseFrame.top, 2);
				BOOST_CHECK_EQUAL(ellipseFrame.width, 12);
				BOOST_CHECK_EQUAL(ellipseFrame.height, 8);	

				auto triangle = group->GetShapeAtIndex(1)->GetFrame();
				BOOST_CHECK_EQUAL(triangle.left, 2);
				BOOST_CHECK_EQUAL(triangle.top, 2);
				BOOST_CHECK_EQUAL(triangle.width, 6);
				BOOST_CHECK_EQUAL(ellipseFrame.height, 8);
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_CASE(has_white_compound_outline_color_by_default)
		{
			BOOST_CHECK(group->GetLineStyle()->GetColor() == RGBAColor(255,255,255,1));
			BOOST_CHECK(group->GetLineStyle()->GetLineWidth() == 1);
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_FIXTURE_TEST_SUITE(Test_OutlineStyle_for_group, when_group_with_real_shapes_)
		BOOST_AUTO_TEST_SUITE(after_setting_same_outline_color_)
			BOOST_AUTO_TEST_CASE(all_shapes_has_same_color)
			{
				group->GetLineStyle()->SetColor(RGBAColor(1, 2, 3, 4));
				auto color = group->GetLineStyle()->GetColor();
				BOOST_CHECK(color == RGBAColor(1, 2, 3, 4));
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(after_change_color_of_one_shape_of_group)
			BOOST_AUTO_TEST_CASE(get_color_should_return_nullopt)
			{
				group->GetShapeAtIndex(1)->GetLineStyle()->SetColor(RGBAColor(0, 0, 0, 0));
				auto color = group->GetLineStyle()->GetColor();
				BOOST_CHECK(color == std::nullopt);
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(after_turning_off_outline_color_of_one_shape)
			BOOST_AUTO_TEST_CASE(isEnabled_should_return_nullopt)
			{
				group->GetShapeAtIndex(1)->GetLineStyle()->Enable(false);
				auto isEnabled = group->GetLineStyle()->IsEnabled();
				BOOST_CHECK(isEnabled == std::nullopt);
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(after_chagning_line_width_of_one_shape)
			BOOST_AUTO_TEST_CASE(getLine_should_return_nullopt)
			{
				group->GetShapeAtIndex(1)->GetLineStyle()->SetLineWidth(8);
				auto width = group->GetLineStyle()->GetLineWidth();
				BOOST_CHECK(width == std::nullopt);
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(after_chagning_line_width_of_group)
			BOOST_AUTO_TEST_CASE(should_set_same_line_width_to_whole_shapes)
			{
				group->GetLineStyle()->SetLineWidth(20);
				auto width = group->GetShapeAtIndex(1)->GetLineStyle()->GetLineWidth();
				BOOST_CHECK(width == 20);
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(after_turning_off_outline_color_of_group)
			BOOST_AUTO_TEST_CASE(should_turn_off_outline_color_of_whole_shapes)
			{
				group->GetLineStyle()->Enable(false);
				auto isEnabled = group->GetShapeAtIndex(1)->GetLineStyle()->IsEnabled();
				BOOST_CHECK(isEnabled == false);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()

		BOOST_FIXTURE_TEST_SUITE(Test_fillColor_for_group, when_group_with_real_shapes_)
		BOOST_AUTO_TEST_SUITE(after_setting_same_fill_color_)
			BOOST_AUTO_TEST_CASE(all_shapes_has_same_color)
			{
				group->GetFillStyle()->SetColor(RGBAColor(1, 2, 3, 4));
				auto color = group->GetFillStyle()->GetColor();
				BOOST_CHECK(color == RGBAColor(1, 2, 3, 4));
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(after_change_color_of_one_shape_of_group)
			BOOST_AUTO_TEST_CASE(get_color_should_return_nullopt)
			{
				group->GetShapeAtIndex(0)->GetFillStyle()->SetColor(RGBAColor(4, 4, 4, 0));
				auto color = group->GetFillStyle()->GetColor();
				BOOST_CHECK(color == std::nullopt);
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(after_turning_off_fill_color_of_one_shape)
			BOOST_AUTO_TEST_CASE(isEnabled_should_return_nullopt)
			{
				group->GetShapeAtIndex(1)->GetFillStyle()->Enable(true);
				auto isEnabled = group->GetFillStyle()->IsEnabled();
 				BOOST_CHECK(isEnabled == std::nullopt);
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(after_turning_off_fill_color_of_group)
			BOOST_AUTO_TEST_CASE(should_turn_off_fill_color_of_whole_shapes)
			{
				group->GetFillStyle()->Enable(false);
				auto isEnabled = group->GetShapeAtIndex(1)->GetFillStyle()->IsEnabled();
				BOOST_CHECK(isEnabled == false);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()