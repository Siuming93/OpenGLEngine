#pragma once
#ifndef __LIGHT_PIPELINE_HEADER__
#define __LIGHT_PIPELINE_HEADER__
#include "./../include/BasePipeline.hpp"
#include <vector>
#include <list>

class LightPipeline :public BasePipeline
{
	list<vec3> cubePositions;
	Shader* shader;
	Shader* lightProxyShader;

	unsigned int diffuseMap;
	unsigned int specularMap;

	unsigned int VAO;

public:
	bool Init();
	void Release();
	void Update();
};

#endif // !__BASE_PIPELINE_HPP__