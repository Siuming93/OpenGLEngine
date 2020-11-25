#ifndef __MATERIAL_HEADER__
#define __MATERIAL_HEADER__

#include "shader.h"
#include <vector>
#include <list>
#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;

enum PropertyType
{
	Bool,
	Int,
	Float,
	Mat4,
	Vec2,
	Vec3,
	Vec4,
	Texutre,
};
struct MaterialProperty
{
	const char* propertyName;
	PropertyType type;

	const char* texPath;
	bool valueBool;
	int valueInt;
	float valueFloat;
	const float* valueMat4;
	vec2 valueVec2;
	vec3 valueVec3;
	vec4 valueVec4;
};


class  Material
{
public:
	Shader* shader;
	vector<MaterialProperty> properties;


public:
	void Init();
	void Release();
	void Use();

public:
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
};

#endif // !__MATERIAL_HEADER__
