#include "stdafx.h"
#include "WindowElement.h"
#include "Managers/ElementMgr.h"

namespace OpenUI
{
#pragma region WindowHeaderElement
	WindowHeaderElement::WindowHeaderElement ( const std::string & p_name )
		: Element ( p_name )
	{
		m_guidDetail = ObjectGuid::Detail::WindowHeaderElement;
	}

	WindowHeaderElement::~WindowHeaderElement ()
	{
	}

	WindowElement& WindowHeaderElement::GetWindowContainer () const
	{
		return *m_windowElement;
	}

	void WindowHeaderElement::SetWindowContainer ( WindowElement * element )
	{
		const auto thisBounds = GetBounds();
		m_windowElement = element;
		AddChild ( m_windowElement );
		m_windowElement->SetPosition ( { thisBounds.X,thisBounds.Y + thisBounds.Height } );
	}

	void WindowHeaderElement::ContainerAddChild ( Element * element ) const
	{
		if (!m_windowElement)
		{
			return;
		}

		m_windowElement->AddChild ( element );
	}

	void WindowHeaderElement::OnMouseDown ()
	{
		Element::OnMouseDown();
		SetMousePressedPosition();
		m_isMousePressed = true;
	}

	void WindowHeaderElement::Update ()
	{
		Element::Update();
		if (!m_isMousePressed || !sInputInformation->MouseIsDown)
		{
			m_isMousePressed = false;
			return;
		}

		DragWindow();
	}

	void WindowHeaderElement::SetMousePressedPosition ()
	{
		const auto currentLocation = GetBounds().Position;
		m_mousePressedPosition.X = sInputInformation->MousePosition.X - currentLocation.X;
		m_mousePressedPosition.Y = sInputInformation->MousePosition.Y - currentLocation.Y;
	}

	void WindowHeaderElement::DragWindow ()
	{
		SetPosition ( sInputInformation->MousePosition - m_mousePressedPosition );
	}

#pragma endregion WindowHeaderElement

#pragma region WindowElement

	WindowElement::WindowElement ( const std::string & p_name )
		: Element ( p_name )
	{
		m_guidDetail = ObjectGuid::Detail::WindowElement;
	}

	WindowElement::~WindowElement ()
	{
	}

#pragma endregion WindowElement
}
