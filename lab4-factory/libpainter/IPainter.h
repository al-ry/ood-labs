#pragma once
#include "../libpainter/PictureDraft.h"

class IPainter
{
public:
	IPainter() = default;
	virtual void DrawPicture(const CPictureDraft& draft, ICanvas& canvas) const = 0;

	virtual ~IPainter() = default;
};