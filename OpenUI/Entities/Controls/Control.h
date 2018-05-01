#pragma once

#include <string>
#include <SFML/Window/Event.hpp>
#include "InputContext.h"

namespace OpenUI
{
	enum class MouseState;
	class Element;

	class Control
	{
	public:
		enum ControlState
		{
			None = 1 << 0,
			Entered = 1 << 1,
			Hovered = 1 << 2,
			Pressed = 1 << 3,
			Dragged = 1 << 4,
		};

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

		virtual void OnMouseDown ( const sf::Event::MouseButtonEvent& event );
		virtual void OnMouseUp(const sf::Event::MouseButtonEvent& event);

		virtual void OnMouseClick (const sf::Event::MouseButtonEvent& event );

		virtual void OnDragBegin ();
		virtual void OnDragEnter ( Element* );
		virtual void OnDragMove ( Element* );

		virtual void OnDrop ( const InputContext::MouseDropEvent& );
		virtual void OnDragDrop ( const InputContext::MouseDragDropEvent& );

		virtual void OnStateChanged(MouseState p_state) {}

	private:
		friend struct InputContext;

		void SetState(ControlState state);
		void SetState(const int state) { SetState((ControlState)state); }

		void AddState(const ControlState state) { SetState(m_st | state); }
		void RemoveState(const ControlState state) { SetState(m_st & ~state); }
		void ToggleState(const ControlState state) { SetState(m_st ^ state); }

		union
		{
			ControlState m_state;
			int m_st = None;
		};
	};
}
