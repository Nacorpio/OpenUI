#pragma once
#include "Common/Enums.h"
#include <SFML/Graphics/Color.hpp>
#include "GraphicProperties.h"
#include "Entities/Elements/Element.h"

namespace OpenUI
{
	template < class _Ty >
	struct State
	{
		union
		{
			struct
			{
				_Ty Default, Disabled, Entered, Dragged, Pressed, Held;
			};

			_Ty Values[6];
		};

		State () = default;

		State ( _Ty all )
			: Default ( all )
			, Disabled ( all )
			, Entered ( all )
			, Dragged ( all )
			, Pressed ( all )
			, Held ( all )
		{
		}

		explicit State ( const State& other )
			: Values ( other.Values )
		{
		}

		explicit State ( State&& other ) noexcept
			: Values ( std::move ( other.Values ) )
		{
		}

		/* Gets a value indicating whether the state should be used. */
		bool IsEnabled = false;

		bool operator == ( const State& rhs )
		{
			for ( int i = 0 ; i < 6 ; ++i )
			{
				if ( Values[i] != rhs.Values[i] )
				{
					return false;
				}
			}

			return true;
		}
		bool operator != ( const State& rhs )
		{
			return !( *this == rhs );
		}

		State& operator= ( const State& rhs )
		{
			Values = rhs.Values;
			return this;
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
	typedef State <std::string> StringState;
	typedef State <Padding> PaddingState, MarginState;
	typedef State <IntVector> VectorState;

	struct Scheme
	{
		struct
		{
			ColorState BackColor;
			ColorState OutlineColor;
		} Colors;

		struct
		{
			ColorState Color;
			ColorState OutlineColor;

			IntState Style = sf::Text::Style::Regular;
			IntState OutlineThickness;

			BoolState ShowOutline = false;
			BoolState Visible = true;
		} Font;

		IntState OutlineThickness;

		PaddingState Padding;
		MarginState Margin;

		StringState Text;

		BoolState ShowOutline = false;
		BoolState Visible = true;

		void Init ( Element& element )
		{
			// Set the default state of the element.
		}

		void Update ( const ControlState state, Element& element )
		{
			// Set the corresponding state of the element.
		}
	};
}
