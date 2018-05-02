#include "stdafx.h"
#include "WindowElement.h"

namespace OpenUI
{
	WindowElement::WindowElement(const std::string& p_name, const uint16_t & p_headerSize)
		: Element("WindowElement")
	{
	}

	WindowElement::~WindowElement()
	{
	}

	void WindowElement::OnMouseClick ( const sf::Event::MouseButtonEvent & event )
	{
	}

	void WindowElement::Start () const
	{
	}

	void WindowElement::Initialize () 
	{
	}

	void WindowElement::Update ( const OpenUI::UpdateContext & p_updateContext )
	{
	}

	void WindowElement::OnBoundsChanged ( OpenUI::IntRect & p_delta )
	{
	}

	void WindowElement::Draw ( const OpenUI::GraphicsContext & gContext )
	{
	}

	void WindowElement::OnMouseDown ( const sf::Event::MouseButtonEvent & event )
	{
	}

	void WindowElement::OnMouseUp ( const sf::Event::MouseButtonEvent & event )
	{
	}

	void WindowElement::OnChildAdded ( Element & child )
	{
	}
}
