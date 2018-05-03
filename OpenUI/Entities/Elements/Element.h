#pragma once

#include <string>
#include <vector>
#include <set>
#include <Entities/Objects/Object.h>
#include <Math/Vector2.h>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Entities/Controls/Control.h"
#include "Graphic/ScissorTest.h"
#include "Contexts.h"
#include "Graphic/Scheme.h"

namespace OpenUI
{
	class ClientWindow;
	class GraphicsContext;

	struct InputContext;

	class Element
			: public Object,
			  public Control
	{
	public:
		enum class ElementFlags : int
		{
			CaptureMouse,
			CaptureKeyboard,
			AllowChildOverlapping,
			AllowScissorTest,

			Interactable = CaptureMouse | CaptureKeyboard
		};

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

		std::vector <sf::RectangleShape*>::iterator GetShapes () { return m_shapes.begin (); }

		std::vector <sf::Text*>::iterator GetTexts () { return m_texts.begin (); }

		std::vector <Element*>::iterator GetChildren () { return m_children.begin (); }

		sf::RectangleShape* GetShape ( const int& index );

		void SetParent ( Element* element );

		void SetScheme ( Scheme* scheme ) { m_scheme = scheme; }

		void SetBounds ( const IntRect& value );
		void SetSize ( const IntVector& value );
		void SetPosition ( const IntVector& value );

		bool HasShape ( const int& index );
		bool HasShape ( sf::RectangleShape* rectangle );

		void AddChild ( Element* element );
		void RemoveChild ( Element* element );
		bool HasChild ( const Element* element );

		virtual void Start () const;
		virtual void Initialize ();

		void OnMouseLeave () override;
		void OnMouseHover () override;
		void OnMouseMove () override;
		void OnMouseEnter () override;

		void OnMouseClick ( const sf::Event::MouseButtonEvent& event ) override;
		void OnMouseDoubleClick ( const sf::Event::MouseButtonEvent& event ) override;

		void OnMouseDown ( const sf::Event::MouseButtonEvent& event ) override;
		void OnMouseUp ( const sf::Event::MouseButtonEvent& event ) override;

		void OnDrop ( const InputHandler::MouseDropEvent& event ) override;
		void OnDragBegin () override;
		void OnDragDrop ( const InputHandler::MouseDragDropEvent& ) override;

		virtual void Update ( const UpdateContext& updateContext );
		virtual void OnBoundsChanged ( IntRect& delta );
		virtual void Draw ( const GraphicsContext& gContext );

		virtual void OnChildAdded ( Element& child )
		{
		}
		virtual void OnChildRemoved ( Element& child )
		{
		}
		virtual void OnParentChanged ( Element& newParent )
		{
		}

		virtual void OnParentBoundsChanged ( IntRect& delta );

		void OnStateChanged ( ControlState state ) override;

		bool operator == ( const Element& rhs ) const;
		bool operator != ( const Element& rhs ) const;

	protected:

		void AddShape ( sf::RectangleShape* rectangle );
		void RemoveShape ( const int& index );

		void SetDrawOrder ( uint16_t value );

	private:
		void SortDrawOrder () const;

		const std::string m_name = "Element";

		Scheme* m_scheme;
		ScissorTest m_scissorTest;

		int m_drawOrder = 0;
		int m_height = 0;
		int m_level = 0;

		sf::RectangleShape m_background;
		std::vector <Element*> m_children { };
		std::vector <sf::RectangleShape*> m_shapes;
		std::vector <sf::Text*> m_texts;
		std::set <sf::Drawable*> m_drawables { };

		IntRect m_bounds;

		Element* m_parent = nullptr;
		ClientWindow* m_clientWindow = nullptr;
	};
}
