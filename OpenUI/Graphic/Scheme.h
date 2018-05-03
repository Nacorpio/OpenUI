#pragma once
#include "Common/Enums.h"
#include <SFML/Graphics/Color.hpp>
#include "GraphicProperties.h"
#include "Math/Vector2.h"
#include <SFML/Graphics/Text.hpp>

namespace OpenUI
{
	template < class _Ty >
	struct State
	{
		_Ty Default, Disabled, Entered, Dragged, Pressed, Held, Hovered;

		State () = default;

		State ( _Ty all )
			: Default ( all )
			, Disabled ( all )
			, Entered ( all )
			, Dragged ( all )
			, Pressed ( all )
			, Held ( all )
			, Hovered ( all )
		{
		}

		/* Gets a value indicating whether the state should be used. */
		bool IsEnabled = false;

		bool operator == ( const State& rhs )
		{
			return Default == rhs.Default && Disabled == rhs.Disabled && Entered == rhs.Entered && Dragged == rhs.Dragged &&
					Pressed == rhs.Pressed && Held == rhs.Held && Hovered == rhs.Hovered;
		}

		bool operator != ( const State& rhs )
		{
			return !( *this == rhs );
		}

		State <_Ty>& operator= ( const State <_Ty>& rhs )
		{
			Default = rhs.Default;
			Disabled = rhs.Disabled;
			Entered = rhs.Entered;
			Dragged = rhs.Dragged;
			Pressed = rhs.Pressed;
			Held = rhs.Held;
			Hovered = rhs.Hovered;

			return *this;
		}

		static State <_Ty> CreateDefault ();
	};

	template < class _Ty >
	State <_Ty> State <_Ty>::CreateDefault ()
	{
		static _Ty Default;
		return State <_Ty> ( Default );
	}

	typedef State <sf::Color> ColorState;
	typedef State <int> IntState;
	typedef State <bool> BoolState;
	typedef State <Padding> PaddingState, MarginState;
	typedef State <IntVector> VectorState;

	class Element;

	struct Scheme
	{
		struct
		{
			ColorState BackColor = sf::Color::White;
			ColorState OutlineColor = sf::Color::Black;;
		} Colors;

		struct
		{
			ColorState Color = sf::Color::Black;
			ColorState OutlineColor = sf::Color::White;

			IntState Style = sf::Text::Style::Regular;
			IntState OutlineThickness;

			BoolState ShowOutline = false;
			BoolState Visible = true;
		} Font;

		IntState OutlineThickness;

		PaddingState Padding;
		MarginState Margin;

		BoolState ShowOutline = false;
		BoolState Visible = true;

		explicit Scheme ()
		{
			Colors.BackColor = ColorState::CreateDefault ();
			Colors.OutlineColor = ColorState::CreateDefault ();

			Padding = PaddingState::CreateDefault ();
			Margin = MarginState::CreateDefault ();
		}

		void Init ( Element& element );
		void Update ( ControlState state, Element& element );
	};
}
