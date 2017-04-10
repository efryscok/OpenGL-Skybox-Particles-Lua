#include "global.h"

void CMoveTo::initialize(glm::vec3 destination, bool timeBased, float value) {
	mDestination = destination;
	mTimeBased = timeBased;
	mValue = value;
}

bool CMoveTo::execute() {
	if (mTimeBased) {
		float speed = glm::distance(mDestination, gSpaceShip->position) / mValue;
		gSpaceShip->position += (glm::normalize(mDestination - gSpaceShip->position) * ((speed < 1.1f) ? 1.1f : speed)) * gDeltaTime;
	}
	else {
		gSpaceShip->position += (glm::normalize(mDestination - gSpaceShip->position) * mValue) * gDeltaTime;
	}
	return true;
}

bool CMoveTo::isDone() {
	if (glm::distance(gSpaceShip->position, mDestination) < 0.1f) {
		return true;
	}

	return false;
}