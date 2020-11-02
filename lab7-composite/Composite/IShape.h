#pragma once
#include "ICanvas.h"
#include "CFrame.h"
#include "IOutlineStyle.h"
#include <memory>
#include "IDrawable.h"

class IGroup;
typedef std::shared_ptr<IGroup> IGroupPtr;

class IShape: public IDrawable
{
public:
	virtual RectD GetFrame() const = 0;
	virtual void SetFrame(const RectD &frame) = 0;

	virtual OutlineStylePtr GetLineStyle() const = 0;

	virtual StylePtr GetFillStyle() const = 0;

	virtual IGroupPtr GetGroup() = 0;

};

typedef std::shared_ptr<IShape> IShapePtr;
