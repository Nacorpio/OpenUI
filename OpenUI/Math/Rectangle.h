#pragma once
#include <cstdint>
#include <SFML/Graphics/Rect.hpp>
#include "Math/Vector2.h"
#include <iostream>

namespace OpenUI
{
	template < class _Ty, typename = std::enable_if_t <std::is_integral_v <_Ty>, _Ty> >
	struct Rectangle
	{
		union
		{
			struct
			{
				_Ty X, Y;
				_Ty Width, Height;
			};

			struct
			{
				Vector2 <_Ty> Position;
				Vector2 <_Ty> Size;
			};

			_Ty Array[4];
		};

		Rectangle ()
			: X ( 0 )
			, Y ( 0 )
			, Width ( 0 )
			, Height ( 0 )
		{
		}

		Rectangle ( const _Ty x, const _Ty y, const _Ty width, const _Ty height )
			: X ( x )
			, Y ( y )
			, Width ( width )
			, Height ( height )
		{
		}

		Rectangle ( _Ty array[4] )
			: X ( array[0] )
			, Y ( array[1] )
			, Width ( array[2] )
			, Height ( array[3] )
		{
		}

		explicit Rectangle ( const sf::IntRect& other )
			: X ( other.left )
			, Y ( other.top )
			, Width ( other.width )
			, Height ( other.height )
		{
		}

		bool IsEmpty ()
		{
			return X == 0 && Y == 0 && Width == 0 && Height == 0;
		}

		bool Contains ( const Vector2 <_Ty>& p_value )
		{
			return X <= p_value.X && Y <= p_value.Y && X + Width >= p_value.X && Y + Height > p_value.Y;
		}

		bool Contains ( Vector2 <_Ty>& p_value )
		{
			return X <= p_value.X && Y <= p_value.Y && X + Width >= p_value.X && Y + Height > p_value.Y;
		}

		/// <summary>
		///		Returns true if the given rectangle is not within the bounds of this rectangle.
		/// </summary>
		/// <param name="p_rectangle">The rectangle to be checked for intersection.</param>
		/// <param name="p_intersection">Optional - sets the intersection to this rectangle.</param>
		/// <returns>True if the given rectangle is intersecting, false if not.</returns>
		bool IsIntersecting ( const Rectangle& p_rectangle, Rectangle& p_intersection )
		{
			p_intersection = ResizeToFit ( p_rectangle );
			return !p_intersection.IsEmpty ();
		}

		/// <summary>
		///		Checks if a specified rectangle is intersecting this rectangle. Use this if you only want to check if something is intersecting as it's almost twice as fast as the IsIntersecting(const Rectangle & p_rectangle, Rectangle & p_intersection).
		/// </summary>
		/// <param name="p_rectangle">Rectangle to be intersected.</param>
		/// <returns></returns>
		bool IsIntersecting ( const Rectangle& p_rectangle )
		{
			return ( Y + Height ) > ( p_rectangle.Y + p_rectangle.Height )
					|| Y < p_rectangle.Y
					|| X < p_rectangle.X
					|| ( X + Width ) > ( p_rectangle.X + p_rectangle.Width );
		}


		/// <summary>
		///		Resizes this rectangle to fit inside a specified rectangle.
		/// </summary>
		/// <param name="p_rectangle">Rectangle to be resized.</param>
		/// <returns>Returns itself.</returns>
		Rectangle& ResizeToFit ( const Rectangle& p_rhs )
		{
			if ( Y < p_rhs.Y )
			{
				Y = p_rhs.Y;
				Height = p_rhs.Y + p_rhs.Height - Y;
			}

			if ( ( Y + Height ) > ( p_rhs.Y + p_rhs.Height ) )
			{
				Height = p_rhs.Y + p_rhs.Height - Y;
			}

			if ( X < p_rhs.X )
			{
				X = p_rhs.X;
				Width -= p_rhs.X;
			}

			if ( ( X + Width ) > ( p_rhs.X + p_rhs.Width ) )
			{
				Width = ( p_rhs.X + p_rhs.Width ) - X;
			}

			return *this;
		}

