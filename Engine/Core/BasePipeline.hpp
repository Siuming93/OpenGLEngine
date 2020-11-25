#pragma once
#ifndef __BASE_PIPELINE_HPP__
#define __BASE_PIPELINE_HPP__
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include <direct.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "shader.h"
#include "camera.h"
#include "stb_image.h"
#include "model.h"

using namespace std;
using namespace glm;

class BasePipeline
{
protected:
	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;
	// settings
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;
	GLFWwindow* window;


public:
	Camera* cam;

public:
	virtual int InitWindow();
	virtual void ProcessInput();

public:
	BasePipeline();
	~BasePipeline();

	virtual bool Init();
	virtual void Update();
	virtual void Release();

public:
	void Loop();

protected:

	bool firstMouse = true;
	bool mousePress = false;
	float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float pitch = 0.0f;
	float lastX = 800.0f / 2.0;
	float lastY = 600.0 / 2.0;

	string GetResourcesPath();
	unsigned int LoadTex(string path);

	// glfw: whenever the mouse moves, this callback is called
	// -------------------------------------------------------
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	static void mouse_btn_callback(GLFWwindow* window, int index, int state, int mod);

	// glfw: whenever the mouse scroll wheel scrolls, this callback is called
	// ----------------------------------------------------------------------
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};




#pragma region Static Tool

#pragma endregion


#endif // !__BASE_PIPELINE_HPP__
