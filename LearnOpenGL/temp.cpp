//#include "glad/glad.h"
//#include "../glfw-3.5.1/include/GLFW/glfw3.h"
//#include <iostream>
//
//// 첫 번째 변수는 GLFWwindow 객체, 두 번째 인수는 새 창 크기를 나타내는 두개의 변수
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow* window);
//
//// 정점 셰이더의 소스 코드를 가져와서 상수 C문자열에 저장
//const char* vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"void main()\n"
//"{\n"
//"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"}\0";
//
//// 프래그먼트 셰이더의 소스코드를 가져와서 상수 C문자열에 저장
//const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//"}\n\0";
//
//int main()
//{
//	// glfw 초기화
//	glfwInit();
//	// GLFW 설정
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	// 윈도우 객체 생성
//	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//
//	// OpenGL의 함수 포인터는 GLAD가 관리
//	// GLAD 초기화
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	// 렌더링 창의 크기를 OpenGL에 알려주는 일
//	// glViewport의 첫 번째와 두 번째 매개 변수는 창의 왼쪽 아래 모서리 위치
//	// 세 번째와 네 번째 매개변수는 렌더링 창의 너비와 높이를 픽샐 단위로 설정
//	//glViewport(0, 0, 800, 600);
//
//	// 창 크기를 조정하는 순간 뷰포트도 조정하는 콜백함수 등록
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//	float vertices[] = {
//	-0.5f, -0.5f, 0.0f,
//	 0.5f, -0.5f, 0.0f,
//	 0.0f,  0.5f, 0.0f
//	};
//
//	// 버퍼 객체 선언
//	unsigned int VBO;
//	// 버퍼 ID와 함께 정점 버퍼 객체 생성
//	glGenBuffers(1, &VBO);
//	// GL_ARRAY_BUFFER에 VBO 바인딩
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	// glBufferData : 현재 바인딩된 버퍼에 사용자 정의 데이터를 복사하는데 사용되는 함수
//	// 첫 번째 인수 - 복사할 버퍼의 유형. 현재 GL_ARRAY_BUFFER에 정점 버퍼 객체가 바인딩되어 있음.
//	// 두 번째 인수 - 버퍼에 전달할 데이터의 크기(바이트)
//	// 세 번째 인수 - 실제로 전송할 데이터
//	// 네 번째 인수 - 그래픽 카드가 주어진 데이터를 처리하는 방식 지정
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//
//
//	// ID로 참조되는 셰이더 객체를 생성
//	unsigned int vertexShader;
//	// glCreateShader를 이용해 셰이더 객체 생성
//	// glCreateShader는 생성할 셰이더 유형을 인수로 전달
//	vertexShader = glCreateShader(GL_VERTEX_SHADER);
//
//	// 셰이더 소스 코드를 셰이더 객체에 연결하고 셰이더 컴파일
//	// glShaderSource
//	// 첫 번째 인수 - 컴파일된 셰이더와 연결할 셰이더 객체를 받음
//	// 두 번째 인수 - 소스 코드로 전달할 문자열의 개수를 지정, 보통 1로 둔다
//	// 세 번째 인수 - 실제 정점 셰이더의 소스 코드
//	// 네 번째 인수 - 소스 코드의 길이. 보통 OpenGL이 알아서 함.
//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//	glCompileShader(vertexShader);
//
//	int success;
//	char infoLog[512];
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//
//	if (!success)
//	{
//		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//
//	unsigned int fragmentShader;
//	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//	glCompileShader(fragmentShader);
//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//	if (!success)
//	{
//		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//
//	// 셰이더 프로그램 객체
//	unsigned int shaderProgram;
//	shaderProgram = glCreateProgram();
//
//	// 이전에 컴파일한 셰이더를 프로그램 객체에 연결한 다음
//	// glLinkProgram 함수를 사용하여 링크해야 함
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//	if (!success)
//	{
//		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::PROGRAM::LINKIN_FAILED\n" << infoLog << std::endl;
//	}
//
//	// glUseProgram 이후의 모든 셰이더 및 렌더링 호출은 프로그램 객체를 사용하게 됨
//	// 셰이더 객체를 프로그램 객체에 연결했으면 삭제해야 함.
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//	// 정점 버퍼 데이터를 어떤식으로 해석해야 하는지를 알려주는 함수
//	// 첫 번째 인수 - 설정하려는 정점의 속성이 무엇인지를 지정해야 함.
//	// 두 번째 인수 - 정점 속성의 크기 지정. 여기서는 vec3이므로 3을 지정
//	// 세 번째 인수 - 데이터 유형 지정
//	// 네 번째 인수 - 데이터를 정규화할지 여부 지정
//	// 다섯 번째 인수 - 스트라이드라고 하며, 연속된 정점 속성 값 사이의 간격을 나타냄
//	// 여섯 번째 인수 - 버퍼에서 위치 데이터가 시작되는 위치의 오프셋
//
//	unsigned int VAO;
//	// VAO를 바인딩하는 함수
//	glGenVertexArrays(1, &VAO);
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	// 이건 바인딩되어 있는 객체를 해제하는 코드로 여기서는 안해도 상관 없음.
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//
//	// glfwWindowShouldClose - 각 루프 반복 시작 시 GLFW에 창을 닫으라는 명령이 내려졌는지 확인
//	// 명령이 내려졌다면 함수는 true를 반환하고 렌더링 루프가 중지되며, 애플리케이션이 종료
//	// glfwPollEvents - 키보드 입력이나 마우스 움직임 이벤트와 같은 이벤트가 발생했는지 확인, 창 상태 업데이트
//	//					해당 함수 호출
//	// glfwSwapBuffers - 컬러 버퍼 교체와 교체된 버퍼를 화면에 출력
//	while (!glfwWindowShouldClose(window))
//	{
//		// 입력 처리
//		processInput(window);
//
//		// 렌더링 명령어들
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//		glUseProgram(shaderProgram);
//		glBindVertexArray(VAO);
//		// 첫 번째 인수 - OpenGL 프리미티브 타입
//		// 두 번째 인수 - 정점 배열의 시작 인덱스
//		// 마지막 인수 - 그릴 정점의 개수 지정
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//
//		// 이벤트를 확인하고 호출한 다음 버퍼를 교체
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteProgram(shaderProgram);
//
//	// GLFW에 할당된 모든 리소스를 정리/삭제
//	glfwTerminate();
//
//	return 0;
//}
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);
//}
//
//void processInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//	{
//		glfwSetWindowShouldClose(window, true);
//	}
//}