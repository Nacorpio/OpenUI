#include "stdafx.h"
#include "Object.h"

OpenUI::Button* OpenUI::Object::ToButton ()
{
	if (m_guidDetail != ObjectGuid::Detail::Button)
	{
		return nullptr;
	}

	return reinterpret_cast <Button*> (this);
}

OpenUI::ClientWindow* OpenUI::Object::ToClientWindow ()
{
	if ( m_guidDetail != ObjectGuid::Detail::ClientWindow )
	{
		return nullptr;
	}

	return reinterpret_cast <ClientWindow*> (this);
}
