#pragma once
#include <string>

class Shader
{
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	void Use();
private:
	unsigned int m_ID;
};

