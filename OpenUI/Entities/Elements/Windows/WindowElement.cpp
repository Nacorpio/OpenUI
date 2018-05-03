#include "stdafx.h"
#include "WindowElement.h"

namespace OpenUI
{
	WindowElement::WindowElement(const std::string& p_name, const uint16_t & p_headerSize)
		: Element(p_name)
	{m_guidDetail = ObjectGuid::Detail::WindowElement;	}

	WindowElement::~WindowElement()
	{
	}

	void WindowElement::Start () const
	{
		Element::Start();
	}

	void WindowElement::Initialize ()
	{
		Element::Initialize();

		const auto bounds = GetBounds();
		m_headerBar = new sf::RectangleShape(sf::Vector2f(bounds.Size.X, m_headerHeight));
		m_headerBar->setPosition(sf::Vector2f(bounds.Position.sfVector));
		m_headerBar->setFillColor(sf::Color(160, 160, 160));
		AddShape(m_headerBar);

		SetContainerRectangle(IntRect(bounds.X, bounds.Y + m_headerHeight, bounds.Width, bounds.Height - m_headerHeight));
	}

	void WindowElement::Update ( )
	{
		Element::Update ( );
		if (!m_isMousePressedHeader)
		{
			return;
		}
		DragWindow();
	}

	void WindowElement::Draw ( const GraphicsContext & gContext )
	{
		Element::Draw(gContext);
	}

	void WindowElement::OnMouseEnter ()
	{
		Element::OnMouseEnter();
	}

	void WindowElement::OnMouseLeave ()
	{
		Element::OnMouseLeave();
	}

	void WindowElement::OnMouseMove ()
	{
		Element::OnMouseMove();
	}

	void WindowElement::OnMouseHover ()
	{
		Element::OnMouseHover();
	}

	void WindowElement::OnMouseUp ()
	{
		Element::OnMouseUp();
		m_isMousePressedHeader = false;
	}

	void WindowElement::OnMouseDown ()
	{
		Element::OnMouseDown();
		m_isMousePressedHeader = CheckMouseDownHeader();
	}

	void WindowElement::OnMouseClick ()
	{
		Element::OnMouseClick();
		m_isMousePressedHeader = false;
	}

	void WindowElement::OnDrop ( const InputHandler::MouseDropEvent & event )
	{
		Element::OnDrop(event);
	}

	void WindowElement::OnDragBegin ()
	{
		Element::OnDragBegin();
	}

	void WindowElement::OnBoundsChanged ( const IntRect & delta )
	{
		Element::OnBoundsChanged ( delta );
		const auto bounds = GetBounds();
		SetContainerRectangle(IntRect(bounds.X, bounds.Y + m_headerHeight, bounds.Width, bounds.Height - m_headerHeight));
		m_headerBar->setSize ( sf::Vector2f ( bounds.Size.sfVector.x, m_headerHeight ) );
		m_headerBar->setPosition ( sf::Vector2f (bounds.Position.sfVector ) );
	}
}
