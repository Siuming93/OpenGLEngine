#pragma once
#ifndef  SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm\gtc\type_ptr.hpp>

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

class  Shader
{
public:
	//程序ID
	unsigned int ID;

	//构造器读取并构建着色器
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	//使用,激活
	void use();
	//uniform工具
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec2(const std::string name, float v1, float v2) const;
	void setVec2(const std::string name, glm::vec2 value) const;
	void setVec3(const std::string name, float v1, float v2, float v3) const;
	void setVec3(const std::string name, glm::vec3 value) const;
	void setMat4(const std::string& name, const float* value) const;
	void setMat4(const std::string& name, glm::mat4 value) const;
	void bindUniformBuffer(const std::string& name, GLuint bufferIndex) const;
private:
	void Init(const GLchar* vertexPath, const GLchar* fragmentPath);
};
#endif // ! SHADER_H
