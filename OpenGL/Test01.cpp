#include "MyCourses.h"
/**
* ��һ�� ����ʼ��һ��GL window
*/
int Test01()
{
	// ����GL-Window �� GLFW ��  
	ConfigGLFwWindow();

	// ��ʼ������ 
	GLFWwindow* window = InitGLFWwindow(SCR_WIDTH, SCR_HEIGHT);

	if (window == nullptr)
	{
		// ��ʼ��ʧ��
		return -1;
	}

	// ��Ⱦѭ��(Render Loop)
	// ---------------------------------------------------------------------------------------------------------
	while (!glfwWindowShouldClose(window) /* �������û�йر� */)
	{
		// ----- �û����� 
		processInput(window);

		// ------ �Զ�����Ⱦ 
		CustomRender();

		// �� glfw: ��������������ѯIO�¼��� ����/�ͷż�������ƶ��� )
		// -------------------------------------------------------------------------------
		// ������ɫ���� 
		glfwSwapBuffers(window);
		// �����û�д����¼�
		glfwPollEvents();
	}
	// ��Ⱦѭ�� ������ ������Ҫ ��ȷ �ͷ�/ɾ�� ֮ǰ�ķ����������Դ 
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}