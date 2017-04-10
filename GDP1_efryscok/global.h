#pragma once

#include <cstdlib>
#include <crtdbg.h>
#include <conio.h>
#include <time.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <array>
#include <cmath>

#include <glad\glad.h>
#include <glfw\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "MeshManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CommandManager.h"
#include "ParticleManager.h"
#include "CommandGroup.h"
#include "MoveTo.h"
#include "OrientTo.h"
#include "LuaBrain.h"
#include "Camera.h"
#include "Model.h"

#define _CRTDBG_MAP_ALLOC

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DBG_NEW
#endif // DBG_NEW
#endif // _DEBUG

extern float gDeltaTime;

extern GLFWwindow* gWindow;
extern CMeshManager* gMeshManager;
extern CShaderManager* gShaderManager;
extern CTextureManager* gTextureManager;
extern CCommandManager* gCommandManager;
extern CParticleManager* gParticleManager;
extern CLuaBrain* gLuaBrain;
extern CCamera* gCamera;
extern CModel* gSkyBox;
extern CModel* gSpaceShip;
extern CModel* gQuad;
extern std::vector<CModel*> gModels;
extern std::array<std::string, 6> gCubeMapFiles;

extern int randi(int low, int hi);
extern float randf(float low, float hi);