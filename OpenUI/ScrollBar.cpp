#include "stdafx.h"
#include "ScrollBar.h"

namespace OpenUI
{
	ScrollBar::ScrollBar ( const std::string & name )
		: Element ( name )
	{
	}

	ScrollBar::~ScrollBar ()
	{
	}

	void ScrollBar::Start ()
	{
		Element::Start();

		const auto bounds = GetBounds();
		m_thumbShape->setSize ( sf::Vector2f ( bounds.Size.X, 30 ) );
		m_thumbShape->setPosition ( sf::Vector2f ( bounds.Position.sfVector ) );
		m_thumbShape->setFillColor ( sf::Color::Blue );
		m_thumbBounds = IntRect ( bounds.X, bounds.Y, bounds.Width, 30 );
	}

	void ScrollBar::OnAdded ()
	{
		Element::OnAdded();

		const auto bounds = GetBounds();
		const auto parentBounds = GetParent()->GetBounds();
		SetSize ( IntVector ( 30, parentBounds.Position.Y - GetPosition().Y + parentBounds.Size.Y ) );
		SetPosition ( IntVector ( parentBounds.X + parentBounds.Width - 30, parentBounds.Y ) );

		m_thumbShape->setSize ( sf::Vector2f ( bounds.Size.X, 30 ) );
		m_thumbShape->setPosition ( sf::Vector2f ( bounds.Position.sfVector ) );
		m_thumbShape->setFillColor ( sf::Color::Blue );
		m_thumbBounds = IntRect ( bounds.X, bounds.Y, bounds.Width, 30 );
	}

	void ScrollBar::Update ()
	{
		Element::Update();

		if (!sInputInformation->MouseIsDown)
		{
			m_isMoving = false;
			m_thumbShape->setFillColor ( GetScheme().Colors.OutlineColor.Default );
			return;
		}

		if (!m_isMoving || !m_enableScroll)
		{
			return;
		}

		m_mouseRelativeToThumb.Y = sInputInformation->MousePosition.Y - m_thumbBounds.Size.Y / 2;
		MoveScrollThumb();
	}

	void ScrollBar::MoveScrollThumb ()
	{
		const auto thisBounds = GetBounds();
		auto thumbBounds = m_thumbBounds;
		const IntVector scrollableArea = thisBounds.Size - thumbBounds.Size;

		if (m_mouseRelativeToThumb.Y < thisBounds.Y)
		{
			m_mouseRelativeToThumb.Y = thisBounds.Y;
		}
		else if (m_mouseRelativeToThumb.Y > thisBounds.Y + thisBounds.Height - thumbBounds.Height)
		{
			m_mouseRelativeToThumb.Y = thisBounds.Y + thisBounds.Height - thumbBounds.Height;
		}

		thumbBounds.Position.Y = m_mouseRelativeToThumb.Y;
		m_thumbShape->setPosition ( m_thumbShape->getPosition().x, m_mouseRelativeToThumb.Y );

		const double mouseRelDelta = m_mouseRelativeToThumb.Y - thisBounds.Position.Y;
		const int scrollValue = mouseRelDelta / scrollableArea.Y * 100;
		MoveElements ( scrollValue );
	}

	void ScrollBar::MoveElements ( int p_scrollValue )
	{
		int const delta = m_virtualSize.Y / 100 * p_scrollValue - m_virtualSize.Y / 100 * m_scollValue;

		for (Element * child : GetParent()->GetChildren())
		{
			if (this == child)
			{
				continue;
			}
			child->SetPosition ( child->GetPosition() + IntVector ( 0, 0 - delta ) );
		}

		m_scollValue = p_scrollValue;
	}

	void ScrollBar::OnMouseDown ()
	{
		Element::OnMouseDown();

		m_thumbShape->setFillColor ( GetScheme().Colors.OutlineColor.Pressed );
		m_isMoving = true;
	}

	void ScrollBar::OnParentChildAdded ( Element * child )
	{
		Element::OnParentChildAdded ( child );

		const auto childbounds = child->GetBounds();
		const auto parentBounds = GetParent()->GetBounds();
		if (childbounds.Y + childbounds.Size.Y > m_virtualSize.Y)
		{
			m_virtualSize.Y = childbounds.Y - parentBounds.Y + childbounds.Size.Y;
		}
		SetScrollThumbHeight();
		//m_enableScroll = m_virtualSize.Y > parentBounds.Size.Y;
	}

	void ScrollBar::OnParentSizeChanged ( const IntVector & delta )
	{
		Element::OnParentSizeChanged ( delta );

		const auto parentBounds = GetParent()->GetBounds();
		//m_enableScroll = m_virtualSize.Y > parentBounds.Size.Y;
	}

	void ScrollBar::SetScrollThumbHeight ()
	{
		const IntRect thisBounds = GetBounds();
		const float viewableRatio = float ( thisBounds.Y ) / float ( m_virtualSize.Y );
		float scrollThumbHeight = thisBounds.Y * viewableRatio;

		if (scrollThumbHeight > thisBounds.Y / 2)
		{
			scrollThumbHeight = thisBounds.Y / 2;
		}

		m_thumbShape->setSize ( sf::Vector2f ( m_thumbBounds.Width, scrollThumbHeight ) );
		m_thumbBounds.Height = scrollThumbHeight;
	}

	void ScrollBar::Initialize ()
	{
		Element::Initialize();

		m_thumbShape = new sf::RectangleShape();
		AddShape ( m_thumbShape );
	}
}
