#pragma once

#include <string>
#include <vector>
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <glm\gtc\quaternion.hpp>

class CModel {
public:
	bool isWireframe;
	bool useDebugColours;
	bool isVisible;
	bool isImposter;
	bool isUpdatedByPhysics;
	bool isCubeMap;

	float scale;
	float alpha;
	float movementSpeed;

	std::string mesh;
	std::string texture;

	std::vector<std::string> textures;
	std::vector<CModel*> children;

	glm::vec3 velocity;
	glm::vec3 acceleration;
	glm::vec3 position;
	glm::vec3 lastPosition;
	glm::vec3 rotSpeed;
	glm::vec4 colour;
	glm::vec3 offset;

	glm::mat4 modelMatrix;

	glm::quat orientation;

private:
	int mUniqueID;
	static int mNextID;

public:
	CModel();
};

