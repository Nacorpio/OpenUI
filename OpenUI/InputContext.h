#pragma once
#include "Math/Vector2.h"
#include <SFML/Window/Event.hpp>
#include "Math/Rectangle.h"

namespace OpenUI
{
	class Element;

	struct InputContext
	{
		struct MouseDropEvent
		{
			explicit MouseDropEvent ( const Element& source )
				: Source ( source )
			{
			}

			const Element& Source;
		};

		struct MouseDragDropEvent
		{
			explicit MouseDragDropEvent ( const Element& target )
				: Target ( target )
			{
			}

			const Element& Target;
		};

		IntVector MousePosition { 0, 0 };
		InputContext ();

		void Refresh ( sf::Event::MouseMoveEvent& event );

		bool IsMouseWithin ( Element* element ) const;

		template < typename _Ty >
		static bool IsMouseWithin ( IntRect& p_value, Vector2 <_Ty> point );

		void OnDragBegin ( Element* source );

		void OnMouseEnter ( Element* element );
		void OnMouseLeave ( Element* element );
		void OnMouseMove ( Element* element );

		void OnMouseDown ( Element* element, const sf::Event::MouseButtonEvent& event, long delta );
		void OnMouseUp ( Element* element, const sf::Event::MouseButtonEvent& event, long delta );

		void HandleElementEvent ( Element* element, const sf::Event& event, long delta );

	private:
		Element* m_activeElement;
		Element* m_pressedElement;

		Element* m_dragDropSource;
		Element* m_dragDropTarget;

		sf::Event m_event;
	};
}
