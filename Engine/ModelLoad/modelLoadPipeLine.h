#pragma once
#ifndef __MODEL_LOAD_PIPELINE_HEADER_
#define __MODEL_LOAD_PIPELINE_HEADER_
#include "../Core/basePipeline.hpp"

class ModelLoadPipeline : public BasePipeline
{
private:
	Model* model;
	Shader* shader;
public:
	bool Init();
	void Release();
	void Update();
};


#endif // !__MODEL_LOAD_PIPELINE_HEADER_
