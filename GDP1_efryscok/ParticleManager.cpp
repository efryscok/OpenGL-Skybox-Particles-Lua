#include "global.h"

SParticleDesc::SParticleDesc() {
	regenerateParticles = true;
	alphaProportionalToLifeTime = false;
	
	particlesCreatedPerUpdate = 1;

	lifetimeMin = 0.f;
	lifetimeMax = 60.f;

	initVelMin = glm::vec3(-1.f, -1.f, -1.f);
	initVelMax = glm::vec3(1.f, 1.f, 1.f);
	ongoingForce = glm::vec3(0.f, 0.f, 0.f);

	initColour = glm::vec4(1.f, 1.f, 1.f, 1.f);
	colourRangeMin = glm::vec4(0.f, 0.f, 0.f, 1.f);
	colourRangeMax = glm::vec4(1.f, 1.f, 1.f, 1.f);
}

bool CParticleManager::allocatateParticles(int numberOfParticles, const SParticleDesc & initSettings, bool overwriteExisting) {
	particleSettings = initSettings;
	mParticles.reserve(numberOfParticles);

	SParticle tempParticle;

	for (int i = 0; i < numberOfParticles; ++i) {
		mParticles.push_back(tempParticle);
	}

	return true;
}

void CParticleManager::mResetParticle(SParticle & particle) {
	particle.life = randf(particleSettings.lifetimeMin, particleSettings.lifetimeMax);
	particle.colour = particleSettings.initColour;
	particle.velocity = glm::vec3(
		randf(particleSettings.initVelMin.x, particleSettings.initVelMax.x),
		randf(particleSettings.initVelMin.y, particleSettings.initVelMax.y),
		randf(particleSettings.initVelMin.z, particleSettings.initVelMax.z)
	);
	particle.position = position;
}

int CParticleManager::mFindNextDeadParticle() {
	for (size_t i = 0; i < mParticles.size(); ++i) {
		if (mParticles[i].life <= 0.f) {
			return i;
		}
	}

	return -1;
}

void CParticleManager::update() {
	position = gSpaceShip->position - (gSpaceShip->orientation * glm::vec3(0.f, 0.f, -.5f));
	particleSettings.imposterEyeLocation = gCamera->position;

	for (int i = 0; i < particleSettings.particlesCreatedPerUpdate; ++i) {
		int deadParticle = mFindNextDeadParticle();

		if (deadParticle >= 0) {
			mResetParticle(mParticles[deadParticle]);
		}
	}

	for (size_t i = 0; i < mParticles.size(); ++i) {
		mParticles[i].life -= gDeltaTime;
	}

	std::vector<SParticle> particles;
	int numParticles = getParticlesCopy(particles);

	for (int i = 0; i < numParticles; ++i) {
		gQuad->position = particles[i].position;
		gMeshManager->update(gQuad);
	}
}

int CParticleManager::getParticlesCopy(std::vector<SParticle> & particles) {
	if (particles.size() < mParticles.size()) {
		particles.reserve(mParticles.size());

		unsigned int particleToCreate = static_cast<unsigned int>(mParticles.size() - particles.size());

		for (int i = 0; i < particleToCreate; ++i) {
			SParticle emptyParticle;
			particles.push_back(emptyParticle);
		}
	}

	unsigned int indexReturned = 0;

	for (size_t i = 0; i < particles.size(); ++i) {
		if (mParticles[i].life > 0.f) {
			particles[indexReturned] = mParticles[i];
			++indexReturned;
		}
	}

	return indexReturned;
}

void CParticleManager::updateImposterEye(glm::vec3 eye) {
	particleSettings.imposterEyeLocation = eye;
}

glm::vec3 CParticleManager::mCalcImposterRotationFromEye(glm::vec3 particlePosition) {
	return glm::vec3(
		0.f,
		atan2(particlePosition.x - particleSettings.imposterEyeLocation.x,
			particlePosition.z - particleSettings.imposterEyeLocation.z),
		0.f
	);
}