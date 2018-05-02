#pragma once
#include "Math/Rectangle.h"
#include <SFML/OpenGL.hpp>
#include "Common/Constants.h"

namespace OpenUI
{
	struct ScissorTest
	{
		#define FlipCoordinateSystem(value) (ClientWindowHeight -value.Y - value.Height)

		// The scissor rectangle that will be used when enabling the scissor test.
		IntRect ScissorRectangle;

		// The height of the scissor test's residing client window, used for converting from the OpenGl coordinate system(Bottom-left) to the sane one(Top-Left).
		uint16_t ClientWindowHeight = 600;

		// If true, a scissor test will be enabled.
		bool Enabled = false;

		// If true, this scissor test will check what scissor the previous enabled scissor test was and resizes it accordingly. 
		bool CheckIntersection = true;

		/// <summary>
		///		Sets the scissor test.
		/// </summary>
		void SetScissorTest ()
		{
			if ( !Enabled )
			{
				return;
			}

			// TODO: Cache this down the hierarchy
			m_scissorTestWasEnabled = glIsEnabled ( GL_SCISSOR_TEST );
			if ( CheckIntersection && m_scissorTestWasEnabled )
			{
				ResizeToFit ();
			}

			EnableScissorTest ( ScissorRectangle );
			CheckIntersection = false;
		}

		/// <summary>
		///		Updates the scissor rectangle to a new one.
		/// </summary>
		/// <param name="p_value">The rectangle</param>
		void UpdateScissorRectangle ( IntRect& p_value )
		{
			ScissorRectangle = p_value;
			CheckIntersection = true;
		}

		/// <summary>
		///		Restores the previous scissor test rectangle that was used before this one.
		/// </summary>
		void RestorePreviousScissorTest ()
		{
			if ( !m_scissorTestWasEnabled )
			{
				return; // No scissor test was enabled before this one.
			}

			EnableScissorTest ( m_previousRectangle );
		}

	private:
		IntRect m_previousRectangle;
		bool m_scissorTestWasEnabled = true;

		/// <summary>
		///		Resizes the scissor rectangle to fit the previous set rectangle.
		/// </summary>
		void ResizeToFit ()
		{
			glGetIntegerv ( GL_SCISSOR_BOX, m_previousRectangle.Array ); // Retrieves the previous scissor tests rectangle.
			m_previousRectangle.Y = FlipCoordinateSystem ( m_previousRectangle );

			ScissorRectangle.ResizeToFit ( m_previousRectangle );
		}

		/// <summary>
		///		Enable the scissor test to the specified rectangle. Remember that OpenGL coordinate system starts at the lower-left and an conversion is required.
		/// </summary>
		/// <param name="p_rect">The specified rectangle to set the scissor test to.</param>
		void EnableScissorTest ( IntRect& p_rect ) const
		{
			glEnable ( GL_SCISSOR_TEST );
			glScissor ( p_rect.X, FlipCoordinateSystem(p_rect), p_rect.Width, p_rect.Height );
		}
	};
}
