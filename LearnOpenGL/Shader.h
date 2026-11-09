#pragma once

#ifndef  SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	// 프로그램 ID
	unsigned int ID;

	// 셰이더를 읽고 생성하는 생성자
	Shader(const char* vertexPath, const char* fragmentPath);

	// 셰이더 사용/활성화
	void use();

	// 유니폼 관련 유틸리티 함수
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
};

#endif // ! SHADER_H
