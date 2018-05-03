#pragma once
#include "Math/Vector2.h"
#include <SFML/Window/Event.hpp>
#include "Math/Rectangle.h"

namespace OpenUI
{
	struct InputContext;
	class Element;

	struct InputHandler
	{
		struct MouseDropEvent
		{
			explicit MouseDropEvent ( Element& source, const IntVector& start, const IntVector& end )
				: Source ( source )
				, Start ( start )
				, End ( end )
			{
			}

			Element& Source;

			const IntVector Start;
			const IntVector End;
		};

		struct MouseDragDropEvent
		{
			explicit MouseDragDropEvent ( Element* target, const IntVector& start, const IntVector& end )
				: Target ( target )
				, Start ( start )
				, End ( end )
			{
			}

			Element* Target;

			const IntVector Start;
			const IntVector End;

			bool DidHitTarget() const
			{
				return Target;
			}
		};

		IntVector MousePosition { 0, 0 };
		InputHandler ();

		void Refresh ( sf::Event::MouseMoveEvent& event );

		bool IsMouseWithin ( Element* element ) const;

		template < typename _Ty >
		static bool IsMouseWithin ( IntRect& p_value, Vector2 <_Ty> point );

		void OnDragBegin ( Element* source );

		void OnMouseEnter ( Element* element );
		void OnMouseLeave ( Element* element );
		void OnMouseMove ( Element* element );

		void OnMouseDown ( Element* element, const sf::Event::MouseButtonEvent& event, const InputContext& inputContext );
		void OnMouseUp ( Element* element, const sf::Event::MouseButtonEvent& event, const InputContext& inputContext );

		void HandleInput ( Element* element, const sf::Event& event, const InputContext& inputContext );
		void UpdateActiveElement( Element* element );

	private:
		int m_consecutiveClicks;

		long m_lastMousePress;
		long m_lastMouseClick;

		IntVector m_lastPressMousePos;

		Element* m_activeElement;
		Element* m_pressedElement;

		Element* m_dragDropSource;
		Element* m_dragDropTarget;

		sf::Event m_event;
	};
}
