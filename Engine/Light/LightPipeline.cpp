#include "LightPipeline.h"

unsigned int GetCubeVAO();

bool LightPipeline::Init()
{
	if (!BasePipeline::Init())
		return false;

	string shaderFloder = GetApplicationPath() + "\\Shader\\";
	shader = new Shader((shaderFloder + "Light.Color.vs").c_str(), (shaderFloder + "Light.Color.fs").c_str());
	lightProxyShader = new Shader((shaderFloder + "Light.Color.vs").c_str(), (shaderFloder + "Light.LightProxy.fs").c_str());
	VAO = GetCubeVAO();
}

void LightPipeline::Release()
{
	if (shader != NULL)
		delete shader;

	if (lightProxyShader != NULL)
		delete lightProxyShader;

	BasePipeline::Release();
}

void LightPipeline::Update()
{
	BasePipeline::Update();

	// render
	// ------
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective((*cam).Zoom, (float)800 / (float)600, 0.1f, 10000.0f);
	glm::mat4 view = cam->GetViewMatrix();

	vec3 pos1(0, 0, -5);
	vec3 lightPos(0.3, 0, -3);
	vec3 lightColor(1.0f, 1.0f, 1.0f);

	lightColor.x = sin(glfwGetTime() * 2.0f);
	lightColor.y = sin(glfwGetTime() * 0.7f);
	lightColor.z = sin(glfwGetTime() * 1.3f);

	// create transformations
	shader->use();
	shader->setMat4("projection", glm::value_ptr(projection));
	shader->setMat4("view", glm::value_ptr(view));
	mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, pos1);
	shader->setMat4("model", glm::value_ptr(model));
	shader->setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
	shader->setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
	shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
	shader->setFloat("material.shininess", 32.0f);
	shader->setVec3("light.ambient", 0.2f * lightColor);
	shader->setVec3("light.diffuse", 0.5f * lightColor); // 将光照调暗了一些以搭配场景
	shader->setVec3("light.specular", lightColor);
	shader->setVec3("light.position", lightPos);
	shader->setVec3("viewPos", cam->Position.x, cam->Position.y, cam->Position.z);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);


	lightProxyShader->use();
	lightProxyShader->setMat4("projection", glm::value_ptr(projection));
	lightProxyShader->setMat4("view", glm::value_ptr(view));
	lightProxyShader->setVec3("lightColor", 1, 1.0, 1.0);
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f));
	lightProxyShader->setMat4("model", glm::value_ptr(model));
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glfwSwapBuffers(window);
	glfwPollEvents();
}


unsigned int GetCubeVAO()
{
	float vertices[] = {
		 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	unsigned int VAO, VBO, EBO;
	//创建VBO
	glGenBuffers(1, &VBO);
	//2.创建VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//绑定VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//解绑
	glBindVertexArray(-1);

	//直接画
	return VAO;
}
