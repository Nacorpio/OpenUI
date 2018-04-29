#pragma once
#include "Graphic/ColorScheme.h"

namespace OpenUI
{
	class ColorManager
	{
	public:
		static ColorManager* instance()
		{
			static ColorManager instance;
			return &instance;
		}

		void Add(ElementType p_elementType, ColorScheme & p_scheme)
		{
			m_colorSchemes.insert_or_assign(p_elementType, p_scheme);
		}


		~ColorManager();

	private:
		std::unordered_map<ElementType, ColorScheme &> m_colorSchemes;
	};
}
#define sColorMgr OpenUI::ColorManager::instance()
