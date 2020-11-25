#include "../Core/shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	Init(vertexPath, fragmentPath);
}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	Init(vertexPath.c_str(), fragmentPath.c_str());
}

void Shader::Init(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	//1.从文件路径中获取顶点/片段着色器
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	//保证ifstream对象可以抛出异常.
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		//打开文件
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		//读取文件内容到数据流中
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		//关闭文件处理
		vShaderFile.close();
		fShaderFile.close();
		//转换数据流到string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (const std::exception&)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	//2.编译着色器
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	//顶点着色器
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	//打印编译错误
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << vertexPath << std::endl << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//片段着色器
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	//打印编译错误
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << fragmentPath << std::endl;
		std::cout<< "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//着色器程序
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	//打印连接错误 
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setMat4(const std::string& name, const float* value) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, value);
}

void Shader::setMat4(const std::string& name, glm::mat4 value) const
{
	setMat4(name, glm::value_ptr(value));
}

void Shader::setVec2(const std::string name, float v1, float v2) const
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), v1, v2);
}

void Shader::setVec2(const std::string name, glm::vec2 value) const
{
	setVec2(name, value.x, value.y);
}

void Shader::setVec3(const std::string name, float v1, float v2, float v3) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), v1, v2, v3);
}

void Shader::setVec3(const std::string name, glm::vec3 value) const
{
	setVec3(name, value.x, value.y, value.z);
}

void Shader::bindUniformBuffer(const std::string& name, GLuint bufferIndex) const
{
	glUniformBlockBinding(ID, glGetUniformBlockIndex(ID, name.c_str()), bufferIndex);
}
