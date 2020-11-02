#pragma once
#include "IGroup.h"
#include <vector>
class CGroup
	: public IGroup
	, public std::enable_shared_from_this<IGroup>
{
public:
	CGroup();

	RectD GetFrame() const override;
	void SetFrame(const RectD& frame) override;

	OutlineStylePtr GetLineStyle() const override;

	StylePtr GetFillStyle() const override;

	void Draw(ICanvas& canvas) const override;

	IGroupPtr GetGroup() override;

	size_t GetShapesCount() const override;
	IShapePtr GetShapeAtIndex(size_t index) const override;
	void InsertShape(const IShapePtr& shape, size_t index = std::numeric_limits<size_t>::max()) override;
	void RemoveShapeAtIndex(size_t index) override;

private:
	std::vector<IShapePtr> m_group;
	
	OutlineStylePtr m_outlineColor;
	StylePtr m_fillColor;
};