#pragma once
#include "Math/Rectangle.h"
#include <SFML/OpenGL.hpp>
#include "Common/Constants.h"

#define FLIP_COORDINATE_SYSTEM(rectangle,clientWindowHeight) (clientWindowHeight -rectangle.Y - rectangle.Height)

namespace OpenUI
{
	class ScissorTest
	{
	public:

		/// <summary>
		///		Enable the scissor test to the specified rectangle. Remember that OpenGL coordinate system starts at the lower-left and an conversion is required.
		/// </summary>
		static void SetScissorTest (IntRect & rect, uint16_t clientWindowHeight = 600)
		{
			if (rect.X < 0)
			{
				rect.X = 0;
			}

			if (rect.Y < 0)
			{
				rect.Y = 0;
			}

			if (rect.Width < 0)
			{
				rect.Width = 0;
			}

			if (rect.Height < 0)
			{
				rect.Height = 0;
			}

			glEnable(GL_SCISSOR_TEST);
			glScissor(rect.X, FLIP_COORDINATE_SYSTEM ( rect,clientWindowHeight ), rect.Width, rect.Height);
		}
	};

}

