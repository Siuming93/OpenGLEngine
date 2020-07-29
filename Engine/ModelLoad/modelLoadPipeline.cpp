#include "modelLoadPipeline.h"
Shader* cubeShader;
bool ModelLoadPipeline::Init()
{
	if (!BasePipeline::Init())
		return false;

	string shaderFloder = GetResourcesPath() + "\\Shader\\";
	shader = new Shader((shaderFloder + "Model.vs").c_str(), (shaderFloder + "Model.fs").c_str());
	cubeShader = new Shader((shaderFloder + "shader.vs").c_str(), (shaderFloder + "shader.fs").c_str());

	string modelFolder = GetResourcesPath() + "\\Model\\";
	model = new Model(modelFolder + "nanosuit/nanosuit.obj");
}

void ModelLoadPipeline::Release()
{
	if (shader != NULL)
		delete shader;

	if (model != NULL)
		delete model;
}

static unsigned int GetCubeVAO()
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

void ModelLoadPipeline::Update()
{
	BasePipeline::Update();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(cam->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = cam->GetViewMatrix();




	cubeShader->use();
	cubeShader->setMat4("projection", value_ptr(projection));
	cubeShader->setMat4("view", value_ptr(view));
	auto pos = vec3(3,0,0);
	glm::mat4 model = glm::mat4(1);
	model = glm::translate(model, pos);
	model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	cubeShader->setMat4("model", glm::value_ptr(model));
	glBindVertexArray(GetCubeVAO());
	glDrawArrays(GL_TRIANGLES, 0, 36);


	vec3 pos1(0, 0, -5);
	vec3 lightPos(0.3, 0, -3);
	vec3 lightDirection(-1.0, -1.0, -1.0);
	vec3 lightColor(1.0f, 1.0f, 1.0f);

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	shader->use();
	shader->setMat4("projection", value_ptr(projection));
	shader->setMat4("view", value_ptr(view));

	shader->setInt("material.diffuse", 0);
	shader->setInt("material.specular", 1);
	shader->setFloat("material.shininess", 32.0f);
	shader->setVec3("ambient", 0.2f * lightColor);
	shader->setVec3("dirLight.diffuse", 0.5f * lightColor); // 将光照调暗了一些以搭配场景
	shader->setVec3("dirLight.specular", lightColor);
	shader->setVec3("dirLight.direction", lightDirection);
	shader->setVec3("flashLight.diffuse", 0.5f * lightColor); // 将光照调暗了一些以搭配场景
	shader->setVec3("flashLight.specular", lightColor);
	shader->setVec3("flashLight.position", cam->Position);
	shader->setVec3("flashLight.direction", cam->Front);
	shader->setFloat("flashLight.cutOff", glm::cos(glm::radians(12.5f)));
	shader->setFloat("flashLight.outerCutOff", glm::cos(glm::radians(17.5f)));
	shader->setFloat("flashLight.constant", 1.0f);
	shader->setFloat("flashLight.linear", 0.09f);
	shader->setFloat("flashLight.quadratic", 0.032f);
	shader->setVec3("pointLights[0].diffuse", 0.5f * lightColor); // 将光照调暗了一些以搭配场景
	shader->setVec3("pointLights[0].specular", lightColor);
	shader->setVec3("pointLights[0].position", pointLightPositions[0]);
	shader->setFloat("pointLights[0].constant", 1.0f);
	shader->setFloat("pointLights[0].linear", 0.09f);
	shader->setFloat("pointLights[0].quadratic", 0.032f);
	shader->setVec3("pointLights[1].diffuse", 0.5f * lightColor); // 将光照调暗了一些以搭配场景
	shader->setVec3("pointLights[1].specular", lightColor);
	shader->setVec3("pointLights[1].position", pointLightPositions[1]);
	shader->setFloat("pointLights[1].constant", 1.0f);
	shader->setFloat("pointLights[1].linear", 0.09f);
	shader->setFloat("pointLights[1].quadratic", 0.032f);
	shader->setVec3("pointLights[2].diffuse", 0.5f * lightColor); // 将光照调暗了一些以搭配场景
	shader->setVec3("pointLights[2].specular", lightColor);
	shader->setVec3("pointLights[2].position", pointLightPositions[2]);
	shader->setFloat("pointLights[2].constant", 1.0f);
	shader->setFloat("pointLights[2].linear", 0.09f);
	shader->setFloat("pointLights[2].quadratic", 0.032f);
	shader->setVec3("pointLights[3].diffuse", 0.5f * lightColor); // 将光照调暗了一些以搭配场景
	shader->setVec3("pointLights[3].specular", lightColor);
	shader->setVec3("pointLights[3].position", pointLightPositions[3]);
	shader->setFloat("pointLights[3].constant", 1.0f);
	shader->setFloat("pointLights[3].linear", 0.09f);
	shader->setFloat("pointLights[3].quadratic", 0.032f);


	shader->setVec3("viewPos", cam->Position.x, cam->Position.y, cam->Position.z);

	// render the loaded model
	 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -1.5f, -2.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	// it's a bit too big for our scene, so scale it down
	model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0, 1.0f, 0.0f));

	shader->setMat4("model", value_ptr(model));
	this->model->Draw(*shader);

	glfwSwapBuffers(window);
	glfwPollEvents();
}