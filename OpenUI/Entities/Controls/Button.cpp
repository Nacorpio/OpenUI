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
		LOG(GetName());
	}

	void Button::OnMouseLeave ()
	{
		Control::OnMouseLeave();
		LOG(GetName());
	}

	void Button::OnMouseMove ()
	{
		Control::OnMouseMove();
		LOG(GetName());
	}

	void Button::OnMouseHover ()
	{
		Control::OnMouseHover();
		LOG(GetName());
	}

	void Button::OnMouseDown ()
	{
		Control::OnMouseDown();
		LOG(GetName());
	}

	void Button::OnMouseUp ()
	{
		Control::OnMouseUp();
		LOG(GetName());
	}

	void Button::OnMouseClick ()
	{
		Control::OnMouseClick();
		LOG(GetName());
	}
}
