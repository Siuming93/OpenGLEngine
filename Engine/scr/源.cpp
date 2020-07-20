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
#include "../Advanced/advancedPipeline.h"
using namespace std;

void Run()
{
	BasePipeline* pipeline = NULL;

	pipeline = new GettingStartPipeline;
	pipeline = new LightPipeline;
	pipeline = new ModelLoadPipeline;
	pipeline = new AdvancedPipeline;


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

