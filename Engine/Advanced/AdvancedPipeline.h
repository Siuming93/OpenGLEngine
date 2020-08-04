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
	GLuint cubeMapTexture;
	unsigned int cubeVAO, planeVAO;
	unsigned int vegetationVAO;
	GLuint quadVAO;
	GLuint skyboxVAO;
	unsigned int framebuffer;
	GLuint textureColorbuffer;
	Shader* shader;
	Shader* singleColorShader;
	Shader* postShader;
	Shader* skyboxShader;

public:
	bool Init();
	void InitFrameBuffer();
	void Release();
	void Update();

private:
	void DrawSkybox();
	void DrawScene();
	void DrawPlane();
	void DrawTwoContainers(Shader* shader, glm::mat4& model, glm::vec3 scale);
	void UpdateStencilTest(glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);
	unsigned int GetCubeVAO();
	unsigned int GetPlaneVAO();
	unsigned int GetVegetationVAO();
	unsigned int GetSkyboxVAO();
	GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil);
	GLuint GetQuadVAO();
	bool LoadCubeMap();

};

#endif // !__ADVANCE_PIPELINE_HEADER__
