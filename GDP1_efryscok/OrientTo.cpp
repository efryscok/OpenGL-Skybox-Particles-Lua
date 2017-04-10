#include "global.h"

void COrientTo::initialize(glm::vec3 destination, bool timeBased, float value) {
	mDestination = destination;
	mTimeBased = timeBased;
	mValue = value;
}

bool COrientTo::execute() {
	if (mTimeBased) {
		float speed = glm::cross(
			mDestination - gSpaceShip->position,
			gSpaceShip->orientation * glm::vec3(0.f, 0.f, 1.f)
		).y / mValue;
		gSpaceShip->orientation *= glm::quat(glm::vec3(0.f, glm::radians(speed), 0.f));
		gQuad->orientation = gSpaceShip->orientation;
	}
	else {
		gSpaceShip->orientation *= glm::quat(glm::vec3(0.f, glm::radians(mValue), 0.f));
		gQuad->orientation = gSpaceShip->orientation;
	}
	return true;
}

bool COrientTo::isDone() {
	glm::vec3 crossProd = glm::cross(
		mDestination - gSpaceShip->position,
		gSpaceShip->orientation * glm::vec3(0.f, 0.f, 1.f)
	);

	if (crossProd.y < 0) {
		return true;
	}

	return false;
}