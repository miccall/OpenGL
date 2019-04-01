#include "MyGLLib.h"

void miccall::ConfigGLFwWindow() {

	// glfw: initialize and configure
	// ------------------------------
	// ���� glfwInit() ����ʼ��GLFW 
	glfwInit();

	//----------------- glfwWindowHint ( ѡ������� , ѡ���ֵ ) ���� GLFW------ ------------------
	// �����汾��(Major) �� �ΰ汾��(Minor)����Ϊ 3  
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// ����GLFW����ʹ�õ��Ǻ���ģʽ( Core-profile ) 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // ���ʹ�õ���ƻ��ϵͳ ��ִ����һ�� 
#endif
}

GLFWwindow * miccall::InitGLFWwindow(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT)
{
	// glfw ����һ�����ڶ��� 
	// --------------------
	// glfwCreateWindow( ���ڵĿ�� �����ڵĸ߶� �����������ƣ����⣩����null��null )  
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

	if (window == nullptr)
	{
		// ��������ʧ��
		cout << " Failed to create GLFW window" << endl;
		// ��ֹ���� 
		glfwTerminate();
		return nullptr;
	}

	// ֪ͨ GLFW �����Ǵ��ڵ�����������Ϊ��ǰ�̵߳��������� 
	glfwMakeContextCurrent(window);

	// ���û��ı䴰�ڵĴ�С��ʱ���ӿ�ҲӦ�ñ����� ����Ҫע��ص�����  
	// ÿ�����ڸı��С��GLFW����� framebuffer_size_callback ���� �������Ӧ�Ĳ������㴦�� 
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// glad: GLAD����������OpenGL�ĺ���ָ��� 
	// ---------------------------------------
	// ��GLAD��������������ϵͳ��ص�OpenGL����ָ���ַ�ĺ���  glfwGetProcAddress�����������Ǳ����ϵͳ��������ȷ�ĺ����� 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		// �������ʧ�� 
		cout << "Failed to initialize GLAD" << endl;
		return NULL;
	}
	return window;
}

void miccall::CheckCompileErrors(int shader)
{
	int  success;
	char infoLog[512];
	// ����Ƿ����ɹ� ��
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	//���ʧ�� ����ӡ������Ϣ 
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}
}

void miccall::CheckCompileErrors(GLuint shader, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}

void miccall::CheckProgramErrors(int program)
{
	int  success;
	char infoLog[512];
	// ����Ƿ����ɹ� ��
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n " << infoLog << std::endl;
	}
}

unsigned int miccall::creatTexture(const char * filename)
{
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	// Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//��ʼ����ԴͼƬ
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char * data = stbi_load(filename, &width, &height, &nrChannels, 0);

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
	return texture1;
}

int miccall::LinkShader(int &vertex, int &frag)
{
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertex);
	glAttachShader(shaderProgram, frag);
	glLinkProgram(shaderProgram);

	//====================  ������Ӵ��� ==================

	CheckProgramErrors(shaderProgram);

	// �ڰ���ɫ���������ӵ���������Ժ󣬼ǵ�ɾ����ɫ���������ǲ�����Ҫ������ 
	glDeleteShader(vertex);
	glDeleteShader(frag);

	return shaderProgram;

}

void miccall::processInput(GLFWwindow *window)
{

	// glfwGetKey(window , keycode�������� )   �Ƿ����ڱ�����  
	// �������Ǽ���û��Ƿ����˷��ؼ�(Esc) 
	// glfwSetwindowShouldClose ʹ�ð� WindowShouldClose ��������Ϊ true �ķ����ر� GLFW 
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	/*
	float cameraSpeed = 2.5 * (deltaTime);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	*/

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);

}

void miccall::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void miccall::CustomRender()
{
	// glClearColor������һ��״̬���ú�������glClear��������һ��״̬ʹ�õĺ�������ʹ���˵�ǰ��״̬����ȡӦ�����Ϊ����ɫ�� 
	// ��������������ɫ 
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	//�����Ļ����ɫ���� ���øո�glClearColor���õ���ɫȥ������
	glClear(GL_COLOR_BUFFER_BIT);
	if (GL_DEPTH_TEST)
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}
	if (GL_STENCIL_TEST)
	{
		glClear(GL_STENCIL_BUFFER_BIT);
	}

	// ���㵱ǰ֡����һ֡��ʱ��
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

}

void miccall::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	/*
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
	*/
	camera.ProcessMouseScroll(yoffset);

}

void miccall::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	/*
	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);

	*/
	camera.ProcessMouseMovement(xoffset, yoffset, true);
}

glm::mat4  miccall::projectionMatrix()
{
	float ifov = camera.Zoom;
	glm::mat4 projection = glm::perspective(glm::radians(ifov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	return projection;
}

glm::mat4  miccall::viewMatrix()
{
	return camera.GetViewMatrix();
}

unsigned int miccall::loadTexture(char const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

unsigned int miccall::TextureFromFile(const char * path, const string & directory, bool gamma)
{
	string filename = string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

