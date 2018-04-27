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

namespace OpenUI
{
	class ClientWindow;
	class GraphicsContext;

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

		IntVector& GetSize ();

		IntVector & GetPosition() { return m_position; }

		std::vector <sf::RectangleShape*>& GetShapes ();
		std::vector <sf::Text*>& GetTexts ();
		sf::RectangleShape* GetShape(const int & p_index);

		std::vector<Element*> GetChildren() const { return m_children; }

		void SetParent(Element* element);

		void SetSize (IntVector & p_value );

		void SetPosition (IntVector & p_value );

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

		/* Updates the state of the element. */
		virtual void Update();

		/* Draws the element. */
		virtual void Draw ( const GraphicsContext& gContext );

		virtual void OnChildAdded ( Element& child ) {}
		virtual void OnChildRemoved ( Element& child ) {}
		virtual void OnParentChanged( Element& newParent) {}

		bool operator == ( const Element& rhs ) const;
		bool operator != ( const Element& rhs ) const;

	protected:
		void SetDrawOrder ( uint16_t value );
		std::vector <Element*> m_children{};

	private:
		void Sort() const;

		const std::string m_name = "Element";
		
		uint16_t m_drawOrder = 0;

		std::vector<sf::RectangleShape*> m_shapes;
		std::vector<sf::Text*> m_texts;
		std::set <sf::Drawable*> m_drawables { };

		IntVector m_position {0,0 };
		IntVector m_size {100,100 };

		Element* m_parent = nullptr;
		ClientWindow* m_clientWindow = nullptr;
	};
}
