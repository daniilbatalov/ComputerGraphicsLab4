#include "prism.h"
Prism::Prism()
{

}
Prism::Prism(int n, int r, int h, int ex, int ey, int ez, int d)
{
    p_n = n;
    p_r = r;
    p_h = h;
    p_ex = ex;
    p_ey = ey;
    p_ez = ez;
    p_d = d;
    init_points();
}
void Prism::init_points()
{
    float phi = 360.0 / p_n;
    for (int i = 0; i < p_n; i++)
    {
        points.append(glm::vec4((int)(p_r * cos(i * phi * PI / 180.0)), (int)(p_r * sin(i * phi * PI / 180.0)), 0, 1));
    }
    for (int i = 0; i < p_n; i++)
    {
        points.append(glm::vec4((int)(p_r * cos(i * phi * PI / 180.0)), (int)(p_r * sin(i * phi * PI / 180.0)), p_h, 1));
    }
}
int Prism::get_n()
{
    return p_n;
}
int Prism::get_ex()
{
    return p_ex;
}
int Prism::get_ey()
{
    return p_ey;
}
int Prism::get_ez()
{
    return p_ez;
}
int Prism::get_d()
{
    return p_d;
}
int Prism::get_size()
{
    return points.size();
}
int Prism::point_at_x(int i)
{
    return points.at(i).x;
}
int Prism::point_at_y(int i)
{
    return points.at(i).y;
}
int Prism::point_at_z(int i)
{
    return points.at(i).z;
}

void Prism::transform_vertex(glm::mat4x4 matrix1, glm::mat4x4 matrix2, glm::mat4x4 matrix3, int number)
{
    points[number] = points.at(number) * matrix1 * matrix2 * matrix3;
    points[number].x = (int)points[number].x;
    points[number].y = (int)points[number].y;
    points[number].z = (int)points[number].z;
    points[number].w = (int)points[number].w;
}
void Prism::transform_vertex(glm::mat4x4 matrix1, glm::mat4x4 matrix2, glm::mat4x4 matrix3, glm::mat4x4 matrix4, int number)
{
    points[number] = points.at(number) * matrix1 * matrix2 * matrix3 * matrix4;
    points[number].x = (int)points[number].x;
    points[number].y = (int)points[number].y;
    points[number].z = (int)points[number].z;
    points[number].w = (int)points[number].w;
}
void Prism::transform_vertex(float d, int number)
{
    points[number].x = d * points.at(number).x / points.at(number).z;
    points[number].y = d * points.at(number).y / points.at(number).z;
    points[number].x = (int)points[number].x;
    points[number].y = (int)points[number].y;
    points[number].z = (int)points[number].z;
    points[number].w = (int)points[number].w;
}
void Prism::update_prism()
{
    points.clear();
    init_points();
}
void Prism::on_n_changed(int new_n)
{
    p_n = new_n;
    update_prism();
    emit prism_updated();
}
void Prism::on_r_changed(int new_r)
{
    p_r = new_r;
    update_prism();
    emit prism_updated();
}
void Prism::on_h_changed(int new_h)
{
    p_h = new_h;
    update_prism();
    emit prism_updated();
}
void Prism::on_ex_changed(int new_ex)
{
    p_ex = new_ex;
    update_prism();
    emit prism_updated();
}
void Prism::on_ey_changed(int new_ey)
{
    p_ey = new_ey;
    update_prism();
    emit prism_updated();
}
void Prism::on_ez_changed(int new_ez)
{
    p_ez = new_ez;
    update_prism();
    emit prism_updated();
}
void Prism::on_d_changed(int new_d)
{
    p_d = new_d;
    update_prism();
    emit prism_updated();
}
