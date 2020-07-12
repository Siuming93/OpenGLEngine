#pragma once
#ifndef __LIGHT_PIPELINE_HEADER__
#define __LIGHT_PIPELINE_HEADER__
#include "./../include/BasePipeline.hpp"

class LightPipeline :public BasePipeline
{
	Shader* shader;
	Shader* lightProxyShader;

	unsigned int VAO;

public:
	bool Init();
	void Release();
	void Update();
};

#endif // !__BASE_PIPELINE_HPP__