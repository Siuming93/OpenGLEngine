#pragma once
#ifndef __ADVANCED_LIGHTING_PIPELINE_TONE_MAPPING_HEADER__
#define __ADVANCED_LIGHTING_PIPELINE_TONE_MAPPING_HEADER__
#include "../Core/BasePipeline.hpp"

class AdvancedLightingPipeline_ToneMapping : public BasePipeline
{
private:
	Shader* shader;
	GLuint planeVAO;
	GLuint textureID;
public:
	bool Init();
	void Release();
	void Update();

private:
	GLuint GetPlaneVAO();
};


#endif // !__ADVANCED_LIGHTING_PIPELINE_TONE_MAPPING_HEADER__
