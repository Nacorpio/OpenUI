#pragma once

#include <string>
#include <SFML/Window/Event.hpp>
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

		bool IsBeingDragged () const { return m_st & Dragged; }
		bool IsCursorInside () const { return m_st & Entered; }
		bool IsBeingPressed () const { return m_st & Pressed; }
		bool IsBeingHovered () const { return m_st & Hovered; }

	protected:
		virtual void OnMouseEnter ();
		virtual void OnMouseLeave ();
		virtual void OnMouseHover ();
		virtual void OnMouseMove ();

		virtual void OnMouseDown ( );
		virtual void OnMouseUp();

		virtual void OnMouseClick ();

		virtual void OnDragBegin ();
		virtual void OnDragEnter ( Element* );
		virtual void OnDragMove ( Element* );

		virtual void OnDrop ( const InputHandler::MouseDropEvent& );
		virtual void OnDragDrop ( const InputHandler::MouseDragDropEvent& );

		virtual void OnStateChanged(const ControlState p_state) {}

	private:
		friend struct InputHandler;

		void SetState ( ControlState state );
		void SetState ( int state );

		void AddState ( ControlState state );
		void RemoveState ( ControlState state );
		void ToggleState ( ControlState state );

		union
		{
			ControlState m_state;
			int m_st = None;
		};
	};
}
