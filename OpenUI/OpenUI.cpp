// OpenUI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Entities/Elements/Windows/ClientWindow.h>
#include <Entities/Controls/Button.h>
#include "Managers/ElementMgr.h"
#include "Managers/Controller.h"

int main ()
{
	//const sf::Image& myImage = sResourceMgr->CreateImage ( 100, 100, sf::Color::White );
	//const sf::Sprite& mySprite = sResourceMgr->CreateSprite ( myImage );
	//const sf::Font& myFont = sResourceMgr->CreateFont ( "AlegreyaSansSC-Regular.ttf" );

	OpenUI::ClientWindow* myClientWindow = sElementMgr->CreateClientWindow ( 0, "clientWindow" );
	OpenUI::Button* myButton = sElementMgr->CreateButton ( 2, "button0" );
	OpenUI::Button* myButton1 = sElementMgr->CreateButton ( 3, "button1" );
	OpenUI::WindowElement* myWindowElement = sElementMgr->CreateWindowElement(4, "windowElement0",30);
	
	myWindowElement->SetBounds({ 10,10,200,200 });
	myButton->SetBounds({ 0,0,100,100 });
	myButton1->SetBounds({ 0,100,100,100 });

	myWindowElement->SetBackgroundColor(sf::Color(60, 60, 60));
	myButton->SetBackgroundColor(sf::Color(90, 90, 90));

	OpenUI::Scheme* myScheme = new OpenUI::Scheme ();

	myScheme->Colors.BackColor = sf::Color::Red;
	myScheme->Colors.BackColor.Entered = sf::Color::Blue;
	myScheme->Colors.BackColor.Pressed = sf::Color::Green;

	myClientWindow->SetScheme(myScheme);
	myButton->SetScheme ( myScheme );
	myButton1->SetScheme ( myScheme );

	myButton->SetBounds ( { 100, 200, 100, 100 } );
	myButton1->SetBounds ( { 120, 120, 100, 100 } );

	myClientWindow->AddChild(myWindowElement);

	myWindowElement->AddChild(myButton);
	myWindowElement->AddChild(myButton1);
	sController->Start();

	std::cin.get ();
	return 0;
}
