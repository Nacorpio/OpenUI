#pragma once
#include "SFML/System/Vector2.hpp"
#include <cstdint>
#include <type_traits>

template < class _Ty, typename = std::enable_if_t <std::is_integral_v <_Ty>, _Ty> >
struct Vector2
{
	_Ty X = 0;
	_Ty Y = 0;

	Vector2 () = default;

	Vector2 ( const _Ty p_x, const _Ty p_y )
		: X ( p_x )
		, Y ( p_y )
	{
	}

	Vector2 ( sf::Vector2 <_Ty>& other )
		: Vector2 ( other.X, other.Y )
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

	Vector2 <_Ty>& operator ++ ()
	{
		++X;
		++Y;

		return *this;
	}

	Vector2 <_Ty>& operator -- ()
	{
		--X;
		--Y;

		return *this;
	}

	Vector2 <_Ty>& operator += ( const _Ty rhs )
	{
		X += rhs;
		Y += rhs;

		return { X + rhs, Y + rhs };
	}

	Vector2 <_Ty>& operator -= ( const _Ty rhs )
	{
		X -= rhs;
		Y -= rhs;

		return *this;
	}

	Vector2 <_Ty>& operator *= ( const _Ty rhs )
	{
		X *= rhs;
		Y *= rhs;

		return *this;
	}

	Vector2 <_Ty>& operator /= ( const _Ty rhs )
	{
		X /= rhs;
		Y /= rhs;

		return *this;
	}

	Vector2 <_Ty>& operator + ( const Vector2 <_Ty> rhs )
	{
		return Vector2 <_Ty> ( X + rhs.X, Y + rhs.Y );
	}

	Vector2 <_Ty>& operator - ( const Vector2 <_Ty> rhs )
	{
		return Vector2 <_Ty> ( X - rhs.X, Y - rhs.Y );
	}

	Vector2 <_Ty>& operator * ( const Vector2 <_Ty> rhs )
	{
		return Vector2 <_Ty> ( X * rhs.X, Y * rhs.Y );
	}

	Vector2 <_Ty>& operator / ( const Vector2 <_Ty> rhs )
	{
		return Vector2 <_Ty> ( X / rhs.X, Y / rhs.Y );
	}
};

typedef Vector2 <int32_t> IntVector;
typedef Vector2 <uint32_t> UIntVector;