		bool operator == ( const Rectangle& rhs )
		{
			return X == rhs.X && Y == rhs.Y && Width == rhs.Width && Height == rhs.Height;
		}

		bool operator != ( const Rectangle& rhs )
		{
			return !( *this == rhs );
		}

		bool operator > ( const Rectangle& rhs )
		{
			return X > rhs.X && Y > rhs.Y && Width > rhs.Width && Height > rhs.Height;
		}

		bool operator < ( const Rectangle& rhs )
		{
			return X < rhs.X && Y < rhs.Y && Width < rhs.Width && Height < rhs.Height;
		}

		bool operator >= ( const Rectangle& rhs )
		{
			return X >= rhs.X && Y >= rhs.Y && Width >= rhs.Width && Height >= rhs.Height;
		}

		bool operator <= ( const Rectangle& rhs )
		{
			return X <= rhs.X && Y <= rhs.Y && Width <= rhs.Width && Height <= rhs.Height;
		}

		Rectangle <_Ty>& operator ++ ()
		{
			++X;
			++Y;

			++Width;
			++Height;

			return *this;
		}

		Rectangle <_Ty>& operator -- ()
		{
			--X;
			--Y;
			--Width;
			--Height;

			return *this;
		}

		Rectangle <_Ty>& operator += ( const Rectangle <_Ty>& rhs )
		{
			X += rhs.X;
			Y += rhs.Y;

			Width += rhs.Width;
			Height += rhs.Height;

			return *this;
		}
		Rectangle <_Ty>& operator += ( const _Ty rhs )
		{
			X += rhs;
			Y += rhs;

			Width += rhs;
			Height += rhs;

			return { X + rhs, Y + rhs, Width + rhs, Height + rhs };
		}

		Rectangle <_Ty>& operator -= ( const _Ty rhs )
		{
			X -= rhs;
			Y -= rhs;

			Width -= rhs;
			Height -= rhs;

			return *this;
		}

		Rectangle <_Ty>& operator *= ( const _Ty rhs )
		{
			X *= rhs;
			Y *= rhs;

			Width *= rhs;
			Height *= rhs;

			return *this;
		}

		Rectangle <_Ty>& operator /= ( const _Ty rhs )
		{
			X /= rhs;
			Y /= rhs;

			Width /= rhs;
			Height /= rhs;

			return *this;
		}

		Rectangle <_Ty> operator + ( const Rectangle <_Ty>& rhs )
		{
			return Rectangle <_Ty> ( X + rhs.X, Y + rhs.Y, Width + rhs.Width, Height + rhs.Height );
		}

		Rectangle <_Ty> operator - ( const Rectangle <_Ty>& rhs ) const
		{
			return Rectangle <_Ty> ( X - rhs.X, Y - rhs.Y, Width - rhs.Width, Height - rhs.Height );
		}

		Rectangle <_Ty> operator * ( const Rectangle <_Ty>& rhs )
		{
			return Rectangle <_Ty> ( X * rhs.X, Y * rhs.Y, Width * rhs.Width, Height * rhs.Height );
		}

		Rectangle <_Ty> operator / ( const Rectangle <_Ty>& rhs )
		{
			return Rectangle <_Ty> ( X / rhs.X, Y / rhs.Y, Width / rhs.Width, Height / rhs.Height );
		}
		friend 	std::ostream & operator<< (std::ostream & os, Rectangle<int> & p_rhs);
	};

	typedef Rectangle <int32_t> IntRect;
	typedef Rectangle <uint32_t> UIntRect;

	inline std::ostream & operator<< ( std::ostream & os, Rectangle<int> & p_rhs)
	{
		os << "X: " << p_rhs.X << " Y: " << p_rhs.Y << " Width: " << p_rhs.Width << " Height: " << p_rhs.Height;
		return os;
	}
}
