// OpenUI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Managers/ElementMgr.h"
#include <iostream>
#include "Managers/ResourceMgr.h"

int main()
{
	sf::Font& font = sResourceMgr->CreateFont("AlegreyaSansSC-Regular.ttf");
	std::cin.get ();

    return 0;
}

