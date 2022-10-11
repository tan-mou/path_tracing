#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp> 
#include<glm/gtc/type_ptr.hpp>
#include<iostream>
#include<vector>
#include<random>
#include<time.h>
#include"Scene.hpp"
#include"svpng.inc"
#define PI 3.141596
#define Width 256
#define Height 192
#define Standard_Z 192
#define Spp 10000
#define Max 1e9
static default_random_engine  n(time(0));
static uniform_real_distribution<double> u(-1, 1);
static uniform_real_distribution<double>k(0, 2);
static uniform_real_distribution<double> r(0, 1);
const double Fov = 60;
const float P_RR = 0.8;
//define default information
const vec3 Blue(0.0f, 0.f, 1.0f);
const vec3 Red(1.f, 0.0f, 0.f);
const vec3 White(1.f, 1.f, 1.f);
const vec3 Gray(.8f, .8f, .6f);
const vec3 Gray2(.4, .4, .4);
const char* Diffuse = "Diffuse";
const char* Specular = "Specular";
//define standard room
const vec3 P1(0.0f, 0.0f, 0.0f);
const vec3 P2(1.0f, 0.0f, 0.0f);
const vec3 P3(1.0f, 1.0f, 0.0f);
const vec3 P4(0.0f, 1.0f, 0.0f);
const vec3 P5(0.0f, 0.0f, -1.0f);
const vec3 P6(1.0f, 0.0f, -1.0f);
const vec3 P7(1.0f, 1.0f, -1.0f);
const vec3 P8(0.0f, 1.0f, -1.0f);
const vec3 N1(0.0f, 1.0f, 0.0f);//down
const vec3 N2(0.0f, -1.0f, 0.0f);//up
const vec3 N3(1.0f, 0.0f, 0.0f);//left
const vec3 N4(-1.0f, 0.0f, 0.0f);//right
const vec3 N5(0.0f, 0.0f, 1.0f);//back
const vec3 N6(0.0f, 0.0f, -1.0f);//front
//define light area
const vec3 L1(0.3f, 0.99f, -0.3f);
const vec3 L2(0.7f, 0.99f, -0.3f);
const vec3 L3(0.7f, 0.99f, -0.7f);
const vec3 L4(0.3f, 0.99f, -0.7f);
const vec3 N7(0.0f, -1.0f, 0.0f);
//define eye position
const vec3 eye(0.5 * Width, 0.5 * Height, Height/2/tan(Fov/180*PI/2));
//define Material
Material M1(Diffuse,Blue,false);
Material M2(Diffuse, Red, false);
Material M3(Diffuse, Gray, false);
Material M4(Diffuse, White, true);
Material M5(Diffuse, White, false);
Material M6(Diffuse, Gray2, false);
Material M7(Specular, Gray2, false);
//define Triangle
const vec3 V1(0.5f, 0.2f, -0.2f);
const vec3 V2(0.7f, 0.2f, -0.5f);
const vec3 V3(0.3f, 0.2f, -0.5f);
const vec3 N8(0.0f, 1.0f, 0.0f);
//define funciton
void output_image(vector<vec3> src);
vec3 path_tracing(Scene& scene, Ray& ray, Point incidence);
Point intersection_scene(Scene& scene, Ray& ray);
Point intersection_tri(Triangle& triangle, Ray& ray);
glm::vec3 random_direction(vec3 normal);
glm::vec3 randomvec3();
int main(){
    cout << Height / 2 / tan(Fov / 180 * PI / 2) << endl;
    vector<vec3> image_src;
    vec3 image_color(0);
    vec3 med_color(0);
    Scene scene(Width, Height, Standard_Z, Fov);

    //light area
    scene.Add_Tri(L1, L2, L3, N7, M4);
    scene.Add_Tri(L1, L3, L4, N7, M4);
    //down
    scene.Add_Tri(P1, P2, P5, N1, M3);
    scene.Add_Tri(P2, P5, P6, N1, M3);
    //Up
    scene.Add_Tri(P3, P4, P8, N2, M3);
    scene.Add_Tri(P3, P7, P8, N2, M3);
    //left
    scene.Add_Tri(P1, P4, P5, N3, M2);
    scene.Add_Tri(P5, P8, P4, N3, M2);
    //right
    scene.Add_Tri(P2, P3, P6, N4, M1);
    scene.Add_Tri(P6, P7, P3, N4, M1);
    //back
    scene.Add_Tri(P5, P6, P7, N5, M3);
    scene.Add_Tri(P7, P8, P5, N5, M3);
    mat4 trans(1.0f);
    trans = glm::translate(trans, vec3(0.3f , 0.0F, -0.4f ));
    trans = glm::rotate(trans, radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    trans = glm::scale(trans, vec3(0.3f, 0.6f, 0.3f));
    //down
    scene.Add_Tri(P1, P2, P5, -N1, M7,trans);
    scene.Add_Tri(P2, P5, P6, -N1, M7,trans);
    //Up
    scene.Add_Tri(P3, P4, P8, -N2, M7,trans);
    scene.Add_Tri(P3, P7, P8, -N2, M7,trans);
    //left
    scene.Add_Tri(P1, P4, P5, -N3, M7,trans);
    scene.Add_Tri(P5, P8, P4, -N3, M7,trans);
    //right
    scene.Add_Tri(P2, P3, P6, -N4, M7,trans);
    scene.Add_Tri(P6, P7, P3, -N4, M7,trans);
    //back
    scene.Add_Tri(P5, P6, P7, -N5, M7,trans);
    scene.Add_Tri(P7, P8, P5, -N5, M7,trans);
    //front
    scene.Add_Tri(P1, P2, P3, -N6, M7, trans);
    scene.Add_Tri(P3, P4, P1, -N6, M7, trans);

    //obejct2 
    trans = mat4(1.0f);
    trans = glm::translate(trans, vec3(0.6f, 0.0F, -0.3f));
    trans = glm::rotate(trans, radians(-30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    trans = glm::scale(trans, vec3(0.2f, 0.2f, 0.2f));
    //down
    scene.Add_Tri(P1, P2, P5, -N1, M6, trans);
    scene.Add_Tri(P2, P5, P6, -N1, M6, trans);
    //Up
    scene.Add_Tri(P3, P4, P8, -N2, M6, trans);
    scene.Add_Tri(P3, P7, P8, -N2, M6, trans);
    //left
    scene.Add_Tri(P1, P4, P5, -N3, M6, trans);
    scene.Add_Tri(P5, P8, P4, -N3, M6, trans);
    //right
    scene.Add_Tri(P2, P3, P6, -N4, M6, trans);
    scene.Add_Tri(P6, P7, P3, -N4, M6, trans);
    //back
    scene.Add_Tri(P5, P6, P7, -N5, M6, trans);
    scene.Add_Tri(P7, P8, P5, -N5, M6, trans);
    //front
    scene.Add_Tri(P1, P2, P3, -N6, M6, trans);
    scene.Add_Tri(P3, P4, P1, -N6, M6, trans);
    scene.View_Port();//trans to world coordinate
    scene.Print_Tri();
    //Pixel data
    Ray ray;
    Point P;
    Point P2;
    vec3 dir(0);
    vec3 pos(0);
    vec3 ref(0);
    for (float j = Height-1; j >= 0; j--)
        for (float i = 0; i < Width; i++) {
            for (int k = 0; k < Spp; k++) {//Spp
                //path tracing in here
                pos = vec3(i, j, 0.0f);
                dir = normalize(pos - eye);
                ray.direction = dir;
                ray.position = pos;
                //emit light
                P = intersection_scene(scene, ray);
                if (!P.t) { med_color += vec3(0.0); }//don't hit obejct
                else {
                    if (P.material.type == "Specular") {//Specular
                        ref = reflect(dir, P.normal);
                        ray.direction = ref;
                        ray.position = P.position;
                        P2 = intersection_scene(scene, ray);
                        if (!P2.t) { med_color += vec3(0.0); }//don't hit obejct
                        else {
                            if (P2.material.emit) { med_color += vec3(1.0f); }//hit light
                            else {
                                ray.direction = -ray.direction;
                                med_color += path_tracing(scene, ray, P2);

                            }
                        }
                        
                    }
                    else {//diffuse
                        if (P.material.emit) { med_color += vec3(1.0f); }//hit light
                        else {
                            ray.direction = -ray.direction;
                            med_color += path_tracing(scene, ray, P);

                        }
                    }
                    
                    
                }
                
            }
            image_color =med_color/vec3(Spp) ;
            image_src.push_back(image_color);
            med_color = vec3(0);
        }
        
    output_image(image_src);
}
//path tracing
vec3 path_tracing(Scene& scene, Ray& ray, Point incidence) {
    
    if (r(n) > P_RR) {//russian roulette
        return vec3(0);
    }
    else {
        Point P;
        vec3 Wi = random_direction(incidence.normal);
        vec3 radiance(0);
        Ray exit(Wi, incidence.position);
        P = intersection_scene(scene, exit);
        if (!P.t) { return vec3(0); }//don't hit object return 0
        else {
            float Cosine = dot(-Wi, P.normal);
            if (Cosine < 0) Cosine = 0;
            if (P.material.emit) {//when hit ray
                
                return vec3(1.0f) * incidence.material.Kd * vec3(2*PI) * Cosine /P_RR;
            }
            else {//hit diffuse obejct
                exit.direction = -exit.direction;
                return path_tracing(scene,exit,P) * incidence.material.Kd * vec3(2) * Cosine / P_RR;
            }
        }
    }
    



}
//intersection
Point intersection_scene(Scene& scene, Ray& ray) {
    Point p;
    p.t = 0;
    Point med_p;
    float Med_t=Max;
    for (auto i : scene.Tri) {//traverse triangle
        med_p = intersection_tri(i, ray);
        if (med_p.t<=0.005) {}//no triangle intersect  to  ray 
        else {//is it min?
            if (med_p.t < Med_t) {
                p = med_p;
                Med_t = med_p.t;
            }
        }
    }
    return p;
}
Point intersection_tri(Triangle& triangle, Ray& ray) {
    glm::vec3 O = ray.position;
    glm::vec3 S = ray.position - triangle.P[0].position;
    glm::vec3 D = ray.direction;
    glm::vec3 E1 = triangle.P[1].position - triangle.P[0].position;
    glm::vec3 E2 = triangle.P[2].position - triangle.P[0].position;
    glm::vec3 S1 = glm::cross(D, E2);
    glm::vec3 S2 = glm::cross(S, E1);
    //Cramer's Rule
    float t = glm::dot(S2, E2) / glm::dot(S1, E1);
    float u = glm::dot(S1, S) / glm::dot(S1, E1);
    float v = glm::dot(S2, D) / glm::dot(S1, E1);
    if (u >=0 && v >= 0 && u + v <= 1) {
        Point point(O + t * D, triangle.normal, triangle.material);
        point.t = t;
        return point;
    }
    else {
        Point point;
        point.t = 0;
        return point;
    }
}
//output image01 
void output_image(vector<vec3> src) {
    unsigned char image[Width * Height * 3], * p = image;
    unsigned x, y;
    auto s = src.begin();
    FILE* fp = fopen("image.png", "wb");
    for (y = Height; y > 0; y--) {

        for (x = 0; x < Width; x++) {

            *p++ = (unsigned char)((*s).x * 255);      /* R */
 
            *p++ = (unsigned char)((*s).y * 255);    /* G */

            *p++ = (unsigned char)((*s).z * 255);    /* B */
            //if ((*s).radiance.x == 0.5f)
            //    cout << "image:" << (*s).position.x << " " << (*s).position.y << " " << (*s).position.z << endl;
            ++s;
        }
    }

    svpng(fp, Width, Height, image, 0);
    fclose(fp);
}
glm::vec3 randomvec3() {
    glm::vec3 r(0);
    while (true) {
        r = glm::vec3(u(n), u(n), u(n));
        if (glm::length(r) >= 1) {

            continue;
        }

        return glm::normalize(r);
    }

}
//create random direciton
glm::vec3 random_direction(vec3 normal) {
    return glm::normalize(normal + randomvec3());
}