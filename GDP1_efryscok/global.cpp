#include "global.h"

float gDeltaTime = 0.f;

GLFWwindow* gWindow = nullptr;
CMeshManager* gMeshManager = nullptr;
CShaderManager* gShaderManager = nullptr;
CTextureManager* gTextureManager = nullptr;
CCommandManager* gCommandManager = nullptr;
CParticleManager* gParticleManager = nullptr;
CLuaBrain* gLuaBrain = nullptr;
CCamera* gCamera = nullptr;
CModel* gSkyBox = nullptr;
CModel* gSpaceShip = nullptr;
CModel* gQuad = nullptr;
std::vector<CModel*> gModels;
std::array<std::string, 6> gCubeMapFiles;

int randi(int low, int hi) {
	return rand() % hi + low;
}

float randf(float low, float hi) {
	return low + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (hi - low)));
}
