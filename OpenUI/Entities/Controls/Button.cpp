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
		//LOG("Button: " << GetName() << " Height: " << GetHeight());
		GetShape(0)->setFillColor(sf::Color(75,75,75));
	}

	void Button::OnMouseLeave ()
	{
		Control::OnMouseLeave();
		//LOG("		Button: " << GetName() << " Height: " << GetHeight());
		GetShape(0)->setFillColor(sf::Color(45, 45, 45));
	}

	void Button::OnMouseMove ()
	{
		Control::OnMouseMove();
		GetShape(0)->setFillColor(sf::Color(75, 75, 75));
	}

	void Button::OnMouseHover ()
	{
		Control::OnMouseHover();
	}

	void Button::OnMouseDown ()
	{
		Control::OnMouseDown();
		GetShape(0)->setFillColor(sf::Color(125, 125, 125));
	}

	void Button::OnMouseUp ()
	{
		Control::OnMouseUp();
		GetShape(0)->setFillColor(sf::Color(45, 45, 45));
	}

	void Button::OnMouseClick ()
	{
		Control::OnMouseClick();
		GetShape(0)->setFillColor(sf::Color(75, 75, 75));
	}
}
