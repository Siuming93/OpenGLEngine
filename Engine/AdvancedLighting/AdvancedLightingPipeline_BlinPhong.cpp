#include "AdvancedLightingPipeline_BlinPhong.h"

bool AdvancedLightingPipeline_BlinPhong::Init()
{
	if (!BasePipeline::Init())
	{
		return false;
	}

	planeVAO = GetPlaneVAO();

	string shaderFloder = GetResourcesPath() + "\\Shader\\";
	shader = new Shader(shaderFloder + "AdvancedLighting.BlinnPhong.vs", shaderFloder + "AdvancedLighting.BlinnPhong.fs");
	textureID = LoadTex(GetResourcesPath() + "\\texture\\wood.png");
}


void AdvancedLightingPipeline_BlinPhong::Release()
{
	if (shader != NULL)
		delete shader;
}

void AdvancedLightingPipeline_BlinPhong::Update()
{
	BasePipeline::Update();

	glClearColor(0.3f, 0.3f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // We're not using stencil buffer now
	glEnable(GL_DEPTH_TEST);

	shader->use();

	glBindVertexArray(planeVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	vec3 lightPos(0.3, 0, -3);
	vec3 lightColor(1.0f, 1.0f, 1.0f);

	shader->setInt("material.diffuse", 0);
	shader->setInt("material.specular", 0);
	shader->setFloat("material.shininess", 32.0f);

	shader->setVec3("light.diffuse", lightColor); // 将光照调暗了一些以搭配场景
	shader->setVec3("light.specular", lightColor);
	shader->setVec3("light.position", lightPos);
	shader->setFloat("light.constant", 1.0f);
	shader->setFloat("light.linear", 0.09f);
	shader->setFloat("light.quadratic", 0.032f);

	glm::mat4 view = cam->GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(cam->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	shader->setMat4("view", view);
	shader->setMat4("projection", projection);
	
	mat4 model = glm::mat4(1.0f);
	auto pos = glm::vec3(0, 0, 0);
	model = glm::translate(model, pos);
	shader->use();
	shader->setMat4("model", model);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------
	glfwSwapBuffers(window);
	glfwPollEvents();
}

GLuint AdvancedLightingPipeline_BlinPhong::GetPlaneVAO()
{
	GLuint VAO, VBO;
	float planeVertices[] = {
		// positions            // normals         // texcoords
		10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
		-10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
		-10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,

		10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
		-10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
		10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glBindVertexArray(0);

	return VAO;
}