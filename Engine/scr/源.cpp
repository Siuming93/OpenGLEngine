#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include "../include/BasePipeline.hpp"
#include "../GettingStart/GettingStartPipeline.h"
#include "../Light/LightPipeline.h"
using namespace std;

int main()
{
	BasePipeline* pipeline = NULL;
	int type = 1;
	switch (type)
	{
	case 0:
		pipeline = new GettingStartPipeline;
		break;
	case 1:
		pipeline = new LightPipeline;
		break;
	default:
		break;
	}

	auto r = pipeline->Init();
	if (!r)
		return 0;

	pipeline->Loop();

	return 0;
}

