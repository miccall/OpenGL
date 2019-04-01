#include "MyCourses.h"

/*
* ʹ�ô��ļ����ص�Shader
*/
int Test07()
{
	ConfigGLFwWindow();
	GLFWwindow * window = InitGLFWwindow(SCR_WIDTH, SCR_HEIGHT);
	if (window == nullptr)
	{
		return -1;
	}
	Shader ourShader("Shader01.vs", "Shader01.fs", nullptr);
	float vertices[] = {
		// positions         // colors
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 

	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/**
	*  glVertexAttribPointer
	*  ��һ�������Ǵ�����ɫ���е� location ֵ
	*  �ڶ���������ָ���������� Vec3 =>  3
	*  ���������Ĳ�����ֵ���� FLOAT �� �Ƿ�ϣ�����ݱ���׼�� FALSE
	*  ����������ǲ���(Stride) �� ��һ�����ݵ��ڶ�����ͬ�������ݵļ�� ����һ�������������Ϣ���ܵ�λ��
	*  ���������� �� λ�������ڻ�������ʼλ�õ�ƫ������Ҳ�������������ʼ��λ�õ���ͷ�ľ��� ��
	*/

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		CustomRender();
		ourShader.use();
		// glUseProgram(shaderprogram);
		glBindVertexArray(VAO);
		// ���ƶ������ ��ƫ�� 
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}