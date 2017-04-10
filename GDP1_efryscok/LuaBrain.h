#pragma once

extern "C" {
#include <Lua5.3.3\lua.h>
#include <Lua5.3.3\lua.h>
#include <Lua5.3.3\lauxlib.h>
#include <Lua5.3.3\lualib.h>
}

#include <string>
#include <vector>
#include <map>

class CModel;

class CLuaBrain {
public:
	CLuaBrain();
	~CLuaBrain();

	void loadScript(std::string scriptName, std::string scriptSource);
	void deleteScript(std::string scriptName);
	void setModelVector(std::vector<CModel*> * pModels);
	void update(float deltaTime);
	void runScriptImmediately(std::string script);
	
	static int sMoveTo(lua_State * L);
	static int sOrientTo(lua_State * L);
	static int sBeginCommands(lua_State * L);
	static int sEndCommands(lua_State * L);

private:
	std::map<std::string, std::string> mScripts;
	static std::vector<CModel*>* mpModels;
	lua_State * mpLuaState;

	std::string mDecodeLuaErrorToString(int error);
	void mScriptError(std::string script, std::string error);
};