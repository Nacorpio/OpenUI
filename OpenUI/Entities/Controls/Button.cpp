#include "stdafx.h"
#include "Button.h"
#include <iostream>

namespace OpenUI
{
	Button::Button ( const std::string& name )
		: Element(name)
	{
		m_guidDetail = ObjectGuid::Detail::Button;
	}

	Button::~Button ()
	{
	}

	void Button::Start ()
	{
	}

	void Button::Initialize ()
	{
		std::cout << "Button initialized" << std::endl;
	}

	void Button::Update ()
	{
		std::cout << "Button updated" << std::endl;
	}


}
