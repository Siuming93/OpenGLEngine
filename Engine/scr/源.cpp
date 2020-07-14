#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include "../include/BasePipeline.hpp"
#include "../GettingStart/GettingStartPipeline.h"
#include "../Light/LightPipeline.h"
#include "../ModelLoad/modelLoadPipeLine.h"
using namespace std;

void Run()
{
	BasePipeline* pipeline = NULL;
	int type = 2;
	switch (type)
	{
	case 0:
		pipeline = new GettingStartPipeline;
		break;
	case 1:
		pipeline = new LightPipeline;
		break;
	case 2:
		pipeline = new ModelLoadPipeline;
		break;
	default:
		break;
	}

	auto r = pipeline->Init();
	if (!r)
		return;

	pipeline->Loop();
}

int main()
{
	while (true)
	{
		Run();

		cout << "渲染已结束,按下回车键重新启动..." << endl;

		while (true)
		{
			int code = _getch();
			//cout << code << endl;

			if (code == 13)
				break;

			if (code == 27 || code == 3)
				return 0;

		}
	}
	return 0;
}

