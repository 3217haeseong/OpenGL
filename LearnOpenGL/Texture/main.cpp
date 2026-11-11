
#include "glad/glad.h"
#include "glfw-3.5.1/include/GLFW/glfw3.h"
#include <LearnOpenGL/Shader.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// 첫 번째 변수는 GLFWwindow 객체, 두 번째 인수는 새 창 크기를 나타내는 두개의 변수
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

void InitTexture();
void DrawTexture();

// 버퍼 객체 선언
unsigned int VBO;

// ID로 참조되는 셰이더 객체를 생성
unsigned int vertexShader;

int success;
char infoLog[512];

unsigned int fragmentShader;

// 셰이더 프로그램 객체
unsigned int shaderProgram;

unsigned int VAO;

unsigned int EBO;

unsigned int texture;

float vertices[] = {
	// positions          // colors           // texture coords
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
};

//float vertices[] = {
//	// positions          // colors           // texture coords (note that we changed them to 2.0f!)
//	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f, // top right
//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f, // bottom right
//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f  // top left 
//};
unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};


float texCoords[] = {
	0.0f, 0.0f,  // lower-left corner  
	1.0f, 0.0f,  // lower-right corner
	0.5f, 1.0f   // top-center corner
};

unsigned char* data;
unsigned char* data2;

unsigned int texture1, texture2;

int width, height, nrChannels;

float ratio = 0.5f;

int main()
{
	// glfw 초기화
	glfwInit();
	// GLFW 설정
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 윈도우 객체 생성
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// OpenGL의 함수 포인터는 GLAD가 관리
	// GLAD 초기화
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// 창 크기를 조정하는 순간 뷰포트도 조정하는 콜백함수 등록
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// 첫 번째 인수 - 텍스처 대상
	// 두 번째 인수 - 설정할 옵션과 텍스처 축을 지정해야 함.
	// 마지막 인수 - 텍스처 래핑 모드 전달
	// 마지막을 GL_CLAMP_TO_BORDER를 선택하는 경우 테두리 색상도 지정해야함
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);*/

	// GL_CLAMP_TO_BORDER 옵션
	// glTexParameterfv 사용, 테두리 색상 값을 담은 float 배열을 전달
	/*float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);*/

	// 텍스처 필터링
	// GL_NEAREST : 텍스처를 구성하는 픽세일 명확하게 보이는 블록 패턴
	// GL_LINEAR : 개별 픽셀이 덜 보이는 더 부드러운 패턴을 생성
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/

	// 밉맵 설정
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/

	
	// 첫 번째 인수 - 파일의 위치를 입력받음
	// 두 번째 인수 - 이미지의 너비
	// 세 번째 인수 - 이미지의 높이
	// 마지막 인수 - 색상 채널 수 
	//data = stbi_load("container.jpg", &width, &height,&nrChannels,0);

	// 먼저 생성할 텍스처의 개수를 입력으로 받아 두 번째 인수로 제공된 부호 없는 정수 배열에 저장.
	/*glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);*/

	// 첫 번째 인수 - 택스처 대상 지정
	// 두 번째 인수 - 텍스처를 생성할 밉맵 레벨 지정, 기본값인 0으로 둔다
	// 세 번째 인수 - OpenGL에게 텍스처를 어떤 형식으로 저장할지 알려줌
	// 네 번째와 다섯 번째 - 텍스처의 너비와 높이
	// 6번째는 항상 0이여야 함.
	// 7번째, 8번째는 소스 이미지의 형식과 데이터 유형 지정, RGB 값으로 문자(바이트)로 저장한 것을 의미
	// 마지막 인수 - 실제 이미지 데이터
	/*glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);*/

	//Shader TextureShader = Shader("Texture.vs", "Texture.fs");
	//Shader Practice1Shader = Shader("Texture.vs", "TexturePractice1.fs");
	Shader Practice4Shader = Shader("Texture.vs", "TexturePractice4.fs");
	InitTexture();
	Practice4Shader.use();
	//Practice1Shader.use();
	/*glUniform1i(glGetUniformLocation(TextureShader.ID, "texture1"), 0);
	TextureShader.setInt("texture2", 1);*/
	//Practice4Shader.setFloat("ratio", ratio);
	Practice4Shader.setInt("texture1", 0);
	Practice4Shader.setInt("texture2", 1);
	while (!glfwWindowShouldClose(window))
	{
		// 입력 처리
		processInput(window);

		// 렌더링 명령어들
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		
		Practice4Shader.use();
		glBindVertexArray(VAO);
		Practice4Shader.setFloat("ratio", ratio);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// 이벤트를 확인하고 호출한 다음 버퍼를 교체
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	// GLFW에 할당된 모든 리소스를 정리/삭제
	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		ratio = ratio + 0.001f;
		if (ratio >= 1.0f)
		{
			ratio = 1.0f;
		}
		std::cout << "UP_KEY " <<ratio << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		ratio = ratio - 0.001f;
		if (ratio <= 0.0f)
		{
			ratio = 0.0f;
		}
		std::cout << "DOWN_KEY " <<ratio << std::endl;
	}
}

void InitTexture()
{
	glGenBuffers(1,&VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// load and create a texture
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);

	data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

void DrawTexture()
{
}
