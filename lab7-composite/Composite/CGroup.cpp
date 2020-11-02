#include "CGroup.h"
#include <stdexcept>
#include "CCompoundOutlineStyle.h"
#include "CCompoundFillStyle.h"

CGroup::CGroup()
{
	OutlineStyleEnumerator outlineEnumerator = [this](std::function<void(IOutlineStyle&)> callback) {
		for (auto& shape : m_group)
		{
			callback(*shape->GetLineStyle());
		}
	};
	m_outlineColor = std::make_unique<CCompoundOutlineStyle>(outlineEnumerator);

	FillStyleEnumerator fillEnumerator = [this](std::function<void(IStyle&)> callback) {
		for (auto& shape : m_group)
		{
			callback(*shape->GetFillStyle());
		}
	};
	m_fillColor = std::make_unique<CCompoundFillStyle>(fillEnumerator);
}
RectD CGroup::GetFrame() const
{
	if (m_group.empty())
	{
		throw std::runtime_error("Cannot get frame from empty group");
	}
	RectD newFrame{
		std::numeric_limits<double>::infinity(),
		std::numeric_limits<double>::infinity(),
		-std::numeric_limits<double>::infinity(),
		-std::numeric_limits<double>::infinity()
	};

	for (const auto& shape : m_group)
	{
		auto shapeFrame = shape->GetFrame();
		newFrame.left = std::min(newFrame.left, shapeFrame.left);
		newFrame.top = std::min(newFrame.top, shapeFrame.top);
		newFrame.height = std::max(newFrame.height, shapeFrame.height); 
		newFrame.width = std::max(newFrame.width, shapeFrame.width);
	}
	newFrame.width = newFrame.width - newFrame.left;
	newFrame.height = newFrame.height - newFrame.top;

	return newFrame;
}

void CGroup::SetFrame(const RectD& frame)
{
	auto oldFrame = GetFrame();
	for (auto& shape: m_group)
	{
		auto shapeFrame = shape->GetFrame();
		double left = frame.left + (shapeFrame.left - oldFrame.left) / oldFrame.width * frame.width;
		double top  = frame.top + (shapeFrame.top - oldFrame.top) / oldFrame.height * frame.height;
		double width = (shapeFrame.width * frame.width) / oldFrame.width;
		double height = (shapeFrame.height * frame.height) / oldFrame.height;
		shape->SetFrame(RectD{left, top, width, height});
	}
}

OutlineStylePtr CGroup::GetLineStyle() const
{
	return m_outlineColor;
}


StylePtr CGroup::GetFillStyle() const
{
	return m_fillColor;
}

void CGroup::Draw(ICanvas& canvas) const
{
	for (const auto &shape :m_group)
	{
		shape->Draw(canvas);
	}
}

IGroupPtr CGroup::GetGroup()
{
	return shared_from_this();
}

size_t CGroup::GetShapesCount() const
{
	return m_group.size();
}

IShapePtr CGroup::GetShapeAtIndex(size_t index) const
{
	if (index >= m_group.size())
	{
		throw std::runtime_error("Index is out of range.");
	}
	return m_group.at(index);
}

void CGroup::InsertShape(const IShapePtr& shape, size_t index)
{
	if (index > m_group.size())
	{
		m_group.push_back(shape);
	}
	else
	{
		m_group.insert(m_group.begin() + index, shape);
	}
}

void CGroup::RemoveShapeAtIndex(size_t index)
{
	if (index >= m_group.size())
	{
		throw std::runtime_error("Index is out of range.");
	}
	m_group.erase(m_group.begin()+ index);
}
