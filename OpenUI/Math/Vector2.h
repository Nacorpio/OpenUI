#pragma once

#include <cstdint>
#include <type_traits>
#include <SFML/System/Vector2.hpp>

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

	explicit Vector2(const sf::Vector2f & p_sfVector)
		: X(p_sfVector.x)
		, Y(p_sfVector.y)
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

	bool operator > (const Vector2& rhs)
	{
		return X > rhs.X && Y > rhs.Y;
	}

	bool operator < (const Vector2& rhs)
	{
		return X < rhs.X && Y < rhs.Y;
	}

	bool operator >= (const Vector2& rhs)
	{
		return X >= rhs.X && Y >= rhs.Y;
	}

	bool operator <= (const Vector2& rhs)
	{
		return X <= rhs.X && Y <= rhs.Y;
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

	Vector2 <_Ty> operator + ( const Vector2 <_Ty> & rhs )
	{
		return Vector2 <_Ty> ( X + rhs.X, Y + rhs.Y );
	}

	Vector2 <_Ty> operator - ( const Vector2 <_Ty> & rhs )
	{
		return Vector2 <_Ty> ( X - rhs.X, Y - rhs.Y );
	}

	Vector2 <_Ty> operator * ( const Vector2 <_Ty> & rhs )
	{
		return Vector2 <_Ty> ( X * rhs.X, Y * rhs.Y );
	}

	Vector2 <_Ty> operator / ( const Vector2 <_Ty> & rhs )
	{
		return Vector2 <_Ty> ( X / rhs.X, Y / rhs.Y );
	}

	// SFML vector2f converters
	Vector2 <_Ty> operator + (const sf::Vector2f & rhs)
	{
		return Vector2 <_Ty>(X + rhs.x, Y + rhs.y);
	}

};



typedef Vector2 <int32_t> IntVector;
typedef Vector2 <uint32_t> UIntVector;
