#pragma once
#ifndef __GETTING_START_HEADER
#define __GETTING_START_HEADER

#include "../Core/BasePipeline.hpp"

class GettingStartPipeline :public BasePipeline
{
private:
	Shader* ourShader;
	unsigned int texture0 = 0, texture1;
	glm::vec3* cubePositionsArr;
	unsigned int VAO;

public:
	bool Init();
	void Release();
	void Update();

private:
	unsigned int GetCubeVAO();

};

#endif // !__GETTING_START_HEADER
