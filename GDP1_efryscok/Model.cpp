#include "global.h"

int CModel::mNextID = 1;

CModel::CModel() {
	isWireframe = false;
	useDebugColours = false;
	isVisible = true;
	isImposter = false;
	isUpdatedByPhysics = false;
	isCubeMap = false;

	scale = 1.f;
	alpha = 1.f;
	movementSpeed = 1.f;

	mesh = "N/A";
	texture = "N/A";

	mUniqueID = ++mNextID;
}
