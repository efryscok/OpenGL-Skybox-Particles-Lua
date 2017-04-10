#pragma once

#include <glm\vec3.hpp>

#include "Command.h"

class COrientTo : public CCommand {
public:
	virtual void initialize(glm::vec3 destination, bool timeBased, float value);
	virtual bool execute();
	virtual bool isDone();

private:
	bool mTimeBased;
	float mValue;
	glm::vec3 mDestination;
};