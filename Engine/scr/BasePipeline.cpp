#include "../include/BasePipeline.hpp"

static BasePipeline* m_curInstance;

int BasePipeline::InitWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_btn_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return true;
}

bool BasePipeline::Init()
{
	cam = new Camera;
	m_curInstance = this;
	return InitWindow();
}

void BasePipeline::Release()
{
	if (cam != NULL)
		delete cam;
}

void BasePipeline::Update()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	ProcessInput();
}

void BasePipeline::Loop()
{
	while (!glfwWindowShouldClose(window))
	{
		Update();
	}

	glfwTerminate();
}

void BasePipeline::ProcessInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float cameraSpeed = 2.5 * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		(*cam).ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		(*cam).ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		(*cam).ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		(*cam).ProcessKeyboard(RIGHT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_F8) == GLFW_PRESS)
	{
		if (cam != NULL)
			delete cam;
		cam = new Camera;
	}
}

BasePipeline::BasePipeline()
{
}

BasePipeline::~BasePipeline()
{
	Release();
}


#pragma region Static 

string BasePipeline::GetResourcesPath()
{
	char* buffer;
	//也可以将buffer作为输出参数
	if ((buffer = _getcwd(NULL, 0)) == NULL)
	{
		perror("getcwd error");
	}
	return string(buffer) + "/../Resources";
}
unsigned int BasePipeline::LoadTex(string path)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// 加载并生成纹理
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	bool hasAlpha = nrChannels == 4;
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, hasAlpha ? GL_RGBA : GL_RGB, width, height, 0, hasAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	return texture;
}

inline void BasePipeline::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (!m_curInstance->mousePress)
	{
		return;
	}
	if (m_curInstance->firstMouse)
	{
		m_curInstance->lastX = xpos;
		m_curInstance->lastY = ypos;
		m_curInstance->firstMouse = false;
	}

	float xoffset = xpos - m_curInstance->lastX;
	float yoffset = m_curInstance->lastY - ypos; // reversed since y-coordinates go from bottom to top
	m_curInstance->lastX = xpos;
	m_curInstance->lastY = ypos;

	float sensitivity = 2.0f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	m_curInstance->yaw += xoffset;
	m_curInstance->pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (m_curInstance->pitch > 89.0f)
		m_curInstance->pitch = 89.0f;
	if (m_curInstance->pitch < -89.0f)
		m_curInstance->pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(m_curInstance->yaw)) * cos(glm::radians(m_curInstance->pitch));
	front.y = sin(glm::radians(m_curInstance->pitch));
	front.z = sin(glm::radians(m_curInstance->yaw)) * cos(glm::radians(m_curInstance->pitch));
	(*m_curInstance->cam).ProcessMouseMovement(xoffset, yoffset);
}

inline void BasePipeline::mouse_btn_callback(GLFWwindow* window, int index, int state, int mod)
{
	if (index == GLFW_MOUSE_BUTTON_2 && state == GLFW_PRESS && !m_curInstance->mousePress)
	{
		m_curInstance->firstMouse = true;
		m_curInstance->mousePress = true;
	}

	if (index == GLFW_MOUSE_BUTTON_2 && state == GLFW_RELEASE && m_curInstance->mousePress)
	{
		m_curInstance->mousePress = false;
	}
}

inline void BasePipeline::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	(*m_curInstance->cam).ProcessMouseScroll(yoffset);
}

inline void BasePipeline::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
#pragma endregion
