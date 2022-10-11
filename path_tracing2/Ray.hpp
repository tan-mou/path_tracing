#pragma once
#include<glm/glm.hpp>
#include<iostream>
using namespace glm;
using namespace std;
class Ray
{

public:
	vec3 direction;
	vec3 position;
	Ray() = default;
	Ray(vec3 d, vec3 p) {
		direction = d;
		position = p;
	}
	void Print(){
		cout << "direction:" << direction.x << " " << direction.y << " " << direction.z << endl;
		cout<<"position:" << position.x << " " << position.y << " " << position.z << endl;
	}
};

