#pragma once

#include <string>
#include "InputHandler.h"
#include "Common/Enums.h"

namespace OpenUI
{
	enum class MouseState;
	class Element;

	class Control

	{
	public:
		virtual ~Control () = default;
		explicit Control ( const std::string& name );

		ControlState GetState () const;

		bool IsBeingDragged () const { return HasState ( Dragged ); }
		bool IsBeingPressed () const { return HasState ( Pressed ); }
		bool IsBeingHovered () const { return HasState ( Hovered ); }

		bool IsCursorInside () const { return HasState ( Entered ); }
		bool HasFocus () const { return HasState ( Focused ); }

	protected:
		virtual void OnMouseEnter() = 0;
		virtual void OnMouseLeave () = 0;
		virtual void OnMouseHover () = 0;
		virtual void OnMouseMove () = 0;

		virtual void OnMouseDown () = 0;
		virtual void OnMouseUp () = 0;

		virtual void OnMouseClick () = 0;
		virtual void OnMouseDoubleClick () = 0;

		virtual void OnDragBegin () = 0;
		virtual void OnDragEnter ( Element* ) = 0;
		virtual void OnDragMove ( Element* ) = 0;

		virtual void OnDrop ( const InputHandler::MouseDropEvent& ) = 0;
		virtual void OnDragDrop ( const InputHandler::MouseDragDropEvent& ) = 0;

		virtual void OnStateChanged ( ControlState p_state ) = 0;

		friend struct InputHandler;

		void SetState ( ControlState state );
		void SetState ( int state );

		void AddState ( ControlState state );
		void RemoveState ( ControlState state );
		void ToggleState ( ControlState state );

		bool HasState ( ControlState state ) const;

	private:
		union
		{
			ControlState m_state;
			int m_st = None;
		};
	};
}
