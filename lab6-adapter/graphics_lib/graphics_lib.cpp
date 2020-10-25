// graphics_lib.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "graphics_lib.h"
#include <iomanip>


void graphics_lib::CCanvas::SetColor(uint32_t rgbColor)
{
	std::cout << "Color: 0x" << std::setfill('0') << std::setw(6) << std::hex << rgbColor << std::endl
	<< std::dec;
}

void graphics_lib::CCanvas::MoveTo(int x, int y)
{
	std::cout << "MoveTo (" << x << ", " << y << ")" << std::endl;
}

void graphics_lib::CCanvas::LineTo(int x, int y)
{
	std::cout << "LineTo (" << x << ", " << y << ")" << std::endl;
}
