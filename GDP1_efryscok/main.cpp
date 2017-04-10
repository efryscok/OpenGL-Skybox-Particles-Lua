#include "global.h"

// Methods
void initialize();
void setupShaderManager();
void setupMeshManager();
void setupTextureManager();
void setupCommandManager();
void setupParticleManager();
void shutdown(const std::string& msg);
void update();

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	srand(static_cast<unsigned int>(time(NULL)));

	initialize();

	double lastTime = glfwGetTime();
	static const float kMaxDeltaTime = 0.1f;

	gCamera = new CCamera();
	gCamera->offset = glm::vec3(0.f, 2.5f, 5.f);
	gCamera->movementSpeed = .1f;

	gSpaceShip = new CModel();
	gSpaceShip->mesh = "spaceShip.obj";
	gSpaceShip->texture = "spaceShipColour.bmp";
	gModels.push_back(gSpaceShip);
	
	{
		CModel * spaceShip = new CModel();
		spaceShip->mesh = "spaceShip.obj";
		spaceShip->texture = "spaceShipBlackWhite.bmp";
		spaceShip->position.x = 15.f;
		spaceShip->position.z = 0.f;
		gModels.push_back(spaceShip);
	}
	{
		CModel * spaceShip = new CModel();
		spaceShip->mesh = "spaceShip.obj";
		spaceShip->texture = "spaceShipBlackWhite.bmp";
		spaceShip->position.x = 0.f;
		spaceShip->position.z = 15.f;
		gModels.push_back(spaceShip);
	}
	{
		CModel * spaceShip = new CModel();
		spaceShip->mesh = "spaceShip.obj";
		spaceShip->texture = "spaceShipBlackWhite.bmp";
		spaceShip->position.x = 15.f;
		spaceShip->position.z = 15.f;
		gModels.push_back(spaceShip);
	}
	{
		CModel * spaceShip = new CModel();
		spaceShip->mesh = "spaceShip.obj";
		spaceShip->texture = "spaceShipBlackWhite.bmp";
		spaceShip->position.x = -15.f;
		spaceShip->position.z = 0.f;
		gModels.push_back(spaceShip);
	}
	{
		CModel * spaceShip = new CModel();
		spaceShip->mesh = "spaceShip.obj";
		spaceShip->texture = "spaceShipBlackWhite.bmp";
		spaceShip->position.x = 0.f;
		spaceShip->position.z = -15.f;
		gModels.push_back(spaceShip);
	}
	{
		CModel * spaceShip = new CModel();
		spaceShip->mesh = "spaceShip.obj";
		spaceShip->texture = "spaceShipBlackWhite.bmp";
		spaceShip->position.x = -15.f;
		spaceShip->position.z = -15.f;
		gModels.push_back(spaceShip);
	}
	{
		CModel * spaceShip = new CModel();
		spaceShip->mesh = "spaceShip.obj";
		spaceShip->texture = "spaceShipBlackWhite.bmp";
		spaceShip->position.x = 15.f;
		spaceShip->position.z = -15.f;
		gModels.push_back(spaceShip);
	}
	{
		CModel * spaceShip = new CModel();
		spaceShip->mesh = "spaceShip.obj";
		spaceShip->texture = "spaceShipBlackWhite.bmp";
		spaceShip->position.x = -15.f;
		spaceShip->position.z = 15.f;
		gModels.push_back(spaceShip);
	}

	gSkyBox = new CModel();
	gSkyBox->mesh = "skybox.ply";
	gSkyBox->texture = "space";
	gSkyBox->position = gCamera->position;
	gSkyBox->scale = 100.f;
	gSkyBox->isCubeMap = true;
	gModels.push_back(gSkyBox);

	gQuad = new CModel();
	gQuad->scale = 0.125f;
	gQuad->mesh = "quad.ply";
	gQuad->texture = "smoke.bmp";
	gQuad->isImposter = true;

	std::string luaScript = "";
	std::ifstream luaStream("commands.lua", std::ios::in);
	if (luaStream.is_open()) {
		std::string line = "";

		while (std::getline(luaStream, line)) {
			luaScript += "\n" + line;
		}

		luaStream.close();
	}

	gLuaBrain = new CLuaBrain();
	gLuaBrain->runScriptImmediately(luaScript);

	do {
		glfwGetFramebufferSize(gWindow, &gCamera->width, &gCamera->height);
		gCamera->aspectRatio = gCamera->width / (float)gCamera->height;

		gDeltaTime = float(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		if (gDeltaTime > kMaxDeltaTime) {
			gDeltaTime = kMaxDeltaTime;
		}

		glViewport(0, 0, gCamera->width, gCamera->height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		update();

		// Swap the glfw window buffers
		glfwSwapBuffers(gWindow);
		glfwPollEvents();
	} while (glfwGetKey(gWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(gWindow) == 0);
}

void initialize() {
	if (!glfwInit()) {
		std::cout << "[ERROR] Failed to initilize glfw" << std::endl << "Press any key to continue . . . ";
		_getch();
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "[INFO] Initialized glfw" << std::endl;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	gWindow = glfwCreateWindow(1200, 800, "Erik Fryscok", NULL, NULL);

	if (!gWindow) {
		shutdown("Failed to open glfw window");
	}
	else {
		std::cout << "[INFO] Opened glfw window" << std::endl;
	}

	glfwSetInputMode(gWindow, GLFW_STICKY_KEYS, GL_TRUE);
	glfwMakeContextCurrent(gWindow);
	glfwSwapInterval(1);
	
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glDepthFunc(GL_LESS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	setupShaderManager();
	setupMeshManager();
	setupTextureManager();
	setupCommandManager();
	setupParticleManager();
}

void setupShaderManager() {
	gShaderManager = new CShaderManager("assets/shaders/");

	// Load, attach, and compile the vertex and fragment shaders
	if (!gShaderManager->loadShaders("vertexShader.glsl", "fragmentShader.glsl")) {
		shutdown("Failed to load shaders");
	}
	else {
		std::cout << "[INFO] Loaded shader files" << std::endl;
	}

	gShaderManager->getUniformLocations();
}

void setupMeshManager() {
	gMeshManager = new CMeshManager("assets/models/");

	// List all the models and load them from file
	std::vector<std::string> modelFiles{
		"suzanne.obj",
		"box.obj",
		"skybox.ply",
		"spaceShip.obj",
		"quad.ply",
	};

	for (std::vector<std::string>::iterator it = modelFiles.begin(); it != modelFiles.end(); ++it) {
		if (gMeshManager->loadModel(*it)) {
			std::cout << "[INFO] Loaded model \"" << *it << "\"" << std::endl;
		}
	}
}

void setupTextureManager() {
	gTextureManager = new CTextureManager("assets/textures/");

	// List all the textures and load them from file
	std::vector<std::string> textureFiles{
		"bricks.bmp",
		"fence.bmp",
		"spaceShipBlackWhite.bmp",
		"spaceShipColour.bmp",
		"smoke.bmp",
	};

	for (std::vector<std::string>::iterator it = textureFiles.begin(); it != textureFiles.end(); ++it) {
		if (gTextureManager->loadTexture(*it)) {
			std::cout << "[INFO] Loaded texture \"" << *it << "\"" << std::endl;
		}
	}

	gCubeMapFiles = {
		"Right.bmp",
		"Left.bmp",
		"Top.bmp",
		"Bottom.bmp",
		"Front.bmp",
		"Back.bmp",
	};

	std::vector<std::string> skyBoxes{
		"space",
		"oceanSky",
	};

	for (std::vector<std::string>::iterator it = skyBoxes.begin(); it != skyBoxes.end(); ++it) {
		if (gTextureManager->loadCubeMap(*it, *it + gCubeMapFiles[0], *it + gCubeMapFiles[1], *it + gCubeMapFiles[2], *it + gCubeMapFiles[3], *it + gCubeMapFiles[4], *it + gCubeMapFiles[5])) {
			std::cout << "[INFO] Loaded cube map \"" << *it << "\"" << std::endl;
		}
	}
}

void setupCommandManager() {
	gCommandManager = new CCommandManager();
}

void setupParticleManager() {
	gParticleManager = new CParticleManager();

	SParticleDesc particleDesc;
	particleDesc.lifetimeMin = 2.f;
	particleDesc.lifetimeMax = 4.f;
	particleDesc.particlesCreatedPerUpdate = 20;
	particleDesc.ongoingForce = glm::vec3(0.f, 0.5f, 0.f);
	particleDesc.initVelMin = glm::vec3(-0.2f, 0.f, -0.2f);
	particleDesc.initVelMax = glm::vec3(0.2f, 1.f, 0.2f);

	gParticleManager->allocatateParticles(2000, particleDesc);
}

void shutdown(const std::string& msg) {
	std::cout << "[ERROR] " << msg << std::endl << "Press any key to continue . . . ";
	_getch();
	glfwTerminate();
	exit(EXIT_FAILURE);
}

void update() {
	if (glfwGetKey(gWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		if (glfwGetKey(gWindow, GLFW_KEY_UP) == GLFW_PRESS)				gCamera->orientationX *= glm::quat(glm::vec3(gCamera->movementSpeed, 0.f, 0.f));
		if (glfwGetKey(gWindow, GLFW_KEY_DOWN) == GLFW_PRESS)			gCamera->orientationX *= glm::quat(glm::vec3(-gCamera->movementSpeed, 0.f, 0.f));
		if (glfwGetKey(gWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)			gCamera->orientationY *= glm::quat(glm::vec3(0.f, gCamera->movementSpeed, 0.f));
		if (glfwGetKey(gWindow, GLFW_KEY_LEFT) == GLFW_PRESS)			gCamera->orientationY *= glm::quat(glm::vec3(0.f, -gCamera->movementSpeed, 0.f));

		if (glfwGetKey(gWindow, GLFW_KEY_ENTER) == GLFW_PRESS) {
			for (std::vector<CModel*>::iterator it = gModels.begin(); it != gModels.end(); ++it) {
				if ((*it)->texture == "spaceShipColour.bmp") {
					(*it)->texture = "spaceShipBlackWhite.bmp";
				}
			}

			gSkyBox->texture = "space";
			gSpaceShip->texture = "spaceShipColour.bmp";
		}
	}
	else {
		if (glfwGetKey(gWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)			gSpaceShip->position.x += gCamera->movementSpeed;
		if (glfwGetKey(gWindow, GLFW_KEY_LEFT) == GLFW_PRESS)			gSpaceShip->position.x -= gCamera->movementSpeed;
		if (glfwGetKey(gWindow, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)	gSpaceShip->position.y += gCamera->movementSpeed;
		if (glfwGetKey(gWindow, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)	gSpaceShip->position.y -= gCamera->movementSpeed;
		if (glfwGetKey(gWindow, GLFW_KEY_UP) == GLFW_PRESS)				gSpaceShip->position.z += gCamera->movementSpeed;
		if (glfwGetKey(gWindow, GLFW_KEY_DOWN) == GLFW_PRESS)			gSpaceShip->position.z -= gCamera->movementSpeed;

		if (glfwGetKey(gWindow, GLFW_KEY_A) == GLFW_PRESS)				gSpaceShip->orientation *= glm::quat(glm::vec3(0.f, gCamera->movementSpeed, 0.f));
		if (glfwGetKey(gWindow, GLFW_KEY_D) == GLFW_PRESS)				gSpaceShip->orientation *= glm::quat(glm::vec3(0.f, -gCamera->movementSpeed, 0.f));

		if (glfwGetKey(gWindow, GLFW_KEY_ENTER) == GLFW_PRESS) {
			for (std::vector<CModel*>::iterator it = gModels.begin(); it != gModels.end(); ++it) {
				if ((*it)->texture == "spaceShipBlackWhite.bmp") {
					(*it)->texture = "spaceShipColour.bmp";
				}
			}

			gSkyBox->texture = "oceanSky";
			gSpaceShip->texture = "spaceShipBlackWhite.bmp";
		}
	}

	gCamera->lookAt = gSpaceShip->position;
	gCamera->position = gSpaceShip->position + (gSpaceShip->orientation * gCamera->offset);
	gSkyBox->position = gCamera->position;

	gCamera->update();
	gShaderManager->update();
	gMeshManager->update();
	gCommandManager->update();
	gParticleManager->update();
}