#pragma once
#ifndef __ADVANCE_PIPELINE_HEADER__
#define __ADVANCE_PIPELINE_HEADER__
#include "../Core/BasePipeline.hpp"

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
	GLuint uboMatrices;
	unsigned int framebuffer;
	GLuint textureColorbuffer;
	Shader* shader;
	Shader* singleColorShader;
	Shader* postShader;
	Shader* skyboxShader;
	Shader* reflectShader;

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
	void DrawCube(glm::vec3& pos, glm::vec3& scale, Shader* shader);
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
