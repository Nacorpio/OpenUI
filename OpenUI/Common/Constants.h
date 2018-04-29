#pragma once
#include <string>  // string
#include "Math/Vector2.h"

namespace OpenUI
{
	static std::string const GLOBAL_WINDOW_TITLE = "OpenUI";
	static bool GLOBAL_DRAW_SCISSOR_BOUNDS = false;
	static bool GLOBAL_DRAW_ELEMENT_BOUNDS = false;
	static UIntVector GLOBAL_RENDER_WINDOW_SIZE = UIntVector ( 600, 600 );

#define LOG(arg) std::cout  << "[LOG] " << __FUNCTION__ << ":" << std::endl << "  - " << arg << std::endl
}
