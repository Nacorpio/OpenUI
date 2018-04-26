#pragma once

#include <string>
#include <vector>
#include <set>
#include <SFML/Graphics/Drawable.hpp>
#include "Entities/Objects/Object.h"
#include "Math/Vector2.h"

namespace OpenUI
{
	class ClientWindow;

	class Element : public Object
	{
	public:
		explicit Element (const std::string& name)
			: m_name ( name )
		{
			m_guidTypeId = ObjectGuid::TypeId::Element;
		}

		~Element() = default;

		const std::string& GetName () const { return m_name; }
		Element* GetParent () const { return m_parent; }
		uint16_t GetDrawOrder () const { return m_drawOrder; }

		void SetParent(Element* element);

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
		virtual void Draw ()
		{
			for (auto it = m_drawables.begin (); it != m_drawables.end(); ++it)
			{
				// it._Ptr->_Myval->draw ()
			}
		}

		virtual void OnChildAdded ( Element& child ) { child.Initialize(); }
		virtual void OnChildRemoved ( Element& child ) {}

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
