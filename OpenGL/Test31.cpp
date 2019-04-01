#include "MyCourses.h"

/*
	ģ����ԣ�
*/

int Test31()
{
	// glfw ���ڹ��� opengl 
	ConfigGLFwWindow();
	GLFWwindow *window = InitGLFWwindow(SCR_WIDTH, SCR_HEIGHT);
	if (window == nullptr) return -1;

	// ����ģ�建��
	glEnable(GL_STENCIL_TEST);

	// ������Ȼ���
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// ��ɫ����ģ�ͣ�
	Shader ourShader("Shader30.vs", "Shader30.fs", nullptr);
	Model ourModel("cube/plane.obj");

	Model cube("cube/cube.obj");
	Model plane("cube/plane.obj");

	// ��Ⱦѭ�� 
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		CustomRender();

		RenderCube(ourShader, plane, glm::vec3(0.0f, -1.2f, -1.0f), glm::vec3(2.0f, 0.5f, 2.0f));
		RenderCube(ourShader, cube, glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f));
		RenderCube(ourShader, cube, glm::vec3(-0.2f, -1.0f, -3.0f), glm::vec3(0.5f, 0.5f, 0.5f));

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
