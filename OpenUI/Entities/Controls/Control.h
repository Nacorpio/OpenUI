#pragma once

#include "Common/Enums.h"
#include <string>

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
			m_mouseState = p_state;
		}

		virtual void OnMouseEnter()
		{
		}

		virtual void OnMouseHover()
		{
		}
		virtual void OnMouseDown()
		{
		}

		virtual void OnMouseUp()
		{
		}

		virtual void OnMouseClick()
		{

		}

	private:
		MouseState m_mouseState = MouseState::None;
	};
}
