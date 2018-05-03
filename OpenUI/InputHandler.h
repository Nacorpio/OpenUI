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

		//IntVector MousePosition { 0, 0 };
		InputHandler();

	//	void Refresh ( sf::Event::MouseMoveEvent& event );

		bool IsMouseWithin ( Element* element ) const;

		template < typename _Ty >
		static bool IsMouseWithin ( IntRect& p_value, Vector2 <_Ty> point );

		void OnDragBegin ( Element* source );

		void OnMouseEnter ( Element* element );
		void OnMouseLeave ( Element* element );
		void OnMouseMove ( Element* element);

		void OnMouseDown ( Element* element);
		void OnMouseUp ( Element* element);

		void HandleInput ( Element* element );

	private:
		void CalculateClick(Element * element);
		void CalculateTopMost(Element* element);

		int m_consecutiveClicks;

		long m_lastMousePressTime;
		long m_lastMouseClickTime;
		long m_lastMouseMoveTime;

		sf::Mouse::Button m_lastMousePress;
		sf::Mouse::Button m_lastMouseClick;

		IntVector m_lastMousePressPos;
		IntVector m_lastMouseClickPos;

		Element* m_top;
		Element* m_pressing;

		Element* m_lastClicked;
		Element* m_lastMoved;

		Element* m_dragDropSource;
		Element* m_dragDropTarget;

		sf::Event m_event;
	};
}
