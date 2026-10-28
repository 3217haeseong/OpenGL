#include "glad/glad.h"
#include "../glfw-3.5.1/include/GLFW/glfw3.h"
#include <iostream>

// 첫 번째 변수는 GLFWwindow 객체, 두 번째 인수는 새 창 크기를 나타내는 두개의 변수
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

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
	glViewport(0, 0, 800, 600);

	// 창 크기를 조정하는 순간 뷰포트도 조정하는 콜백함수 등록
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glfwWindowShouldClose - 각 루프 반복 시작 시 GLFW에 창을 닫으라는 명령이 내려졌는지 확인
	// 명령이 내려졌다면 함수는 true를 반환하고 렌더링 루프가 중지되며, 애플리케이션이 종료
	// glfwPollEvents - 키보드 입력이나 마우스 움직임 이벤트와 같은 이벤트가 발생했는지 확인, 창 상태 업데이트
	//					해당 함수 호출
	// glfwSwapBuffers - 컬러 버퍼 교체와 교체된 버퍼를 화면에 출력
	while (!glfwWindowShouldClose(window))
	{
		// 입력 처리
		processInput(window);

		// 렌더링 명령어들
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 이벤트를 확인하고 호출한 다음 버퍼를 교체

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
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
}