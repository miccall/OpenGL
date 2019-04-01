#include "MyCourses.h"
/**
* ������ �� ����һ������
*
* ������������ѧϰ
*
*/

int Test03() {
	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";
	ConfigGLFwWindow();
	GLFWwindow* window = InitGLFWwindow(SCR_WIDTH, SCR_HEIGHT);
	if (window == nullptr)
	{
		// ��ʼ��ʧ��
		return -1;
	}

	// =========================  ����shader =�������=����=���================================================================= 

	int vertshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertshader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertshader);
	CheckCompileErrors(vertshader);

	int fragshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragshader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragshader);
	CheckCompileErrors(fragshader);

	// =========================== ���� shader =========================================================================================

	int shaderprogram = LinkShader(vertshader, fragshader);

	// ========================== ���ö������� ===============================================================================

	// һ������ �������������ι��ɣ�����Ҫ���� 4�ֽ� * 18�� = 72 �ֽ� 
	/*
	float vertices[] = {
		// ��һ��������
		0.5f, 0.5f, 0.0f,   // ���Ͻ�
		0.5f, -0.5f, 0.0f,  // ���½�
		-0.5f, 0.5f, 0.0f,  // ���Ͻ�
		// �ڶ���������
		0.5f, -0.5f, 0.0f,  // ���½�
		-0.5f, -0.5f, 0.0f, // ���½�
		-0.5f, 0.5f, 0.0f   // ���Ͻ�
	};

	�������˷ѵ�

	*/

	// һ�����ε��ĸ����� ��4�ֽ� * 12 = 48�ֽ�  
	float vertices[] = {
		0.5f, 0.5f, 0.0f,   // ���Ͻ�
		0.5f, -0.5f, 0.0f,  // ���½�
		-0.5f, -0.5f, 0.0f, // ���½�
		-0.5f, 0.5f, 0.0f   // ���Ͻ�
	};

	// ���ε�������vertices[]���˳�� 
	unsigned int indices[] = { // ע��������0��ʼ! 
		0, 1, 3, // ��һ��������
		1, 2, 3  // �ڶ���������
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	//�߿�ģʽ��Ⱦ
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//���ģʽ��Ⱦ
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// ��Ⱦѭ��(Render Loop)
	// ---------------------------------------------------------------------------------------------------------
	while (!glfwWindowShouldClose(window) /* �������û�йر� */)
	{
		// ----- �û����� 
		processInput(window);

		// ------ �Զ�����Ⱦ 
		CustomRender();

		glUseProgram(shaderprogram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// �� glfw: ��������������ѯIO�¼�������/�ͷż�������ƶ��� )
		// -------------------------------------------------------------------------------
		// ������ɫ���� 
		//glBindVertexArray(0);
		glfwSwapBuffers(window);
		// �����û�д����¼�
		glfwPollEvents();
	}
	// ��Ⱦѭ�� ������ ������Ҫ ��ȷ �ͷ�/ɾ�� ֮ǰ�ķ����������Դ 
	// ------------------------------------------------------------------

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}