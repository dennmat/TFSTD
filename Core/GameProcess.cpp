#include "GameProcess.h"

using namespace Core;

GameProcess::GameProcess() {
	this->type = ProcessType::Game;
	this->state = ProcessState::PreInit;
}

GameProcess::~GameProcess() {
}

void GameProcess::Load() {
	glEnable(GL_DEPTH_TEST);

	Core::ShaderLoader shaderLoader;
	program = shaderLoader.CreateProgram("Shaders\\Vertex_Shader.glsl", "Shaders\\Fragment_Shader.glsl");

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	this->state = ProcessState::Ready;
}

void GameProcess::PreLoad(void) {
	this->state = ProcessState::Initialized;
}

void GameProcess::Render(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0);//clear red

	//use the created program
	glUseProgram(this->program);

	//draw 3 vertices as triangles
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
}

void GameProcess::Update(void) {}

void GameProcess::Destroy(void) {
	this->state = ProcessState::Destroying;

	glDeleteProgram(this->program);

	this->state = ProcessState::Destroyed;
}

void GameProcess::Event(void) {}