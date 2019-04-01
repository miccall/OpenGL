#pragma once
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;
namespace miccall {

	// camera
	extern glm::vec3 cameraPos;
	extern glm::vec3 cameraFront;
	extern glm::vec3 cameraUp;

	// timing
	extern float deltaTime;
	extern float lastFrame;

	// mouse control var 
	extern bool firstMouse;
	extern float yaw;
	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	extern float pitch;
	extern float lastX;
	extern float lastY;
	extern float fov;
	extern unsigned int SCR_WIDTH;
	extern unsigned int SCR_HEIGHT;

	enum Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	// Default camera values
	extern const float YAW;
	extern const float PITCH;
	extern const float SPEED;
	extern const float SENSITIVTY;
	extern const float ZOOM;

	//����GLFw
	void ConfigGLFwWindow();

	//����windows������
	GLFWwindow * InitGLFWwindow(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);

	//���shader����
	void CheckCompileErrors(int shader);
	void CheckCompileErrors(GLuint shader, std::string type);

	//������Ӵ���
	void CheckProgramErrors(int program);

	//����shader �������ӳ���
	int LinkShader(int &vertex, int &frag);

	//�������� 
	void processInput(GLFWwindow *window);

	//��ȾԤ����
	void CustomRender();



	//�����ֺ��ƶ����¼� 
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	//��������
	unsigned int creatTexture(const char * filename);

	glm::mat4 projectionMatrix();
	glm::mat4 viewMatrix();


	unsigned int loadTexture(char const * path);
	unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

	class Shader
	{
	public:
		// ����ID
		unsigned int ID;
		// ��������ȡ��������ɫ��
		Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath);
		// ʹ��/�������
		void use();
		// uniform���ߺ���
		void setBool(const std::string &name, bool value) const;
		void setInt(const std::string &name, int value) const;
		void setFloat(const std::string &name, float value) const;
		void setVec2(const std::string & name, const glm::vec2 & value) const;
		void setVec2(const std::string & name, float x, float y) const;
		void setVec3(const std::string & name, const glm::vec3 & value) const;
		void setVec3(const std::string & name, float x, float y, float z) const;
		void setVec4(const std::string & name, const glm::vec4 & value) const;
		void setVec4(const std::string & name, float x, float y, float z, float w);
		void setMat2(const std::string & name, const glm::mat2 & mat) const;
		void setMat3(const std::string & name, const glm::mat3 & mat) const;
		void setMat4(const std::string & name, const glm::mat4 & mat) const;
	};

	class Camera {
	public:
		// Camera Attributes
		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 WorldUp;
		// Eular Angles
		float Yaw;
		float Pitch;
		// Camera options
		float MovementSpeed;
		float MouseSensitivity;
		float Zoom;

		// Constructor with vectors
		//Camera(glm::vec3 position , glm::vec3 up, float yaw, float pitch);
		Camera();
		Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
		// Constructor with scalar values
		Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

		// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
		glm::mat4 GetViewMatrix();

		// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
		void ProcessKeyboard(Camera_Movement direction, float deltaTime);

		// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
		void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch);

		// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
		void ProcessMouseScroll(float yoffset);
	private:
		// Calculates the front vector from the Camera's (updated) Eular Angles
		void updateCameraVectors();
	};

	extern Camera camera;
}
