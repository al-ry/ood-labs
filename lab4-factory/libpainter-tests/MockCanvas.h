#pragma once
#include "stdafx.h"
#include "../libpainter/Color.h"
#include <boost\test\tools\output_test_stream.hpp>
class MockCanvas : public ICanvas
{
public:
	MockCanvas(boost::test_tools::output_test_stream& strm, Color color)
		: m_stream(strm)
		, m_color(color)
	{
	}
	void SetColor(Color color) override
	{
		m_color = color;
	}
	void DrawLine(const CPoint& from, const CPoint& to) override
	{
		from;
		to;
		m_stream << "DrawLine\n";
	}
	void DrawEllipse(const CPoint& center, double verticalRadius, double horizontalRadius) override
	{
		center;
		verticalRadius;
		horizontalRadius;
		m_stream << "DrawEllipse\n";
	}
	Color m_color;
	boost::test_tools::output_test_stream& m_stream;
};