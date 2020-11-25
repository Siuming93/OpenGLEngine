#pragma once
#ifndef __ADVANCE_PIPELINE_INSTANCE_HEADER__
#define __ADVANCE_PIPELINE_INSTANCE_HEADER__
#include "../Core/BasePipeline.hpp"

class AdvancedPipeline_instance : public BasePipeline
{
private:
	GLuint quadVAO;
	Shader* shader;
	glm::vec2 translations[100];

	Shader* planetShader;
	glm::mat4* modelMatrices;
	unsigned int amount = 100000;
	
	Shader* rockShader;

	Model* planet;
	Model* rock;
	Model* model;

	GLuint rockVAO;

public:
	bool Init();
	void Release();
	void Update();

private:
	void DrawPlanet();
	void DrawRock();
};

#endif // !__ADVANCE_PIPELINE_INSTANCE_HEADER__
