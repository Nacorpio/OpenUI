#pragma once
#include <unordered_map>
#include "Entities/Elements/Windows/ClientWindow.h"

namespace OpenUI
{
	class Element;
	class Button;
	class ClientWindow;

	typedef std::unordered_map <uint64_t, Element*> ElementMap;

	class ElementMgr
	{
	public:
		static ElementMgr* instance ()
		{
			static ElementMgr instance;
			return &instance;
		}

		~ElementMgr ();

		Element* operator [] ( uint64_t id );

		void Add ( uint64_t id, Element* element );
		bool Exists ( uint64_t id ) const;

		ClientWindow* CreateClientWindow ( uint64_t id, const std::string& name, const RenderWindowSettings& settings = RenderWindowSettings() );
		Button* CreateButton ( uint64_t id, const std::string& name );

		Element* GetElementByName ( const std::string& name );

		const std::vector <Element*>& GetElements () const;
		const std::set <ClientWindow*>& GetClientWindows() const;

	private:
		ElementMap m_mappedObjects;

		friend class Controller;

		std::set <ClientWindow*> m_clientWindows;
		std::vector <Element*> m_elements;
	};
}

#define sElementMgr OpenUI::ElementMgr::instance()
