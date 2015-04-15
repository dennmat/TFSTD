#include "LuaProgram.h"

#include <iostream>

using namespace Core;

LuaProgram::LuaProgram(void) : L(nullptr) {}

LuaProgram::~LuaProgram(void) {
	if (this->L != nullptr) {
		lua_close(this->L);
		this->L = nullptr;
	}
}

void LuaProgram::InitializeProgram(std::string compiledFileName) {
	this->compiledFileName = compiledFileName;
	this->L = luaL_newstate();
	
	if (luaL_loadfile(this->L, this->compiledFileName.c_str())) {
		std::cout << "Lua failed to load file " << compiledFileName << " error: " << lua_tostring(this->L, -1) << std::endl;
		std::terminate();
	}
}

void LuaProgram::Run() {
	if (lua_pcall(this->L, 0, 0, 0)) {
		std::cout << "Lua failed to execute file " << compiledFileName << " error: " << lua_tostring(this->L, -1) << std::endl;
		std::terminate();
	}
}

TFSint LuaProgram::GetIntFromLua(std::string name) {
	lua_getglobal(this->L, name.c_str());

	if (!lua_isnumber(this->L, -1)) {
		luaL_error(this->L, "'%s' should be a number", name);
		return 0; //Perhaps throw? but speed bro
	}

	return (TFSint)lua_tonumber(this->L, -1);
}

std::string LuaProgram::GetStrFromLua(std::string name) {
	lua_getglobal(this->L, name.c_str());

	if (!lua_isstring(this->L, -1)) {
		luaL_error(this->L, "'", name, "' should be a string.");
		return "";
	}

	return (std::string)lua_tostring(this->L, -1);
}

bool LuaProgram::GetBoolFromLua(std::string name) {
	lua_getglobal(this->L, name.c_str());
	
	if (!lua_isboolean(this->L, -1)){
		luaL_error(this->L, "'", name, "' should be a boolean.");
		return 0;
	}

	return lua_toboolean(this->L, -1);
}

double LuaProgram::GetDoubleFromLua(std::string name) {
	lua_getglobal(this->L, name.c_str());

	if (!lua_isnumber(this->L, -1)) {
		luaL_error(this->L, "'", name, "' should be double.");
		return 0.0;
	}

	return (double)lua_tonumber(this->L, -1);
}