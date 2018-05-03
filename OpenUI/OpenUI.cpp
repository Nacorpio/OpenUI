// OpenUI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Entities/Elements/Windows/ClientWindow.h>
#include <Entities/Controls/Button.h>
#include "Managers/ElementMgr.h"
#include "Managers/Controller.h"
#include "Graphic/Scheme.h"

int main ()
{
	//const sf::Image& myImage = sResourceMgr->CreateImage ( 100, 100, sf::Color::White );
	//const sf::Sprite& mySprite = sResourceMgr->CreateSprite ( myImage );
	//const sf::Font& myFont = sResourceMgr->CreateFont ( "AlegreyaSansSC-Regular.ttf" );

	OpenUI::ClientWindow* myClientWindow = sElementMgr->CreateClientWindow ( 0, "clientWindow" );
	OpenUI::Button* myButton = sElementMgr->CreateButton ( 2, "button0" );
	OpenUI::Button* myButton1 = sElementMgr->CreateButton ( 3, "button1" );

	OpenUI::Scheme* myScheme = new OpenUI::Scheme ();

	myScheme->Colors.BackColor = sf::Color::Red;
	myScheme->Colors.BackColor.Entered = sf::Color::Blue;
	myScheme->Colors.BackColor.Pressed = sf::Color::Green;

	myClientWindow->SetScheme(myScheme);
	myButton->SetScheme ( myScheme );
	myButton1->SetScheme ( myScheme );

	myButton->SetBounds ( { 100, 200, 100, 100 } );
	myButton1->SetBounds ( { 120, 120, 100, 100 } );

	//myButton->GetShape(0)->setFillColor(sf::Color::Red);
	//myButton1->GetShape(0)->setFillColor(sf::Color::Blue);
	myClientWindow->AddChild ( myButton );
	myButton->AddChild ( myButton1 );

	sController->Start ();

	std::cin.get ();
	return 0;
}
