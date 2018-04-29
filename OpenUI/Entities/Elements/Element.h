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
#include "Math/Rectangle.h"
#include "Graphic/ScissorTest.h"
#include "Graphic/ColorScheme.h"

namespace OpenUI
{
	class ClientWindow;
	class GraphicsContext;
	struct InputContext;

	class Element : public Object , public Control
	{
	public:
		enum class ElementFlags : uint32_t
		{
			CaptureMouse,
			CaptureKeyboard,
			AllowChildOverlapping,
			AllowScissorTest,

			Interactable = CaptureMouse | CaptureKeyboard
		};

		explicit Element ( const std::string& name );
		~Element() = default;

		const std::string& GetName () const { return m_name; }

		ClientWindow* GetClientWindow() const { return m_clientWindow; }

		Element* GetParent () const { return m_parent; }
		uint16_t GetDrawOrder () const { return m_drawOrder; }

		/// <summary>
		/// 	The height of an element is the number of connections on the longest path between that element and the root element.
		/// </summary>
		/// <returns>The height of this element.</returns>
		uint16_t GetHeight() const { return m_height; }

		/// <summary>
		///		The level of an element is defined by 1 + (the number of connections between the element and the root element).
		/// </summary>
		/// <returns>The level of this element.</returns>
		uint16_t GetLevel() const { return m_level; }

		IntRect & GetBounds()  { return m_bounds;	}
		IntVector& GetSize() { return m_bounds.Size; }
		IntVector & GetPosition() { return m_bounds.Position; }

		std::vector <sf::RectangleShape*>& GetShapes ();
		std::vector <sf::Text*>& GetTexts ();
		sf::RectangleShape* GetShape(const int & p_index);

		std::vector<Element*> & GetChildren()  { return m_children; }

		void SetParent(Element* element);

		void SetBounds ( const IntRect & p_value );

		void SetSize (const IntVector & p_value );
		void SetPosition (const IntVector & p_value );

		void AddShape ( sf::RectangleShape * p_rectangle );
		void RemoveShape (const int & p_index );
		bool HasShape (const int & p_index);
		bool HasShape(sf::RectangleShape * p_rectangle);

		void AddChild ( Element* element );
		void RemoveChild ( Element* element );
		bool HasChild ( const Element* element );

		/* Parent is not guarenteed to be set. */
		virtual void Start ();

		/* Parent is guaranteed to be set. */
		virtual void Initialize();

		virtual void Input(InputContext * p_inputContext);

		/* Updates the state of the element. */
		virtual void Update();

		/* Draws the element. */
		virtual void Draw ( const GraphicsContext& gContext );

		virtual void OnChildAdded ( Element& child ) {}
		virtual void OnChildRemoved ( Element& child ) {}
		virtual void OnParentChanged( Element& newParent) {}

		virtual void OnBoundsChanged ( IntRect & p_delta );
		virtual void OnParentBoundsChanged ( IntRect & p_delta );

		bool operator == ( const Element& rhs ) const;
		bool operator != ( const Element& rhs ) const;

	protected:
		void SetDrawOrder ( uint16_t value );

		std::vector <Element*> m_children{};

	private:
		void SortDrawOrder() const;

	public:
		void OnStateChanged ( MouseState p_state ) override
		{
			m_shapes[0]->setFillColor(*m_scheme.GetColor(ColorType::BackgroundColor,p_state));
			
		}

	private:
		const std::string m_name = "Element";
		ScissorTest m_scissorTest;
		uint16_t m_drawOrder = 0;
		uint16_t m_height = 0;
		uint16_t m_level = 0;

		ColorScheme m_scheme;
		std::vector<sf::RectangleShape*> m_shapes;
		std::vector<sf::Text*> m_texts;
		std::set <sf::Drawable*> m_drawables { };

		IntRect m_bounds;
		
		Element* m_parent = nullptr;
		ClientWindow* m_clientWindow = nullptr;
	};
}
