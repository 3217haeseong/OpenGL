//// 버퍼 객체 선언
//unsigned int VBO;
//// 버퍼 ID와 함께 정점 버퍼 객체 생성
//glGenBuffers(1, &VBO);
//// GL_ARRAY_BUFFER에 VBO 바인딩
//glBindBuffer(GL_ARRAY_BUFFER, VBO);
//// glBufferData : 현재 바인딩된 버퍼에 사용자 정의 데이터를 복사하는데 사용되는 함수
//// 첫 번째 인수 - 복사할 버퍼의 유형. 현재 GL_ARRAY_BUFFER에 정점 버퍼 객체가 바인딩되어 있음.
//// 두 번째 인수 - 버퍼에 전달할 데이터의 크기(바이트)
//// 세 번째 인수 - 실제로 전송할 데이터
//// 네 번째 인수 - 그래픽 카드가 주어진 데이터를 처리하는 방식 지정
//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//// 정점 셰이더의 소스 코드를 가져와서 상수 C문자열에 저장
//const char* vertexShaderSource = "#Version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"void main()\n"
//"{\n"
//"	gl_Position = vec4(a.Pos.x, aPos.y, aPos.z, 1.0);\n"
//"}\n";
//
//// ID로 참조되는 셰이더 객체를 생성
//unsigned int vertexShader;
//// glCreateShader를 이용해 셰이더 객체 생성
//// glCreateShader는 생성할 셰이더 유형을 인수로 전달
//vertexShader = glCreateShader(GL_VERTEX_SHADER);
//
//// 셰이더 소스 코드를 셰이더 객체에 연결하고 셰이더 컴파일
//// glShaderSource
//// 첫 번째 인수 - 컴파일된 셰이더와 연결할 셰이더 객체를 받음
//// 두 번째 인수 - 소스 코드로 전달할 문자열의 개수를 지정, 보통 1로 둔다
//// 세 번째 인수 - 실제 정점 셰이더의 소스 코드
//// 네 번째 인수 - 소스 코드의 길이. 보통 OpenGL이 알아서 함.
//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//glCompileShader(vertexShader);
//
//int success;
//char infoLog[512];
//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//
//if (!success)
//{
//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//}
//
//const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//"}\n";
//
//unsigned int fragmentShader;
//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//
//// 셰이더 프로그램 객체
//unsigned int shaderProgram;
//shaderProgram = glCreateProgram();
//
//// 이전에 컴파일한 셰이더를 프로그램 객체에 연결한 다음
//// glLinkProgram 함수를 사용하여 링크해야 함
//glAttachShader(shaderProgram, vertexShader);
//glAttachShader(shaderProgram, fragmentShader);
//glLinkProgram(shaderProgram);
//
//// glUseProgram 이후의 모든 셰이더 및 렌더링 호출은 프로그램 객체를 사용하게 됨
//glUseProgram(shaderProgram);
//
//// 셰이더 객체를 프로그램 객체에 연결했으면 삭제해야 함.
//glDeleteShader(vertexShader);
//glDeleteShader(fragmentShader);
//
//// 정점 버퍼 데이터를 어떤식으로 해석해야 하는지를 알려주는 함수
//// 첫 번째 인수 - 설정하려는 정점의 속성이 무엇인지를 지정해야 함.
//// 두 번째 인수 - 정점 속성의 크기 지정. 여기서는 vec3이므로 3을 지정
//// 세 번째 인수 - 데이터 유형 지정
//// 네 번째 인수 - 데이터를 정규화할지 여부 지정
//// 다섯 번째 인수 - 스트라이드라고 하며, 연속된 정점 속성 값 사이의 간격을 나타냄
//// 여섯 번째 인수 - 버퍼에서 위치 데이터가 시작되는 위치의 오프셋
//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//// 정점 속성 활성화
//glEnableVertexAttribArray(0);
//
//// OpenGL에서 객체를 그리는 전체 과정
//// OpenGL에서 사용할 수 있도록 정점 배열을 버퍼에 복사
//glBindBuffer(GL_ARRAY_BUFFER, VBO);
//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//// 정점 속성 포인터를 설정
//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//glEnableVertexAttribArray(0);
//// 객체를 렌더링할 때 우리의 셰이더 프로그램을 사용하도록 설정
//glUseProgram(shaderProgram);