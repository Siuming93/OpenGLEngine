#include "LightPipeline.h"

unsigned int GetCubeVAO();

bool LightPipeline::Init()
{
	if (!BasePipeline::Init())
		return false;

	string shaderFloder = GetApplicationPath() + "\\Shader\\";
	shader = new Shader((shaderFloder + "Light.Color.vs").c_str(), (shaderFloder + "Light.Color.fs").c_str());

	VAO = GetCubeVAO();
}

void LightPipeline::Release()
{
	if (shader != NULL)
		delete shader;

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

	shader->use();

	// create transformations
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective((*cam).Zoom, (float)800 / (float)600, 0.1f, 10000.0f);
	shader->setMat4("projection", glm::value_ptr(projection));
	glm::mat4 view = cam->GetViewMatrix();
	shader->setMat4("view", glm::value_ptr(view));

	shader->SetVec3("lightColor", 1.0, 1.0, 1.0);

	vec3 pos1(0, 0, -5);
	vec3 pos2(1.5, 1.5, -7);

	mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, pos1);
	shader->setMat4("model", glm::value_ptr(model));
	shader->SetVec3("objectColor", 1.0f, 0.5f, 0.31f);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model = glm::mat4(1.0f);
	model = glm::translate(model, pos2);
	shader->setMat4("model", glm::value_ptr(model));
	shader->SetVec3("objectColor", 1.0f, 1.0f, 1.0f);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glfwSwapBuffers(window);
	glfwPollEvents();
}


unsigned int GetCubeVAO()
{
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//解绑
	glBindVertexArray(-1);

	//直接画
	return VAO;
}
