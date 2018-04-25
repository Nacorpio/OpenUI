#pragma once
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <type_traits>

namespace OpenUI
{
	template < class _Ty, typename = std::enable_if_t <std::is_integral_v <_Ty>, _Ty> >
	struct Vector2
	{
		_Ty X = 0;
		_Ty Y = 0;

		Vector2() = default;

		Vector2 ( const _Ty p_x, const _Ty p_y )
			: X ( p_x )
			, Y ( p_y )
		{
		}

		Vector2 (sf::Vector2<_Ty>& other)
			: Vector2(other.X, other.Y)
		{
		}

		bool operator == ( const Vector2& rhs )
		{
			return X == rhs.X && Y == rhs.Y;
		}

		bool operator != ( const Vector2& rhs )
		{
			return !( *this == rhs );
		}


	};

	typedef Vector2<int> IntVector;

	template < class T, typename = std::enable_if_t <std::is_arithmetic_v <T>, T> >
	struct Point
	{
		int X, Y;

		sf::Vector2i ToVector () const
		{
			return sf::Vector2i ( X, Y );
		}

		Point ()
			: X ( 0 )
			, Y ( 0 )
		{
		}

		Point ( uint32_t p_x, uint32_t p_y )
			: X ( p_x )
			, Y ( p_y )
		{
		}

		Point ( const Point& p_other )
			: X ( p_other.X )
			, Y ( p_other.Y )
		{
		}

		bool operator == ( Point p_other ) const
		{
			return X == p_other.X & Y == p_other.Y;
		}

		bool operator != ( Point p_other ) const
		{
			return !( *this == p_other );
		}
	};

	template < class T, typename = std::enable_if_t <std::is_arithmetic_v <T>, T> >
	struct Size
	{
		int X, Y;

		sf::Vector2i ToVector () const
		{
			return sf::Vector2i ( X, Y );
		}

		Size ()
			: X ( 0 )
			, Y ( 0 )
		{
		}

		Size ( T p_x, T p_y )
			: X ( p_x )
			, Y ( p_y )
		{
		}

		Size ( const Size& p_other )
			: X ( p_other.X )
			, Y ( p_other.Y )
		{
		}

		bool IsEmpty () const
		{
			return X == 0 && Y == 0;
		}

		bool operator== ( Size p_other ) const
		{
			return X == p_other.X && Y == p_other.Y;
		}

		bool operator != ( Size p_other ) const
		{
			return !( *this == p_other );
		}
	};

	typedef Size <int> sizei;
	typedef Size <float> sizef;
}
