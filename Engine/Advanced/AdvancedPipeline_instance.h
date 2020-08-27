#pragma once
#ifndef __ADVANCE_PIPELINE_INSTANCE_HEADER__
#define __ADVANCE_PIPELINE_INSTANCE_HEADER__
#include "../include/BasePipeline.hpp"

class AdvancedPipeline_instance : public BasePipeline
{
private:
	GLuint quadVAO;
	Shader* shader;
	glm::vec2 translations[100];
public:
	bool Init();
	void Release();
	void Update();

private:
	GLuint GetQuadVAO();
};

#endif // !__ADVANCE_PIPELINE_INSTANCE_HEADER__
