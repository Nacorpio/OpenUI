﻿#pragma once

#include <string>
#include <vector>
#include <set>
#include <Entities/Objects/Object.h>
#include <Math/Vector2.h>
#include <Rectangle.h>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Entities/Controls/Control.h"
#include <SFML/Window/Event.hpp>

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

		IntRect& GetBounds()  { return m_bounds;	}
		IntVector& GetSize() { return m_bounds.Size; }
		IntVector& GetPosition() { return m_bounds.Position; }

		std::vector <sf::RectangleShape*>& GetShapes ();
		std::vector <sf::Text*>& GetTexts ();
		std::vector <Element*>& GetChildren() { return m_children; }

		sf::RectangleShape* GetShape(const int & p_index);

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

		virtual void Start () const;
		virtual void Initialize() const;

		virtual void Update();
		virtual void Draw ( const GraphicsContext& gContext );

		virtual void OnChildAdded ( Element& child ) {}
		virtual void OnChildRemoved ( Element& child ) {}
		virtual void OnParentChanged( Element& newParent) {}

		void OnMouseEnter () override;
		void OnMouseLeave () override;
		void OnMouseHover () override;
		void OnMouseMove () override;

		void OnMouseDown ( const sf::Event::MouseButtonEvent& event) override;
		void OnMouseUp ( const sf::Event::MouseButtonEvent& event ) override;

		virtual void OnDrop ( const InputContext::MouseDropEvent& event ) override;
		virtual void OnDragDrop( const InputContext::MouseDragDropEvent& event ) override;
		virtual void OnDragEnter ( Element* source ) override;
		virtual void OnDragMove ( Element* source ) override;

		bool operator == ( const Element& rhs ) const;
		bool operator != ( const Element& rhs ) const;

	protected:
		void SetDrawOrder ( uint16_t value );

		std::vector <Element*> m_children{};

	private:
		void SortDrawOrder() const;

		const std::string m_name = "Element";
		
		uint16_t m_drawOrder = 0;
		uint16_t m_height = 0;
		uint16_t m_level = 0;

		long m_lastMouseDown = 0;
		long m_lastMouseRelease = 0;

		std::vector<sf::RectangleShape*> m_shapes;
		std::vector<sf::Text*> m_texts;
		std::set <sf::Drawable*> m_drawables { };

		IntRect m_bounds;
		
		Element* m_parent = nullptr;

		ClientWindow* m_clientWindow = nullptr;
	};
}
