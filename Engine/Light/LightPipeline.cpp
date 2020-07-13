#include "LightPipeline.h"

unsigned int GetCubeVAO();

bool LightPipeline::Init()
{
	if (!BasePipeline::Init())
		return false;

	string shaderFloder = GetApplicationPath() + "\\Shader\\";
	shader = new Shader((shaderFloder + "Light.Color.vs").c_str(), (shaderFloder + "Light.MultipleLights.fs").c_str());
	lightProxyShader = new Shader((shaderFloder + "Light.Color.vs").c_str(), (shaderFloder + "Light.LightProxy.fs").c_str());
	VAO = GetCubeVAO();
	string textFolder = GetApplicationPath() + "\\Texture\\";
	diffuseMap = LoadTex(textFolder + "container2.png");
	specularMap = LoadTex(textFolder + "container2_specular.png");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularMap);

	cubePositions = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f)
	};
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
	vec3 lightDirection(-1.0, -1.0, -1.0);
	vec3 lightColor(1.0f, 1.0f, 1.0f);

	glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
	};

	/*lightColor.x = sin(glfwGetTime() * 2.0f);
	lightColor.y = sin(glfwGetTime() * 0.7f);
	lightColor.z = sin(glfwGetTime() * 1.3f);*/

	// create transformations
	shader->use();
	shader->setMat4("projection", glm::value_ptr(projection));
	shader->setMat4("view", glm::value_ptr(view));
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

	int i = 0;
	for (vec3 pos : cubePositions)
	{
		mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, pos + pos1);
		float angle = 20.0f * i++;
		//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f) + glm::radians(angle + 0), glm::vec3(0.5f, 1.0f, 0.0f));
		model = glm::rotate(model,  glm::radians(50.0f) + glm::radians(angle + 0), glm::vec3(0.5f, 1.0f, 0.0f));
		shader->setMat4("model", glm::value_ptr(model));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	for (vec3 pos: pointLightPositions)
	{
		lightProxyShader->use();
		lightProxyShader->setMat4("projection", glm::value_ptr(projection));
		lightProxyShader->setMat4("view", glm::value_ptr(view));
		lightProxyShader->setVec3("lightColor", 1, 1.0, 1.0);
		mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, pos);
		model = glm::scale(model, glm::vec3(0.2f));
		lightProxyShader->setMat4("model", glm::value_ptr(model));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	

	glfwSwapBuffers(window);
	glfwPollEvents();
}


unsigned int GetCubeVAO()
{
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//解绑
	glBindVertexArray(-1);

	//直接画
	return VAO;
}
