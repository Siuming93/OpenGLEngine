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
	GLuint quadVAO;
	unsigned int framebuffer;
	GLuint textureColorbuffer;
	Shader* shader;
	Shader* singleColorShader;
	Shader* postShader;

public:
	bool Init();
	void InitFrameBuffer();
	void Release();
	void Update();

	void DrawScene();

private:
	void DrawPlane();
	void DrawTwoContainers(Shader* shader, glm::mat4& model, glm::vec3 scale);
	void UpdateStencilTest(glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);
	unsigned int GetCubeVAO();
	unsigned int GetPlaneVAO();
	unsigned int GetVegetationVAO();
	GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil);
	GLuint GetQuadVAO();

};

#endif // !__ADVANCE_PIPELINE_HEADER__
