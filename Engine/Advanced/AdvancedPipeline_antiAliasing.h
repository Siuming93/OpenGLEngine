#pragma once
#ifndef __ADVANCE_PIPELINE_ANTI_ALIASING_HEADER__
#define __ADVANCE_PIPELINE_ANTI_ALIASING_HEADER__
#include "../Core/BasePipeline.hpp"

class AdvancedPipeline_antiAliasing : public BasePipeline
{
private:
	GLuint cubeVAO;
	Shader* shader;


public:
	bool Init();
	void Release();
	void Update();

private:
	GLuint GetCubeVAO();
};

#endif // !__ADVANCE_PIPELINE_ANTI_ALIASING_HEADER__
