#pragma once
#include<vector>
#include"Point.hpp"
#include"Material.hpp"
#include"Ray.hpp"
class Object
{
public:
    
private:

};
class Triangle :Object {
public  :
    Triangle(vec3 position1, vec3 position2, vec3 position3, vec3 n, Material m) {
        normal = n;
        Point point1(position1, normal,m);
        Point point2(position2, normal,m);
        Point point3(position3, normal,m);
        P.push_back(point1);
        P.push_back(point2);
        P.push_back(point3);
        material = m;
    }
    vector<Point> P;
    vec3 normal;
    Material material;

};

