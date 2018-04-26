#include "stdafx.h"
#include "Button.h"
#include <iostream>

namespace OpenUI
{
	Button::Button ( const std::string& name )
		: Control ( name )
	{
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

	void Button::Draw ()
	{
		std::cout << "Button drawn" << std::endl;
	}
}
