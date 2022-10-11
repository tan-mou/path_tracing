#pragma once
#include"Ray.hpp"
#include"Material.hpp"
#include<time.h>
#include<random>

class Point
{
private:
    
public :
    Point() = default;
    Point(vec3 pos, vec3 n,Material m) {
        position = pos;
        normal = n;
        material = m;
    }
	void print() {
		cout <<"position:" << position.x << " " << position.y << " " << position.z << endl;
	}

    vec3 position;
    vec3 normal;
    Material material;
    float t;//ray and point patameter
};

