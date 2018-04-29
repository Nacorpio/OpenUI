#pragma once

#include "Common/Enums.h"
#include <string>
#include "Common/Constants.h"
#include <iostream>

namespace OpenUI
{
	class Control
	{
	public:
		virtual ~Control () = default;

		explicit Control ( const std::string& name );

		//void Initialize () override;
		//void Update () override;
		//void Draw ( const GraphicsContext& gContext ) override;

		MouseState GetState() const
		{
			return m_mouseState;
		}

		void SetState(MouseState p_state)
		{
			if(p_state == m_mouseState)
			{
				return;
			}

			LOG(p_state);
			m_mouseState = p_state;
		}

		virtual void OnMouseEnter()
		{
			SetState (MouseState::Entered);
		}

		virtual void OnMouseLeave()
		{
			SetState(MouseState::None);
		}

		virtual void OnMouseHover()
		{
			SetState(MouseState::Hovered);
		}

		virtual void OnMouseMove()
		{
			SetState(MouseState::Moved);
		}

		virtual void OnMouseDown()
		{
			SetState(MouseState::Pressed);
		}

		virtual void OnMouseUp()
		{
			SetState(MouseState::Released);
		}

		virtual void OnMouseClick()
		{
			SetState(MouseState::Clicked);
		}

	private:
		MouseState m_mouseState;
	};
}
