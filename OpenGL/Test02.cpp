#include "MyCourses.h"
/**
* �ڶ��� ������һ��������
*
* ������ɫ�� ƬԪ��ɫ���Ĵ����ͱ���
* ����������� ��������������ʶ
*
*/

int Test02()
{
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
	if (window == nullptr) return -1;

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

	// xyz��xyz��xyz �� �����ε������� �� 4���ֽ� * 9�� == 36�ֽ� 
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	// ======================   �����ݷ��͵� GPU ��     ====vbo���� ��vbo ����vbo ================================================================================
	unsigned int VBO;
	// ����VBO 
	glGenBuffers(1, &VBO);
	// ��vbo
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// �� ���� ���� ����ǰ�󶨵� ���� 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ======================  VAO ���� ==============================================
	unsigned int VAO;
	//���� VAO
	glGenVertexArrays(1, &VAO);
	//��VAO 
	glBindVertexArray(VAO);

	// 3. ���ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind

	// �����
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


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
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// �� glfw: ��������������ѯIO�¼�������/�ͷż�������ƶ��� )
		// -------------------------------------------------------------------------------
		// ������ɫ���� 
		glfwSwapBuffers(window);
		// �����û�д����¼�
		glfwPollEvents();
	}
	// ��Ⱦѭ�� ������ ������Ҫ ��ȷ �ͷ�/ɾ�� ֮ǰ�ķ����������Դ 
	// ------------------------------------------------------------------

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;

}