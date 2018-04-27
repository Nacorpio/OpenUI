#include "stdafx.h"
#include "Button.h"
#include <iostream>

namespace OpenUI
{
	Button::Button ( const std::string& name )
		: Element(name)
	{
		m_guidDetail = ObjectGuid::Detail::Button;
		AddShape(new sf::RectangleShape({100,100}));
	}

	Button::~Button ()
	{
	}

	void Button::Start ()
	{
		Element::Start();
	}

	void Button::Initialize ()
	{
		Element::Initialize();
	}

	void Button::Update ()
	{
		Element::Update();
	}

	void Button::Draw ( const GraphicsContext & gContext )
	{
		Element::Draw ( gContext );
	}

	void Button::OnMouseEnter ()
	{
		Control::OnMouseEnter();
	}

	void Button::OnMouseLeave ()
	{
		Control::OnMouseLeave();
	}

	void Button::OnMouseMove ()
	{
		Control::OnMouseMove();
	}

	void Button::OnMouseHover ()
	{
		Control::OnMouseHover();
	}

	void Button::OnMouseDown ()
	{
		Control::OnMouseDown();
	}

	void Button::OnMouseUp ()
	{
		Control::OnMouseUp();
	}

	void Button::OnMouseClick ()
	{
		Control::OnMouseClick();
	}
}
