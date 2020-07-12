#pragma once
#include "Camera.h"

class ModelCamera : public Camera
{
public:
	void Frame();
	void UpdateVector();
	void Update();
public:
	ModelCamera();
	~ModelCamera();
};

