#include "global.h"

std::vector<CModel*> * CLuaBrain::mpModels;

CLuaBrain::CLuaBrain() {
	mpModels = nullptr;
	mpLuaState = luaL_newstate();

	luaL_openlibs(mpLuaState);

	lua_pushboolean(mpLuaState, true);
	lua_setglobal(mpLuaState, "time");

	lua_pushboolean(mpLuaState, false);
	lua_setglobal(mpLuaState, "speed");

	lua_pushboolean(mpLuaState, true);
	lua_setglobal(mpLuaState, "serial");

	lua_pushboolean(mpLuaState, false);
	lua_setglobal(mpLuaState, "parallel");

	lua_pushcfunction(mpLuaState, CLuaBrain::sMoveTo);
	lua_setglobal(mpLuaState, "moveTo");

	lua_pushcfunction(mpLuaState, CLuaBrain::sOrientTo);
	lua_setglobal(mpLuaState, "orientTo");

	lua_pushcfunction(mpLuaState, CLuaBrain::sBeginCommands);
	lua_setglobal(mpLuaState, "beginCommands");

	lua_pushcfunction(mpLuaState, CLuaBrain::sEndCommands);
	lua_setglobal(mpLuaState, "endCommands");
}

CLuaBrain::~CLuaBrain() {
	lua_close(mpLuaState);
}

void CLuaBrain::loadScript(std::string scriptName, std::string scriptSource) {
	mScripts[scriptName] = scriptSource;
}

void CLuaBrain::deleteScript(std::string scriptName) {
	mScripts.erase(scriptName);
}

void CLuaBrain::setModelVector(std::vector<CModel*> * pModels) {
	mpModels = pModels;
}

void CLuaBrain::update(float deltaTime) {
	for (std::map<std::string, std::string>::iterator itScript = mScripts.begin(); itScript != mScripts.end(); ++itScript) {
		std::string currentLuaScript = itScript->second;

		int error = luaL_loadstring(mpLuaState, currentLuaScript.c_str());

		if (error != 0) {
			mScriptError(itScript->first, mDecodeLuaErrorToString(error));
			continue;
		}

		error = lua_pcall(mpLuaState, 0, 0, 0);

		if (error != 0) {
			std::string luaError;
			// Get error information from top of stack (-1 is top)
			luaError.append(lua_tostring(mpLuaState, -1));

			mScriptError(itScript->first, mDecodeLuaErrorToString(error) + " - " + luaError);

			// We passed zero (0) as errfunc, so error is on stack)
			lua_pop(mpLuaState, 1);  /* pop error message from the stack */

			continue;
		}
	}
}

void CLuaBrain::runScriptImmediately(std::string script) {
	int error = luaL_loadstring(mpLuaState, script.c_str());

	if (error != 0) {
		mScriptError(script, mDecodeLuaErrorToString(error));
		return;
	}

	error = lua_pcall(mpLuaState, 0, 0, 0);

	if (error != 0) {
		std::string luaError;
		// Get error information from top of stack (-1 is top)
		luaError.append(lua_tostring(mpLuaState, -1));

		mScriptError(script, mDecodeLuaErrorToString(error) + " - " + luaError);

		lua_pop(mpLuaState, 1);  /* pop error message from the stack */
	}
}

int CLuaBrain::sMoveTo(lua_State * L) {
	CMoveTo * command = new CMoveTo();
	command->initialize(
		glm::vec3(
			static_cast<float>(lua_tonumber(L, 1)),
			static_cast<float>(lua_tonumber(L, 2)),
			static_cast<float>(lua_tonumber(L, 3))),
		lua_toboolean(L, 4) != 0,
		static_cast<float>(lua_tonumber(L, 5))
	);

	gCommandManager->addCommand(lua_toboolean(L, 6) != 0, command);

	return 0;
}

int CLuaBrain::sOrientTo(lua_State * L) {
	COrientTo * command = new COrientTo();
	command->initialize(
		glm::vec3(
			static_cast<float>(lua_tonumber(L, 1)),
			static_cast<float>(lua_tonumber(L, 2)),
			static_cast<float>(lua_tonumber(L, 3))),
		lua_toboolean(L, 4) != 0,
		static_cast<float>(lua_tonumber(L, 5))
	);

	gCommandManager->addCommand(lua_toboolean(L, 6) != 0, command);

	return 0;
}

int CLuaBrain::sBeginCommands(lua_State * L) {
	gCommandManager->beginCommandGroup();

	return 0;
}

int CLuaBrain::sEndCommands(lua_State * L) {
	gCommandManager->endCommandGroup();

	return 0;
}

std::string CLuaBrain::mDecodeLuaErrorToString(int error) {
	switch (error) {
	case 0:
		return "Lua: no error";
		break;
	case LUA_ERRSYNTAX:
		return "Lua: syntax error";
		break;
	case LUA_ERRMEM:
		return "Lua: memory allocation error";
		break;
	case LUA_ERRRUN:
		return "Lua: Runtime error";
		break;
	case LUA_ERRERR:
		return "Lua: Error while running the error handler function";
		break;
	}

	return "Lua: UNKNOWN error";
}

void CLuaBrain::mScriptError(std::string script, std::string error) {
	std::cout << "-------------------------------------------------------" << std::endl;
	std::cout << "Error running Lua script: ";
	std::cout << script << std::endl;
	std::cout << error << std::endl;
	std::cout << "-------------------------------------------------------" << std::endl;
}
