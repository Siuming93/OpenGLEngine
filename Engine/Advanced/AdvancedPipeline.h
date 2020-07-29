#pragma once
#ifndef __ADVANCE_PIPELINE_HEADER__
#define __ADVANCE_PIPELINE_HEADER__
#include "../include/BasePipeline.hpp"

class AdvancedPipeline : public BasePipeline
{
private:
	unsigned int cubeTexture;
	unsigned int floorTexture;
	unsigned int grassTexture;
	unsigned int cubeVAO, planeVAO;
	unsigned int vegetationVAO;
	Shader* shader;
	Shader* singleColorShader;

public:
	bool Init();
	void Release();
	void Update();

private:
	void DrawPlane();
	void DrawTwoContainers(Shader* shader, glm::mat4& model, glm::vec3 scale);
	void UpdateStencilTest(glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);
	unsigned int GetCubeVAO();
	unsigned int GetPlaneVAO();
	unsigned int GetVegetationVAO();

};

#endif // !__ADVANCE_PIPELINE_HEADER__
