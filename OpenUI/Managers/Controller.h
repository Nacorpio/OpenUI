#pragma once
#include "Entities/Elements/Windows/ClientWindow.h"
#include "Managers/ElementMgr.h"
#include <iostream>
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
			StartAndInitWindows();
			InputAndUpdateWindows();
			ProgramLoop();
		}

		std::set <ClientWindow*> & GetClientWindows() const
		{
			return *m_clientWindows;
		}

	private:

		void ProgramLoop() const
		{
			sf::Clock clock;


			int nextTick = clock.getElapsedTime().asMilliseconds();
			int loops = 0;
			long previousUpdate = 1, currentUpdate = 1, delta = 0,previousFPSUpdate = 0, nextFPSUpdate = nextTick + 1000;
			float interpolation = 0;

			double frames = 0;
			double frameTime = 0;
			const bool enablePerformanceProfiler = false;

			while (true)
			{
				sTimeInformation->ElapsedTime = clock.getElapsedTime().asMilliseconds();

				loops = 0;

				while (sTimeInformation->ElapsedTime > nextTick && loops < sTimeInformation->MaxFrameSkips)
				{
					InputAndUpdateWindows();
					nextTick += sTimeInformation->SkipTicks;
					++loops;
				}

				previousUpdate = currentUpdate;
				currentUpdate = sTimeInformation->ElapsedTime;

				DrawWindows();

				if(enablePerformanceProfiler)
				{
					if (currentUpdate > nextFPSUpdate)
					{
						frameTime = 1000 / (frames);
						LOG("Frames: " << frames << " frameTime: " << frameTime << " SkipTicks: " << sTimeInformation->SkipTicks << " loops: " << loops);
						frames = 0;
						nextFPSUpdate = currentUpdate + 1000;
					}
					++frames;
				}
			}
			
		}

		/// <summary>
		///		Starts and initializes the windows which will start and initialize the elements.
		/// </summary>
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
		///		Input and update the clientwindow(s).
		/// </summary>
		void InputAndUpdateWindows() const
		{
			ClientWindow * clientWindow = nullptr;
			for (auto it = m_clientWindows->begin(); it != m_clientWindows->end(); ++it)
			{
				clientWindow = it._Ptr->_Myval;
				clientWindow->Input();
				clientWindow->Update();
			}
		}

		void DrawWindows() const
		{
			ClientWindow * clientWindow = nullptr;
			for (auto it = m_clientWindows->begin(); it != m_clientWindows->end(); ++it)
			{
				clientWindow = it._Ptr->_Myval;
				clientWindow->Draw(*m_graphicsContext);
			}
		}

		std::set <ClientWindow*> * m_clientWindows = nullptr;
		GraphicsContext* m_graphicsContext = nullptr;
	};
	
}
#define sController OpenUI::Controller::instance()
