#pragma once
#ifndef __ADVANCE_PIPELINE_HEADER__
#define __ADVANCE_PIPELINE_HEADER__
#include "../include/BasePipeline.hpp"

class AdvancedPipeline : public BasePipeline
{
private:
	unsigned int cubeTexture;
	unsigned int floorTexture;
	unsigned int cubeVAO, planeVAO;
	Shader* shader;

public:
	bool Init();
	void Release();
	void Update();
};

#endif // !__ADVANCE_PIPELINE_HEADER__
