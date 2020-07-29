#include "AdvancedPipeline.h"


bool AdvancedPipeline::Init()
{
	if (!BasePipeline::Init())
		return false;



	// load textures
	// -------------
	cubeTexture = LoadTex(GetResourcesPath() + "\\texture\\marble.jpg");
	floorTexture = LoadTex(GetResourcesPath() + "\\texture\\metal.png");
	//grassTexture = LoadTex(GetResourcesPath() + "\\texture\\grass.png");
	grassTexture = LoadTex(GetResourcesPath() + "\\texture\\blending_transparent_window.png");

	string shaderFloder = GetResourcesPath() + "\\Shader\\";
	shader = new Shader(shaderFloder + "Advanced.AlphaTest.vs", shaderFloder + "Advanced.AlphaTest.fs");
	singleColorShader = new Shader(shaderFloder + "Advanced.SingleColor.vs", shaderFloder + "Advanced.SingleColor.fs");

	// configure global opengl state
	// -----------------------------

	cubeVAO = GetCubeVAO();
	planeVAO = GetPlaneVAO();
	vegetationVAO = GetVegetationVAO();

	//glDepthFunc(GL_ALWAYS); // always pass the depth test (same effect as glDisable(GL_DEPTH_TEST))
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
}

unsigned int AdvancedPipeline::GetVegetationVAO()
{
	float transparentVertices[] = {
		// positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
		0.0f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.0f, -0.5f,  0.0f,  0.0f,  0.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  0.0f,

		0.0f,  0.5f,  0.0f,  0.0f,  1.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  0.0f,
		1.0f,  0.5f,  0.0f,  1.0f,  1.0f,
	};  // transparent VAO
	unsigned int transparentVAO, transparentVBO;
	glGenVertexArrays(1, &transparentVAO);
	glGenBuffers(1, &transparentVBO);
	glBindVertexArray(transparentVAO);
	glBindBuffer(GL_ARRAY_BUFFER, transparentVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindVertexArray(0);
	glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	//glCullFace(GL_BACK);

	return transparentVAO;
}


void AdvancedPipeline::Release()
{
	if (shader != NULL)
		delete shader;
}


void AdvancedPipeline::Update()
{
	BasePipeline::Update();

	glEnable(GL_DEPTH_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = cam->GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(cam->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);


	shader->use();
	shader->setInt("texture1", 0);
	shader->setMat4("view", view);
	shader->setMat4("projection", projection);

	//UpdateStencilTest(model, view, projection);

	DrawPlane();

	DrawTwoContainers(shader, model, glm::vec3(1, 1, 1));

	vector<glm::vec3> vegetation;
	vegetation.push_back(glm::vec3(-1.5f, 0.0f, -0.48f));
	vegetation.push_back(glm::vec3(1.5f, 0.0f, 0.51f));
	vegetation.push_back(glm::vec3(0.0f, 0.0f, 0.7f));
	vegetation.push_back(glm::vec3(-0.3f, 0.0f, -2.3f));
	vegetation.push_back(glm::vec3(0.5f, 0.0f, -0.6f));

	glBindVertexArray(vegetationVAO);
	glBindTexture(GL_TEXTURE_2D, grassTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::map<float, glm::vec3> sorted;
	for (unsigned int i = 0; i < vegetation.size(); i++)
	{
		float distance = glm::length(cam->Position - vegetation[i]);
		sorted[distance] = vegetation[i];
	}
	vector<glm::vec3> vegetation1;
	for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
	{
		vegetation1.push_back(it->second);

	/*	model = glm::mat4();
		std::cout <<it->first<<"     " << it->second.x << " "<< it->second.y <<" "<< it->second.z << endl;;
		//!!!!!!!!!!
		//model 没有初始化
		model = glm::translate(model, it->second);
		shader->setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 6);*/

		model = glm::mat4(1.0f);
		model = glm::translate(model, it->second);
		shader->setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	/*for (unsigned int i = 0; i < vegetation1.size(); i++)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, vegetation1[i]);
		shader->setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}*/

	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------
	glfwSwapBuffers(window);
	glfwPollEvents();

}

void AdvancedPipeline::UpdateStencilTest(glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
{
	glStencilMask(0x00); // 记得保证我们在绘制地板的时候不会更新模板缓冲
	shader->use();
	DrawPlane();


	glStencilFunc(GL_ALWAYS, 0xFF, 0xFF); // 所有的片段都应该更新模板缓冲
	glStencilMask(0xF0); // 启用模板缓冲写入
	DrawTwoContainers(shader, model, glm::vec3(1, 1, 1));

	glStencilFunc(GL_NOTEQUAL, 0xF0, 0xFF);
	glStencilMask(0x00);
	glDisable(GL_DEPTH_TEST);
	singleColorShader->use();
	singleColorShader->setMat4("view", view);
	singleColorShader->setMat4("projection", projection);
	DrawTwoContainers(singleColorShader, model, glm::vec3(1.2, 1.2, 1.2));
	glStencilMask(0xFF);
	glEnable(GL_DEPTH_TEST);
}

void AdvancedPipeline::DrawPlane()
{
	// floor
	glBindVertexArray(planeVAO);
	glBindTexture(GL_TEXTURE_2D, floorTexture);
	shader->setMat4("model", glm::mat4(1.0f));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void AdvancedPipeline::DrawTwoContainers(Shader* shader, glm::mat4& model, glm::vec3 scale)
{
	// cubes
	glBindVertexArray(cubeVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cubeTexture);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
	model = glm::scale(model, scale);
	shader->setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	model = glm::scale(model, scale);
	shader->setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

unsigned int AdvancedPipeline::GetCubeVAO()
{
	float cubeVertices[] = {
		// positions          // texture Coords
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

	// cube VAO
	unsigned int cubeVAO, cubeVBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindVertexArray(0);

	return cubeVAO;
}

unsigned AdvancedPipeline::GetPlaneVAO()
{
	float planeVertices[] = {
		// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
		 5.0f, -0.5f, -5.0f,  2.0f, 2.0f
	};


	unsigned VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindVertexArray(0);
	return VAO;
}