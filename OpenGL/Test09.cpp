#include "MyCourses.h"
/**
*  ��ϰ��ʹ��������ͼ��һ������ ��
*/
int Test09()
{
	ConfigGLFwWindow();
	GLFWwindow * window = InitGLFWwindow(SCR_WIDTH, SCR_HEIGHT);
	if (window == nullptr)
	{
		return -1;
	}
	// ��ɫ�� 
	Shader ourShader("Shader08.vs", "Shader08.fs", nullptr);

	// ����
	float vertices[] = {
		//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
		-0.5f,  -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,    // ����
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
	};

	unsigned int index[] = {
		0 , 1 , 2 ,
		0 , 2 , 3
	};
	// GPU����
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// uv attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	//����һ����ͼ
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Ϊ��ǰ�󶨵������������û��ơ����˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//��ʼ����ԴͼƬ
	int width, height, nrChannels;
	unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

	//ʹ���������ԴͼƬ�����ͼ
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	//�ͷ��ڴ�
	stbi_image_free(data);



	// ��Ⱦ��ʽ 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		CustomRender();

		//����ͼ
		glBindTexture(GL_TEXTURE_2D, texture);
		//glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		ourShader.use();
		// glUseProgram(shaderprogram);
		glBindVertexArray(VAO);
		// ���ƶ������ ��ƫ�� 
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}