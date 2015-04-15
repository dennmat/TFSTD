#include "Engine.h"

#include <iostream>

using namespace Core;

Engine::Engine() : isRunning(true)
{}

Engine::~Engine() {
	this->ClearProcesses();
}

void Engine::Load(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Triple Foot Smash");

	glewInit();
	if (glewIsSupported("GL_VERSION_4_4")) {
		std::cout << "GLEW Version is 4.4\n";
	}
	else {
		std::cout << "GLEW 4.4 not supported\n";
	}

	//std::cout << "A" << std::endl;
	//Core::LuaLoader ll;
	//ll.LoadProgram("C:\\Users\\dennm_000\\Documents\\Visual Studio 2013\\Projects\\tfstd\\Debug\\test.lua");
	//std::cout << "A" << std::endl;
	//Core::LuaProgram lp;
	//lp.InitializeProgram("C:\\Users\\dennm_000\\Documents\\Visual Studio 2013\\Projects\\tfstd\\Debug\\test.tfsb");
	//std::cout << "A" << std::endl;
	//lp.Run();
	//std::cout << "A" << std::endl;
	//std::cout << "Result: " << lp.GetIntFromLua("testint") << std::endl;
	
	for (ProcessListIt it = this->processes.begin(); it != this->processes.end(); it++) {
		(*it)->PreLoad();
	}
}

void Engine::Start() {
	for (ProcessListIt it = this->processes.begin(); it != this->processes.end(); it++) {
		(*it)->Load();
	}

	while (this->isRunning) {
		glutMainLoopEvent();
		this->Update();
		this->Render();
	}
}

void Engine::SetProcess(GameProcessInterface::ProcessType type) {
	this->ClearProcesses();

	GameProcessInterface* gpi = this->ProcessFromType(type);

	this->processes.push_back(gpi);
}

void Engine::OverlayProcess(GameProcessInterface::ProcessType type) {
	GameProcessInterface* gpi = this->ProcessFromType(type);

	this->processes.push_back(gpi);
}

GameProcessInterface* Engine::ProcessFromType(GameProcessInterface::ProcessType type) {
	switch (type) {
		case GameProcessInterface::ProcessType::Game:
			return (GameProcessInterface*)new GameProcess();
		break;
	}
}

void Engine::ClearProcesses() {
	for (ProcessListIt it = this->processes.begin(); it != this->processes.end(); it++) {
		(*it)->Destroy();
		delete *it;
	}

	this->processes.clear();
}

void Engine::KeyDownEvent(unsigned char key, int mouseX, int mouseY) {

}

void Engine::KeyUpEvent(unsigned char key, int mouseX, int mouseY) {

}

void Engine::MouseMoveEvent() {

}

void Engine::Update()  {

}

void Engine::Render() {
	for (ProcessListIt it = this->processes.begin(); it != this->processes.end(); it++) {
		(*it)->Render();
	}
}
