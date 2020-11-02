#pragma once

#include <memory>
#include <limits>
#include <stdint.h>
#include "IShape.h"

class IGroup : public IShape
{
public:
	virtual size_t GetShapesCount() const = 0;
	virtual IShapePtr GetShapeAtIndex(size_t index) const = 0;
	virtual void InsertShape(const IShapePtr& shape, size_t index = std::numeric_limits<size_t>::max()) = 0;
	virtual void RemoveShapeAtIndex(size_t index) = 0;

	virtual ~IGroup() = default;
};
