#pragma once
#include "Entities/Elements/Element.h"
#include "Common/Global.h"

namespace OpenUI
{

	class ScrollBar : public Element
	{
	public:
		explicit ScrollBar(const std::string& name);
		~ScrollBar();

		void Start () override;

		void OnAdded () override;

		void Update () override;

		void Initialize() override;

		void OnMouseDown() override;

		void OnParentChildAdded(Element * child) override;

		void OnParentSizeChanged(const IntVector & delta) override;

		void MoveScrollThumb ();

		void MoveElements ( int p_scrollValue );

		void SetScrollThumbHeight ();

	private:
		sf::RectangleShape * m_thumbShape = nullptr;
		IntRect m_thumbBounds;
		IntRect m_virtualSize;
		IntVector m_mouseRelativeToThumb;
		double m_scollValue = 0;
		bool m_isMoving = false;
		bool m_enableScroll = true;

	};
	
}
