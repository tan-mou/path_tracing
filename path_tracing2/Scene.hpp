#pragma once
#include"Object.hpp"
class Scene
{
private:
	const float Width;
	const float Height;
	const float Standard_Z;
	const float Fov;
	
	
public:
	
	Scene(float width, float height, float standard_z, float fov) :Width(width), Height(height), Standard_Z(standard_z), Fov(fov) {}
	vector<Triangle> Tri;
	void Add_Tri(vec3 position1, vec3 position2, vec3 position3, vec3 n, Material m) {
		Triangle t(position1, position2, position3, n, m);
		Tri.push_back(t);
	}
	void Add_Tri(vec3 position1, vec3 position2, vec3 position3, vec3 n, Material m, mat4 trans) {
		position1 = vec3(trans * vec4(position1, 1.0f));
		position2 = vec3(trans * vec4(position2, 1.0f));
		position3 = vec3(trans * vec4(position3, 1.0f));
		n= normalize(transpose(inverse(mat3(trans))) * n);
		Triangle t(position1, position2, position3, n, m);
		
		Tri.push_back(t);
	}
	//将标准立方空间坐标转为实际空间坐标
	void View_Port() {
		for (auto& i : Tri) 
			for (auto& j : i.P) {
				j.position.x *= Width;
				j.position.y *= Height;
				j.position.z *= Standard_Z;
			}
	}
	void Print_Tri() {
		int num = 0;
		for (auto& i : Tri) {
			cout <<"tri"<<num<<":" << i.P[0].position.x << " " << i.P[0].position.y << " " << i.P[0].position.z << endl;
			cout << "tri" << num << ":" << i.P[1].position.x << " " << i.P[1].position.y << " " << i.P[1].position.z << endl;
			cout << "tri" <<num << ":"  <<i.P[2].position.x << " " << i.P[2].position.y << " " << i.P[2].position.z << endl;
			num++;
		}
	}
		
	
	
};

