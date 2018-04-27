#pragma once
#include "Entities/Elements/Windows/ClientWindow.h"
#include "Managers/ElementMgr.h"
#include "Managers/StateManager.h"
#include "InputContext.h"

namespace OpenUI
{
	class Controller
	{
	public:
		static Controller* instance()
		{
			static Controller instance;
			return &instance;
		}

		void Start()
		{
			m_clientWindows = &sElementMgr->m_clientWindows;
			//m_inputContext = new InputContext(m_stateManager, m_stateManager.GetMousePosition());
			StartAndInitWindows();
			DrawAndUpdateWindows();
			ProgramLoop();
		}

		std::set <ClientWindow*> & GetClientWindows() const
		{
			return *m_clientWindows;
		}

	private:

		void ProgramLoop()
		{
			while (true)
			{
				DrawAndUpdateWindows();
			}
		}

		void StartAndInitWindows() const
		{
			ClientWindow * clientWindow = nullptr;
			for (auto it = m_clientWindows->begin(); it != m_clientWindows->end(); ++it)
			{
				clientWindow = it._Ptr->_Myval;
				clientWindow->Start();
				clientWindow->Initialize();
			}
		}

		/// <summary>
		///		Draw and update the clientwindow(s).
		/// </summary>
		void DrawAndUpdateWindows()
		{
			ClientWindow * clientWindow = nullptr;
			for (auto it = m_clientWindows->begin(); it != m_clientWindows->end(); ++it)
			{
				clientWindow = it._Ptr->_Myval;
				m_stateManager.CheckMouseIntersection(clientWindow);
				clientWindow->Update();
				clientWindow->Draw(*m_graphicsContext);
			}
		}

		std::set <ClientWindow*> * m_clientWindows;
		GraphicsContext* m_graphicsContext;
		StateManager m_stateManager{};
		InputContext * m_inputContext = nullptr;
	};
	
}
#define sController OpenUI::Controller::instance()
