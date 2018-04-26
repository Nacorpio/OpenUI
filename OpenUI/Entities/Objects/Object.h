#pragma once

#include "ObjectGuid.h"
#include <cstdint>

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

		/* Sets a bit flag to the specified value. */
		void SetFlag ( const uint32_t flag, const bool value )
		{
			if ( value )
			{
				m_flags |= flag;
				return;
			}

			m_flags &= ~flag;
		}

		/* Toggles a bit flag. */
		void ToggleFlag ( const uint32_t flag )
		{
			m_flags ^= flag;
		}

		/* Determines whether a bit flag is set. */
		bool HasFlag ( const uint32_t flag ) const
		{
			return (m_flags & flag) != 0;
		}

		/* Resets the bit flags. */
		void ResetFlags()
		{
			m_flags = 0;
		}

		uint32_t GetFlags() const { return m_flags; }

		Button* ToButton ();
		ClientWindow* ToClientWindow ();

	protected:
		uint32_t m_flags = 0;

		ObjectGuid::TypeId m_guidTypeId;
		ObjectGuid::Detail m_guidDetail;
	};
}
