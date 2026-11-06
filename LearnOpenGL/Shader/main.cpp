#include "glad/glad.h"
#include "glfw-3.5.1/include/GLFW/glfw3.h"
#include <iostream>
#include <LearnOpenGL/Shader.h>

// 첫 번째 변수는 GLFWwindow 객체, 두 번째 인수는 새 창 크기를 나타내는 두개의 변수
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// 삼각형 그리기에 필요한 버퍼 등을 준비하는 함수
void InitTriangle();
// 삼각형을 렌더링하는 함수
void DrawTriangle();

//void InitPractice1();
//void DrawPractice1();
//
//void InitPractice2();
//void DrawPractice2();
//
//void InitPractice3();
//void DrawPractice3();

// 정점 셰이더의 소스 코드를 가져와서 상수 C문자열에 저장
//const char* vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"layout (location = 1 ) in vec3 aColor;\n"
//"out vec3 ourColor;\n"
//"void main()\n"
//"{\n"
//"	gl_Position = vec4(aPos, 1.0);\n"
//"	ourColor = aColor;\n"
//"}\0";
//
//// 프래그먼트 셰이더의 소스코드를 가져와서 상수 C문자열에 저장
//const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"in vec3 ourColor;\n"
//"void main()\n"
//"{\n"
//"	FragColor = vec4(ourColor,1.0f);\n"
//"}\n\0";

// 버퍼 객체 선언
unsigned int VBO;

float vertices[] = {
	// positions         // colors
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};

// 삼각형 정점
float triangle_vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

float practice1_vertices[] = {
	-1.f, -0.5f, 0.0f,
	-0.0f,-0.5f, 0.0f,
	-0.5f,0.5f, 0.0f,
	1.0f,-0.5f, 0.0f,
	0.f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f
};

float practice2_1_vertices[] = {
	-1.f, -0.5f, 0.0f,
	-0.0f,-0.5f, 0.0f,
	-0.5f,0.5f, 0.0f
};

float practice2_2_vertices[] = {
	1.0f,-0.5f, 0.0f,
	0.f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f
};

// ID로 참조되는 셰이더 객체를 생성
unsigned int vertexShader;

int success;
char infoLog[512];

unsigned int fragmentShader;

// 셰이더 프로그램 객체
unsigned int shaderProgram;

unsigned int VAO;

float square_vertices[] = {
	0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
};

unsigned int indices[] = {
	0,1,3,
	1,2,3
};

unsigned int EBO;

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

	// 렌더링 창의 크기를 OpenGL에 알려주는 일
	// glViewport의 첫 번째와 두 번째 매개 변수는 창의 왼쪽 아래 모서리 위치
	// 세 번째와 네 번째 매개변수는 렌더링 창의 너비와 높이를 픽샐 단위로 설정
	//glViewport(0, 0, 800, 600);

	// 창 크기를 조정하는 순간 뷰포트도 조정하는 콜백함수 등록
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glfwWindowShouldClose - 각 루프 반복 시작 시 GLFW에 창을 닫으라는 명령이 내려졌는지 확인
	// 명령이 내려졌다면 함수는 true를 반환하고 렌더링 루프가 중지되며, 애플리케이션이 종료
	// glfwPollEvents - 키보드 입력이나 마우스 움직임 이벤트와 같은 이벤트가 발생했는지 확인, 창 상태 업데이트
	//					해당 함수 호출
	// glfwSwapBuffers - 컬러 버퍼 교체와 교체된 버퍼를 화면에 출력

	// 셰이더 객체 선언
	Shader ourShader = Shader("3.3.shader.vs", "3.3.shader.fs");
	while (!glfwWindowShouldClose(window))
	{
		// 입력 처리
		processInput(window);

		// 렌더링 명령어들
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);

		// glfwGetTime()를 사용하여 실행 시간을 초 단위로 가져옴
		// sin 함수를 사용하여 색상을 0.0~1.0 범위로 변화시킴
		// glGetUniformLocation을 사용하여 ourColor 유니폼의 위치를 조회
		// 인수에는 셰이더 프로그램과 위치를 가져올 유니폼의 이름을 전달.
		// glUniform4f를 사용하여 유니폼 값을 서절할 수 있음.
		// 유니폼 위치를 찾는 데에는 셰이더 프로그램을 사용할 필요가 없지만,
		// 유니폼 값을 업데이트하려면 먼저 해당 프로그램을 사용해야 함.
		/*float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUseProgram(shaderProgram);
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/

		InitTriangle();
		ourShader.use();
		DrawTriangle(); 
		
		// 이벤트를 확인하고 호출한 다음 버퍼를 교체
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// GLFW에 할당된 모든 리소스를 정리/삭제
	glfwTerminate();

	return 0;
}

void InitTriangle()
{
	// 버퍼 ID와 함께 정점 버퍼 객체 생성
	glGenBuffers(1, &VBO);
	// GL_ARRAY_BUFFER에 VBO 바인딩
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// glBufferData : 현재 바인딩된 버퍼에 사용자 정의 데이터를 복사하는데 사용되는 함수
	// 첫 번째 인수 - 복사할 버퍼의 유형. 현재 GL_ARRAY_BUFFER에 정점 버퍼 객체가 바인딩되어 있음.
	// 두 번째 인수 - 버퍼에 전달할 데이터의 크기(바이트)
	// 세 번째 인수 - 실제로 전송할 데이터
	// 네 번째 인수 - 그래픽 카드가 주어진 데이터를 처리하는 방식 지정
	//glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
	//// glCreateShader를 이용해 셰이더 객체 생성
	//// glCreateShader는 생성할 셰이더 유형을 인수로 전달
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);

	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	//if (!success)
	//{
	//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}

	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);
	//glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}

	//shaderProgram = glCreateProgram();

	//// 이전에 컴파일한 셰이더를 프로그램 객체에 연결한 다음
	//// glLinkProgram 함수를 사용하여 링크해야 함
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);
	//glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	//if (!success)
	//{
	//	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::PROGRAM::LINKIN_FAILED\n" << infoLog << std::endl;
	//}

	//// glUseProgram 이후의 모든 셰이더 및 렌더링 호출은 프로그램 객체를 사용하게 됨
	//// 셰이더 객체를 프로그램 객체에 연결했으면 삭제해야 함.
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);

	// VAO를 바인딩하는 함수
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
		

	// 이건 바인딩되어 있는 객체를 해제하는 코드로 여기서는 안해도 상관 없음.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void DrawTriangle()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
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
}
