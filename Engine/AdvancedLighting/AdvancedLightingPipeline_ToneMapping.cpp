#include "AdvancedLightingPipeline_ToneMapping.h"

bool AdvancedLightingPipeline_ToneMapping::Init()
{
	if (!BasePipeline::Init())
	{
		return false;
	}
}


void AdvancedLightingPipeline_ToneMapping::Release()
{
}

void AdvancedLightingPipeline_ToneMapping::Update()
{
	BasePipeline::Update();

    //先clear



    //监听窗口事件
    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------
	glfwSwapBuffers(window);
	glfwPollEvents();
}