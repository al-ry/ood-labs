#pragma once
#include "../graphics_lib/graphics_lib.h"
#include "../modern_graphics_lib/modern_graphics_lib.h"


class CModernGraphicsRendererObjectAdapter: public graphics_lib::ICanvas
{
public:
	CModernGraphicsRendererObjectAdapter(modern_graphics_lib::CModernGraphicsRenderer& renderer);
	
	void MoveTo(int x, int y) override;
	void LineTo(int x, int y) override;
	void SetColor(uint32_t rgbColor) override;
	void SetCapacity(float opacity);

private:
	modern_graphics_lib::CPoint m_fromPoint;
	modern_graphics_lib::CModernGraphicsRenderer& m_renderer;
	modern_graphics_lib::CRGBAColor m_color;
};