#pragma once
#include "ModelCamera.h"
class DebugCam : public ModelCamera
{
public:
	void Frame();
	void UpdateVector();
public:
	DebugCam();
	~DebugCam();
};

