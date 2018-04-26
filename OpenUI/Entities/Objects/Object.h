#pragma once

#include "ObjectGuid.h"

namespace OpenUI
{
	class Button;
	class ClientWindow;

	class Object
	{
	public:
		virtual ~Object () = default;

		Object ()
			: m_guidTypeId ( ObjectGuid::TypeId::Object ), m_guidDetail ( ObjectGuid::Detail::None )
		{
		}

		Button* ToButton() { return reinterpret_cast <Button*> (this); }
		ClientWindow* ToClientWindow() { return reinterpret_cast<ClientWindow*>(this); }

	protected:
		ObjectGuid::TypeId m_guidTypeId;
		ObjectGuid::Detail m_guidDetail;
	};
}
