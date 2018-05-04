#pragma once

#include <string>
#include <vector>
#include <set>
#include <Entities/Objects/Object.h>
#include "Entities/Controls/Control.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <Math/Vector2.h>
#include "Graphic/ScissorTest.h"
#include "Common/Comparers/ElementComparer.h"

namespace OpenUI
{
	class ClientWindow;
	class GraphicsContext;

	struct InputContext;
	struct Scheme;
	struct ElementComparerHeight;

	class Element
			: public Object,
			  public Control
	{
	public:
		explicit Element ( const std::string& name );
		~Element () = default;

		const std::string& GetName () const { return m_name; }

		ClientWindow* GetClientWindow () const { return m_clientWindow; }
		Element* GetParent () const { return m_parent; }
		uint16_t GetDrawOrder () const { return m_drawOrder; }

		/// <summary>
		/// 	The height of an element is the number of connections on the longest path between that element and the root element.
		/// </summary>
		/// <returns>The height of this element.</returns>
		int GetHeight () const { return m_height; }

		/// <summary>
		///		The level of an element is defined by 1 + (the number of connections between the element and the root element).
		/// </summary>
		/// <returns>The level of this element.</returns>
		int GetLevel () const { return m_level; }

		IntRect& GetBounds () { return m_bounds; }
		IntVector& GetSize () { return m_bounds.Size; }
		IntVector& GetPosition () { return m_bounds.Position; }

		//IntRect& GetContainerRectangle () { return m_containerRectangle; }

		std::vector <Element*> GetChildren () const { return m_children; }

		std::vector <sf::RectangleShape*>::iterator GetShapes() { return m_shapes.begin(); }
		std::vector <sf::Text*>::iterator GetTexts() { return m_texts.begin(); }
		sf::RectangleShape* GetShape ( const int& index );
		Scheme& GetScheme () const;

		void SetParent ( Element* element );
		void SetScheme ( Scheme* scheme ) { m_scheme = scheme; }

		void SetBounds ( const IntRect& value );
		void SetSize ( const IntVector& value );
		void SetPosition ( const IntVector& value );
		void ChangeContainerRectangle ( const IntRect& p_value );
		//void SetContainerRectangle(const IntRect & p_value);

		void SetBackgroundColor ( const sf::Color& p_color ) const;

		bool HasShape ( const int& index );
		bool HasShape ( sf::RectangleShape* rectangle );

		void AddChild ( Element* element );
		void RemoveChild ( Element* element );
		bool HasChild ( const Element* element );

		virtual void Update ();
		virtual void Draw ( const GraphicsContext& gContext );

		virtual void Start ();
		virtual void Initialize ();

		virtual void OnAscendingEvent(const sf::Event& event) {}
		
		bool operator == ( const Element& rhs ) const;
		bool operator != ( const Element& rhs ) const;

	protected:
		void SetContainerRectangle(const IntRect& p_value);

		virtual void OnDragEnter ( Element* ) override {}
		virtual void OnDragMove ( Element* ) override {}

		virtual void OnMouseLeave() override;
		virtual void OnMouseHover() override;
		virtual void OnMouseMove() override;
		virtual void OnMouseEnter() override;

		virtual void OnMouseClick() override;
		virtual void OnMouseDoubleClick() override;

		virtual void OnMouseDown() override;
		virtual void OnMouseUp() override;

		virtual void OnDrop(const InputHandler::MouseDropEvent& event) override;
		virtual void OnDragBegin() override;
		virtual void OnDragDrop(const InputHandler::MouseDragDropEvent&) override;

		virtual void OnAdded(){}

		virtual void OnBoundsChanged ( const IntRect& delta );
		virtual void OnPositionChanged ( const IntVector& delta );
		virtual void OnSizeChanged ( const IntVector& delta );
		virtual void OnFocusGained ();
		virtual void OnFocusLost ();

		virtual void OnChildAdded ( Element& child )
		{
			for (Element * element : m_children)
			{
				element->OnParentChildAdded(&child);
			}
		}
		virtual void OnChildRemoved ( Element& child )
		{
			for (Element * element : m_children)
			{
				element->OnParentChildRemoved(&child);
			}
		}

		virtual void OnParentChanged ( Element& newParent )
		{
		}
		virtual void OnFocusChanged() {}

		virtual void OnParentChildAdded(Element * child){}
		virtual void OnParentChildRemoved(Element * child) {}


		virtual void OnParentBoundsChanged ( const IntRect& delta );
		virtual void OnParentPositionChanged ( const IntVector& delta );
		virtual void OnParentSizeChanged ( const IntVector& delta );

		virtual void OnChildAdded(Element& child) {}
		virtual void OnChildRemoved(Element& child) {}
		virtual void OnParentChanged(Element& newParent) {}

		virtual void OnParentBoundsChanged(const IntRect& delta);
		virtual void OnParentPositionChanged(const IntVector& delta);
		virtual void OnParentSizeChanged(const IntVector& delta);

		virtual void OnStateChanged(ControlState state) override;

		void AddShape ( sf::RectangleShape* rectangle );
		void RemoveShape ( const int& index );

		void SetDrawOrder ( uint16_t value );

		void GiveFocus ();
		void LoseFocus ();

	private:
		void SortDrawOrder () const;

		/// <summary>
		///		Sets the visible bounds of this element. Visible bounds refers to what's left after clipping AKA what's visible.
		/// </summary>
		/// <returns>Returns True, if this element was resized. Returns false if not.</returns>
		bool SetVisibleBounds()
		{
			m_visibleBounds = m_bounds;

			if(!m_parent || m_parent->m_allowOutOfBoundsDrawing)
			{
				return false;
			}

			const auto boundsToFitInside = m_parent->m_visibleBounds;
			auto const boundsToFitInsideBottom = boundsToFitInside.Y + boundsToFitInside.Height;
			auto const boundsToFitInsideFitRight = boundsToFitInside.X + boundsToFitInside.Width;
			auto const resizingRectangleBottom = m_visibleBounds.Y + m_visibleBounds.Height;
			auto const resizingRectangleRight = m_visibleBounds.X + m_visibleBounds.Width;

			bool const isIntersectingBottom = resizingRectangleBottom > boundsToFitInsideBottom;
			bool const isIntersectingTop = m_visibleBounds.Y < boundsToFitInside.Y;
			bool const isIntersectingLeft = m_visibleBounds.X < boundsToFitInside.X;
			bool const isIntersectingRight = resizingRectangleRight > boundsToFitInsideFitRight;

			bool const resized = isIntersectingBottom || isIntersectingLeft || isIntersectingRight || isIntersectingTop;
			
			if (isIntersectingTop)
			{
				auto const delta = m_visibleBounds.Y - boundsToFitInside.Y;
				m_visibleBounds.Y = boundsToFitInside.Y;
				m_visibleBounds.Height += delta;
			}

			if (isIntersectingBottom)
			{
				m_visibleBounds.Height = boundsToFitInsideBottom - m_visibleBounds.Y;
			}

			if (isIntersectingLeft)
			{
				auto const delta = m_visibleBounds.X - boundsToFitInside.X;
				m_visibleBounds.X = boundsToFitInside.X;
				m_visibleBounds.Width += delta;
			}

			if (isIntersectingRight)
			{
				m_visibleBounds.Width = boundsToFitInsideFitRight - m_visibleBounds.X;
			}

			return resized;
		}

		const std::string m_name = "Element";

		friend class ElementMgr;
		Scheme* m_scheme;
		//ScissorTest m_scissorTest;
		IntRect m_visibleBounds;

		bool m_allowOutOfBoundsDrawing = false;

		int m_drawOrder = 0;
		int m_height = 0;
		int m_level = 0;

		friend struct InputHandler;
		long m_lastMoveTime = 0;
		bool m_isTopMost = false;

		sf::RectangleShape* m_background;

		std::vector <Element*> m_children { };

		std::vector <sf::RectangleShape*> m_shapes;
		std::vector <sf::Text*> m_texts;
		std::set <sf::Drawable*> m_drawables { };

		IntRect m_bounds;
		//IntRect m_containerRectangle;

		Element* m_parent = nullptr;
		ClientWindow* m_clientWindow = nullptr;
	};
}
