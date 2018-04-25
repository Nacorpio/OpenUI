// OpenUI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Managers/ElementMgr.h"
#include <iostream>
#include "Managers/ResourceMgr.h"

int main()
{
	sf::Image& myImage = sResourceMgr->CreateImage(100, 100, sf::Color::White);
	sf::Sprite& mySprite = sResourceMgr->CreateSprite(myImage);

	sf::Font& font = sResourceMgr->CreateFont("AlegreyaSansSC-Regular.ttf");
	std::cin.get ();

    return 0;
}

