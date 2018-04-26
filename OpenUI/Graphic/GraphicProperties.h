#pragma once
#include <SFML/System/Vector2.hpp>
#include <unordered_map>
#include <SFML/Graphics/Rect.hpp>
#include "Common/Enums.h"

namespace OpenUI
{
	/// <summary>
	///		Defines the distance the inheriting object should position its children located away from itself.
	/// </summary>
	struct Padding
	{
		enum PaddingSide
		{
			Left,
			Right,
			Top,
			Bottom
		};

		/// <summary>
		///		Sets a specific side of the padding.
		/// </summary>
		/// <param name="p_side">The side of the padding to be changed</param>
		/// <param name="p_value">The value of which the side will be set to</param>
		void Set ( const PaddingSide p_side, const int p_value )
		{
			m_paddingCollection[p_side] = p_value;
		}

		/// <summary>
		///		Sets all of the sides of the padding to a specific value.
		/// </summary>
		/// <param name="p_value">The value of which to set all the sides to</param>
		void SetAll ( const int p_value )
		{
			m_paddingCollection[Left] = p_value;
			m_paddingCollection[Right] = p_value;
			m_paddingCollection[Top] = p_value;
			m_paddingCollection[Bottom] = p_value;
		}

		/// <summary>
		///		Gets the value of a specific side of the padding.
		/// </summary>
		/// <param name="p_side">The side of the padding</param>
		/// <returns>The value of the specific side</returns>
		int Get ( PaddingSide p_side )
		{
			return m_paddingCollection[p_side];
		}

		/// <summary>
		///		Gets a corner of the padding by specifiing two sides.
		/// </summary>
		/// <param name="p_side1">First side</param>
		/// <param name="p_side2">Second side</param>
		/// <returns>Two sides of a the padding</returns>
		sf::Vector2i GetCorner ( const PaddingSide p_side1, const PaddingSide p_side2 )
		{
			return sf::Vector2i ( m_paddingCollection[p_side1], m_paddingCollection[p_side2] );
		}

		/// <summary>
		///		Gets all of the sides of the padding.
		/// </summary>
		/// <returns>Returns an array of the value of each side in the following order: Left,Right,Top,Bottom</returns>
		int* GetAll ()
		{
			int arr[4];
			arr[0] = m_paddingCollection[Left];
			arr[1] = m_paddingCollection[Right];
			arr[2] = m_paddingCollection[Top];
			arr[3] = m_paddingCollection[Bottom];

			return arr;
		}

		bool operator == ( Padding& p_rhs )
		{
			return GetAll () == p_rhs.GetAll ();
		}

		bool operator != ( Padding& p_rhs )
		{
			return !( *this == p_rhs );
		}

	private:
		std::unordered_map <PaddingSide, int> m_paddingCollection;
	};

	/// <summary>
	///		Defines the edges of a child that will meet its parent edges
	/// </summary>
	struct Docking
	{
		struct DockStyleChangedInfo
		{
			DockStyleChangedInfo (
				sf::IntRect& p_childRectangle, sf::IntRect& p_parrentRectangle,
				sf::IntRect& p_childRectangleChanged, const DockStyle p_dockStyle )
				: ChildRectangle ( p_childRectangle )
				, ParentRectangle ( p_parrentRectangle )
				, ChildRectangleChanged ( p_childRectangleChanged )
				, DockStyleUsed ( p_dockStyle )
			{
			}

			sf::IntRect& ChildRectangle;
			sf::IntRect& ChildRectangleChanged;
			sf::IntRect& ParentRectangle;

			DockStyle DockStyleUsed;
		};

		/// <summary>
		///		Calculates the change in a child's bounds if a child was to dock with a parent using the specified dock-style. 
		/// </summary>
		/// <param name="p_parentBounds">The parent's bounds</param>
		/// <param name="p_childBounds">The child's bounds</param>
		/// <returns>Docking data</returns>
		static DockStyleChangedInfo CalculateDock (
			const DockStyle p_dockStyle, sf::IntRect& p_parentBounds, sf::IntRect& p_childBounds )
		{
			sf::IntRect childBoundsChanged = p_childBounds;

			switch ( p_dockStyle )
			{
				case Left :
				{
					childBoundsChanged.left = p_parentBounds.left;
					childBoundsChanged.top = p_parentBounds.top;
					childBoundsChanged.height = p_parentBounds.height;
					break;
				}

				case Right :
				{
					childBoundsChanged.left = p_parentBounds.left + p_parentBounds.width - p_childBounds.width;
					childBoundsChanged.top = p_parentBounds.top;
					childBoundsChanged.height = p_parentBounds.height;
					break;
				}

				case Top :
				{
					childBoundsChanged.left = p_parentBounds.left;
					childBoundsChanged.top = p_parentBounds.top;
					childBoundsChanged.width = p_parentBounds.width;
					break;
				}

				case Bottom :
				{
					childBoundsChanged.left = p_parentBounds.left;
					childBoundsChanged.top = p_parentBounds.top + p_parentBounds.height - p_childBounds.height;
					childBoundsChanged.width = p_parentBounds.width;
					break;
				}

				case Filled :
				{
					childBoundsChanged = p_parentBounds;
					break;
				}

				case None :
					break;
				default :
					break;
			}

			return DockStyleChangedInfo ( p_childBounds, p_parentBounds, childBoundsChanged, p_dockStyle );
		}
	};
}
