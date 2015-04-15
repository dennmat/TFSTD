#pragma once

#include "GameProcess.h"

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <list>
#include <map>

namespace Core {
	class Engine {
	public:
		typedef std::list<GameProcessInterface*> ProcessList;
		typedef ProcessList::iterator ProcessListIt;

	private:
		ProcessList processes;

		bool isRunning;
	
	public:

		//typedef std::map<ProcessTypes, GameProcessInterface*> ProcessMap;
		//typedef ProcessMap::iterator ProcessMapIt;

		Engine();	
		~Engine();

		void SetProcess(GameProcessInterface::ProcessType type);
		void OverlayProcess(GameProcessInterface::ProcessType type);

		GameProcessInterface* ProcessFromType(GameProcessInterface::ProcessType type);
		void ClearProcesses();

		void Load(int argc, char** argv);
		void Start(void);
	
		void Render(void);
		void Update(void);

		void KeyDownEvent(unsigned char key, int mouseX, int mouseY);
		void KeyUpEvent(unsigned char key, int mouseX, int mouseY);

		void MouseMoveEvent(void);

		void Close(void);
	};
}

