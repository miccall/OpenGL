#include "MyCourses.h"

/*
*  ����任
*/

int Test10()
{
	/*
	*  λ�ƾ����ʹ��
	*/
	glm::vec4 vec(0.0f, 1.0f, 0.0f, 0.0f);
	// vec = 1 0 0 1 
	glm::mat4 trans;


	// ���� trans �ƶ�Ϊ  1 1 0 
	//trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));

	/*
	*  ������� ��ת��������ž���
	*/
	// ��z����ת90��  �� radians���Ƕ�ת��Ϊ���� ��
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));


	// ÿ���ᶼ���ŵ�0.5��
	//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));


	vec = trans * vec;
	// 0.5  2  0  
	std::cout << vec.x << "\n" << vec.y << "\n" << vec.z << " " << std::endl;


	while (1)
	{
		;
	}
	return 0;
}