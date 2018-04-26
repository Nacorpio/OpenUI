#pragma once

#include "ObjectGuid.h"

namespace OpenUI
{
	class Button;

	class Object
	{
	public:
		virtual ~Object () = default;

		Object ()
			: m_guid ( ObjectGuid::TypeId::Object, ObjectGuid::Detail::None )
		{
		}

		ObjectGuid& GetGuid () { return m_guid; }

		Button* ToButton() { return reinterpret_cast <Button*> (this); }

	protected:
		ObjectGuid m_guid;
	};
}
