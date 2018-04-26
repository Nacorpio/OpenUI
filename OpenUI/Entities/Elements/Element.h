#pragma once

#include <string>
#include <vector>
#include <set>
#include <Entities/Objects/Object.h>
#include <Math/Vector2.h>
#include <SFML/Graphics/Drawable.hpp>

namespace OpenUI
{
	class ClientWindow;
	class GraphicsContext;

	class Element : public Object
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
		std::vector <Element*> GetChildren() const { return m_children; }
		IntVector & GetSize() { return m_size; }
		IntVector & GetPosition() { return m_position; }

		IntVector GetPosition() const { return m_position; }
		IntVector GetSize() const { return m_size; }

		std::vector<Element*> GetChildren() const { return m_children; }

		void SetParent(Element* element);
		void SetSize(IntVector p_value) { m_size = p_value; }
		void SetPosition(IntVector p_value) { m_position = p_value; }

		void AddChild ( Element* element );
		void RemoveChild ( Element* element );
		bool HasChild ( const Element* element );

		/* Parent is not guarenteed to be set. */
		virtual void Start() = 0;

		/* Parent is guaranteed to be set. */
		virtual void Initialize () = 0;

		/* Updates the state of the element. */
		virtual void Update () = 0;

		/* Draws the element. */
		virtual void Draw ( const GraphicsContext& gContext );

		virtual void OnChildAdded ( Element& child ) { child.Initialize(); }
		virtual void OnChildRemoved ( Element& child ) {}

		virtual void OnParentChanged( Element& newParent) {}

		bool operator == ( const Element& rhs ) const;
		bool operator != ( const Element& rhs ) const;

	protected:
		void SetDrawOrder ( uint16_t value );

	private:
		void Sort() const;

		const std::string m_name = "Element";
		
		uint16_t m_drawOrder = 0;

		std::set <sf::Drawable*> m_drawables { };
		std::vector <Element*> m_children { };

		IntVector m_position { };
		IntVector m_size { };

		Element* m_parent = nullptr;
		ClientWindow* m_clientWindow = nullptr;
	};
}
