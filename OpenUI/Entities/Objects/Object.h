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
			: m_guidTypeId ( ObjectGuid::TypeId::Object )
			, m_guidDetail ( ObjectGuid::Detail::None )
		{
		}

		ObjectGuid::TypeId GetTypeId() const
		{
			return m_guidTypeId;
		}

		ObjectGuid::Detail GetDetail() const
		{
			return m_guidDetail;
		}

		void SetFlag ( const int flag )
		{
			m_flags = flag;
		}

		void AddFlag ( const int flag )
		{
			m_flags |= flag;
		}

		void RemoveFlag ( const int flag )
		{
			m_flags &= ~flag;
		}

		/* Toggles a bit flag. */
		void ToggleFlag ( const int flag )
		{
			m_flags ^= flag;
		}

		/* Determines whether a bit flag is set. */
		bool HasFlag ( const int flag ) const
		{
			return m_flags & flag;
		}

		/* Resets the bit flags. */
		void ResetFlags()
		{
			m_flags = 0;
		}

		int GetFlags() const { return m_flags; }

		Button* ToButton ();
		ClientWindow* ToClientWindow ();

	protected:
		int m_flags = 0;

		ObjectGuid::TypeId m_guidTypeId;
		ObjectGuid::Detail m_guidDetail;
	};
}
