#pragma once
#include "Math/Rectangle.h"
#include <SFML/OpenGL.hpp>
#include "Common/Constants.h"

#define FLIP_COORDINATE_SYSTEM(value) (ClientWindowHeight -value.Y - value.Height)

namespace OpenUI
{
	struct ScissorTest
	{

		// The scissor rectangle that will be used when enabling the scissor test.
		IntRect ScissorRectangle;

		// The height of the scissor test's residing client window, used for converting from the OpenGl coordinate system(Bottom-left) to the sane one(Top-Left).
		uint16_t ClientWindowHeight = 600;

		// The scissor rectangle of the parent, used when restoring the scissor rectangle after all the children of the elements are finished drawing.
		IntRect ParentScissorTest;

		/// <summary>
		///		Sets the scissor test.
		/// </summary>
		void SetScissorTest ()
		{
			EnableScissorTest ( ScissorRectangle );
		}

		/// <summary>
		///		Updates the scissor rectangle to a new one.
		/// </summary>
		/// <param name="p_value">The rectangle</param>
		void UpdateScissorRectangle ( IntRect& p_value )
		{
			ScissorRectangle = p_value;
		}

		/// <summary>
		///		Restores the previous scissor test rectangle that was used before this one.
		/// </summary>
		void RestoreParentsScissorTest ()
		{
			EnableScissorTest(ParentScissorTest);
		}

	private:
		/// <summary>
		///		Enable the scissor test to the specified rectangle. Remember that OpenGL coordinate system starts at the lower-left and an conversion is required.
		/// </summary>
		/// <param name="p_rect">The specified rectangle to set the scissor test to.</param>
		void EnableScissorTest ( IntRect& p_rect ) const
		{
			if(p_rect.X < 0)
			{
				p_rect.X = 0;
			}

			if(p_rect.Y < 0)
			{
				p_rect.Y = 0;
			}

			if(p_rect.Width < 0 )
			{
				p_rect.Width = 0;
			}

			if (p_rect.Height < 0)
			{
				p_rect.Height = 0;
			}

			glEnable ( GL_SCISSOR_TEST );
			glScissor ( p_rect.X, FLIP_COORDINATE_SYSTEM(p_rect), p_rect.Width, p_rect.Height );
		}
	};

}

