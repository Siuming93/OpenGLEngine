#include "AdvancedPipeline_instance.h"
bool AdvancedPipeline_instance::Init()
{
	if (!BasePipeline::Init())
		return false;

	string shaderFloder = GetResourcesPath() + "\\Shader\\";
	shader = new Shader((shaderFloder + "Advanced.Instance_planet.vs").c_str(), (shaderFloder + "Advanced.Instance_planet.fs").c_str());
	rockShader = new Shader(shaderFloder + "Advanced.Instance_rock.vs", shaderFloder + "Advanced.Instance_planet.fs");
	string modelFolder = GetResourcesPath() + "\\Model\\";
	rock = new Model(modelFolder + "rock/rock.obj");
	planet = new Model(modelFolder + "planet/planet.obj");

	model = planet;

	modelMatrices = new glm::mat4[amount];
	srand(glfwGetTime()); // 初始化随机种子    
	float radius = 150.0;
	float offset = 25;
	for (unsigned int i = 0; i < amount; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		// 1. 位移：分布在半径为 'radius' 的圆形上，偏移的范围是 [-offset, offset]
		float angle = (float)i / (float)amount * 360.0f;
		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float x = sin(angle) * radius + displacement;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float y = displacement * 0.4f; // 让行星带的高度比x和z的宽度要小
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float z = cos(angle) * radius + displacement;
		model = glm::translate(model, glm::vec3(x, y, z));

		// 2. 缩放：在 0.05 和 0.25f 之间缩放
		float scale = (rand() % 20) / 100.0f + 0.05;
		model = glm::scale(model, glm::vec3(scale));

		// 3. 旋转：绕着一个（半）随机选择的旋转轴向量进行随机的旋转
		float rotAngle = (rand() % 360);
		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

		// 4. 添加到矩阵的数组中
		modelMatrices[i] = model;
	}

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);


	for (int i = 0; i < rock->meshes.size(); i++)
	{
		auto rockVAO = rock->meshes[i].VAO;


		glBindVertexArray(rockVAO);
		GLsizei vec4Size = sizeof(glm::vec4);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(vec4Size));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);

		glBindVertexArray(0);
	}

	cam->MovementSpeed *= 10;
}

void AdvancedPipeline_instance::Release()
{
	if (shader != NULL)
		delete shader;

	if (model != NULL)
		delete model;
}

void AdvancedPipeline_instance::Update()
{
	BasePipeline::Update();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(cam->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000000.0f);
	glm::mat4 view = cam->GetViewMatrix();

	rockShader->use();
	rockShader->setMat4("projection", value_ptr(projection));
	rockShader->setMat4("view", value_ptr(view));
	shader->use();
	shader->setMat4("projection", value_ptr(projection));
	shader->setMat4("view", value_ptr(view));


	// render the loaded model
	auto model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(10, 10, 10));	// it's a bit too big for our scene, so scale it down
	model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0, 1.0f, 0.0f));

	shader->setMat4("model", value_ptr(model));
	this->planet->Draw(*shader);

	DrawRock();

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void AdvancedPipeline_instance::DrawRock()
{
	rockShader->use();
	this->rock->DrawInstance(*rockShader, amount);

	/*for (int i = 0; i < amount; i++)
	{
		auto model = modelMatrices[i];
		shader->setMat4("model", value_ptr(model));
		this->rock->Draw(*shader);
	}*/
}