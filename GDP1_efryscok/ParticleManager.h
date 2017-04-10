#pragma once

#include <glm\vec3.hpp>
#include <glm\vec4.hpp>
#include <vector>

struct SParticle {
public:
	SParticle() : life(0.f), colour(0.f, 0.f, 0.f, 1.f) {};

	float life;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	
	glm::vec4 colour;
};

struct SParticleDesc {
	SParticleDesc();

	bool regenerateParticles;
	bool isImposter;
	bool randomizeColours;
	bool alphaProportionalToLifeTime;

	int particlesCreatedPerUpdate;

	float lifetimeMin;
	float lifetimeMax;

	glm::vec3 initVelMin;
	glm::vec3 initVelMax;
	glm::vec3 ongoingForce;
	glm::vec3 rotationPerSecond;
	glm::vec3 imposterEyeLocation;

	glm::vec4 initColour;
	glm::vec4 colourRangeMin;
	glm::vec4 colourRangeMax;
};

class CParticleManager {
public:
	static const int kDefaultNumberOfParticles = 100;
	
	glm::vec3 position;

	SParticleDesc particleSettings;

public:
	bool allocatateParticles(int numberOfParticles, const SParticleDesc & initSettings, bool overwriteExisting = true);
	void update();
	int getParticlesCopy(std::vector<SParticle> & particles);
	void updateImposterEye(glm::vec3 eye);

private:
	std::vector<SParticle> mParticles;

private:
	glm::vec3 mCalcImposterRotationFromEye(glm::vec3 particlePosition);
	void mResetParticle(SParticle & particle);
	int mFindNextDeadParticle();
};