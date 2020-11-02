#pragma once
#include "../modern_graphics_lib/modern_graphics_lib.h"
#include "../graphics_lib/graphics_lib.h"


class ModernGraphicsRendererClassAdapter : public graphics_lib::ICanvas, public modern_graphics_lib::CModernGraphicsRenderer
{
public:
	ModernGraphicsRendererClassAdapter(std::ostream& strm);
	void MoveTo(int x, int y) override;
	void LineTo(int x, int y) override;
	void SetColor(uint32_t rgbColor) override;

private:
	modern_graphics_lib::CPoint m_fromPoint;
	modern_graphics_lib::CRGBAColor m_color;
};