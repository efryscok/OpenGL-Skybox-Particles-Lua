#pragma once

#include <glm\vec4.hpp>
#include <string>
#include <vector>
#include <map>

class CModel;

struct SMeshEntry {
	GLuint vertexArrayID;
	int numIndices;
	int baseIndex;
	int baseVertex;
};

struct SMeshVertex {
	glm::vec4 position;
	glm::vec4 texCoord;
	glm::vec4 normal;
};

class CMeshManager {
private:
	GLuint mTexCoordBufferID;
	GLuint mNormalBufferID;
	GLuint mIndexBufferID;
	std::string mRootDir;
	std::vector<SMeshVertex> mVertices;
	std::vector<unsigned int> mIndices;
	std::map<std::string, SMeshEntry> mMeshInfo;

public:
	CMeshManager(std::string rootDir) : mRootDir(rootDir) {}
	~CMeshManager() {}

	bool loadModel(std::string modelFile);
	void update();
	void update(CModel * model);
};

