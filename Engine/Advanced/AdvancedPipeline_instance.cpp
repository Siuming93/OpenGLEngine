#include "AdvancedPipeline_instance.h"


bool AdvancedPipeline_instance::Init()
{
	if (!BasePipeline::Init())
		return false;

	string shaderFloder = GetResourcesPath() + "\\Shader\\";
	shader = new Shader(shaderFloder + "Advanced.Instance.vs", shaderFloder + "Advanced.Instance.fs");

	quadVAO = GetQuadVAO();

	int index = 0;
	float offset = 0.1f;
	for (int y = -10; y < 10; y += 2)
	{
		for (int x = -10; x < 10; x += 2)
		{
			glm::vec2 translation;
			translation.x = (float)x / 10.0f + offset;
			translation.y = (float)y / 10.0f + offset;
			translations[index++] = translation;
		}
	}

	glEnable(GL_DEPTH_TEST);
}

void AdvancedPipeline_instance::Release()
{
	if (shader != NULL)
		delete shader;
}

void AdvancedPipeline_instance::Update()
{
	BasePipeline::Update();

	glClearColor(0.3f, 0.3f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // We're not using stencil buffer now

	shader->use();

	for (unsigned int i = 0; i < 100; i++)
	{
		stringstream ss;
		string index;
		ss << i;
		index = ss.str();
		shader->setVec2(("offsets[" + index + "]").c_str(), translations[i]);
	}

	glBindVertexArray(quadVAO);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);
	glBindVertexArray(0);


	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------
	glfwSwapBuffers(window);
	glfwPollEvents();

}

GLuint AdvancedPipeline_instance::GetQuadVAO()
{
	float quadVertices[] = {
		// Î»ÖÃ          // ÑÕÉ«
		-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
		 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
		-0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

		-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
		 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
		 0.05f,  0.05f,  0.0f, 1.0f, 1.0f
	};
	GLuint quadVAO, quadVBO;
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glBindVertexArray(0);

	return quadVAO;
}