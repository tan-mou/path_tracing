#pragma once
#include<glm/glm.hpp>
using namespace glm;
class Material
{
public:
	const char* type;//Material type
	vec3 Kd;
	bool emit;
	Material() =default;
	Material(const char* t, vec3 kd, bool e) {
		type = t;
		Kd = kd;
		emit = e;
	}
};

