#include "modelLoadPipeline.h"

bool ModelLoadPipeline::Init()
{
	if (!BasePipeline::Init())
		return false;

	string shaderFloder = GetApplicationPath() + "\\Shader\\";
	shader = new Shader((shaderFloder + "Light.Color.vs").c_str(), (shaderFloder + "Light.MultipleLights.fs").c_str());

	string modelFolder = GetApplicationPath() + "\\Model\\";
	model = new Model(modelFolder + "nanosuit/nanosuit.obj");
}

void ModelLoadPipeline::Release()
{
	if (shader != NULL)
		delete shader;

	if (model != NULL)
		delete model;
}

void ModelLoadPipeline::Update()
{
	BasePipeline::Update();

	model->Draw(*shader);
}