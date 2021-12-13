#ifndef CUSTOMQTOPENGLWIDGET_H
#define CUSTOMQTOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <cmath>
#include <iostream>
#include <QRandomGenerator>
#include <limits>

#include "prism.h"
#include "include/glm/mat4x4.hpp"
#include "include/glm/vec4.hpp"


#define PI 3.14159265

class customqtopenglwidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    customqtopenglwidget(QWidget* parent = nullptr)
    {
        Q_UNUSED(parent);
    }
    Prism prism1 = Prism(3, 200, 400, 200, 0, 20, 0);
    Prism prism2 = Prism(3, 20, 40, 20, 0, 20, 10);
public slots:
    void repaint_par();
    void repaint_per();
protected:
    void initializeGL() override
    {
        if(this->objectName() == "mainOpenGLWidget")
        {
            glClearColor(1,1,1,1);
            expand_color(1, 20);
            this->set_view();
        }
        else
        {
            glClearColor(1,1,1,1);
            expand_color(2, 20);
            this->perspective();
        }
    }
    void paintGL() override
    {
        if(this->objectName() == "mainOpenGLWidget")
        {
            int n = prism1.get_n();
            for (int i = 0; i < 860; i++)
            {
                for (int j = 0; j < 860; j++)
                {
                    zbuffer1[i][j] = INT_MAX;
                }
            }
            for (int i = 0; i < n - 1; i++)
            {
                draw_line(prism1.point_at_x(i), prism1.point_at_y(i), prism1.point_at_z(i), prism1.point_at_x(i + 1), prism1.point_at_y(i + 1), prism1.point_at_z(i + 1), 0.0f, 0.0f, 0.0f);
            }
            draw_line(prism1.point_at_x(n - 1), prism1.point_at_y(n - 1), prism1.point_at_z(n - 1), prism1.point_at_x(0), prism1.point_at_y(0), prism1.point_at_z(0), 0.0f, 0.0f, 0.0f);
            for (int i = n; i < 2 * n - 1; i++)
            {
                draw_line(prism1.point_at_x(i), prism1.point_at_y(i), prism1.point_at_z(i), prism1.point_at_x(i + 1), prism1.point_at_y(i + 1), prism1.point_at_z(i + 1), 0.0f, 0.0f, 0.0f);
            }
            draw_line(prism1.point_at_x(2 * n - 1), prism1.point_at_y(2 * n - 1), prism1.point_at_z(2 * n - 1), prism1.point_at_x(n), prism1.point_at_y(n), prism1.point_at_z(n), 0.0f, 0.0f, 0.0f);
            for (int i = 0; i < n; i++)
            {
               draw_line(prism1.point_at_x(i), prism1.point_at_y(i), prism1.point_at_z(i), prism1.point_at_x(i + n), prism1.point_at_y(i + n), prism1.point_at_z(i + n), 0.0f, 0.0f, 0.0f);
            }
            int c = 0;
            for (int i = 1; i < n - 1; i++)
            {
                fill_triangle(prism1.point_at_x(0), prism1.point_at_y(0), prism1.point_at_z(0),
                              prism1.point_at_x(i), prism1.point_at_y(i), prism1.point_at_z(i),
                              prism1.point_at_x(i + 1), prism1.point_at_y(i + 1), prism1.point_at_z(i + 1),
                              color_array1.at(c).x, color_array1.at(c).y, color_array1.at(c).z);
                c++;
            }

            for (int i = n + 1; i < 2*n - 1; i++)
            {
                fill_triangle(prism1.point_at_x(n), prism1.point_at_y(n), prism1.point_at_z(n),
                              prism1.point_at_x(i), prism1.point_at_y(i), prism1.point_at_z(i),
                              prism1.point_at_x(i + 1), prism1.point_at_y(i + 1), prism1.point_at_z(i + 1),
                              color_array1.at(c).x, color_array1.at(c).y, color_array1.at(c).z);
                c++;
            } //up and down


            for (int i = 0; i < n - 1; i++)
            {
                fill_triangle(prism1.point_at_x(i), prism1.point_at_y(i), prism1.point_at_z(i),
                              prism1.point_at_x(i + 1), prism1.point_at_y(i + 1), prism1.point_at_z(i + 1),
                              prism1.point_at_x(i + n), prism1.point_at_y(i + n), prism1.point_at_z(i + n),
                              color_array1.at(c).x, color_array1.at(c).y, color_array1.at(c).z);
                c++;
            }
            fill_triangle(prism1.point_at_x(n - 1), prism1.point_at_y(n - 1), prism1.point_at_z(n - 1),
                          prism1.point_at_x(0), prism1.point_at_y(0), prism1.point_at_z(0),
                          prism1.point_at_x(2 * n - 1), prism1.point_at_y(2 * n - 1), prism1.point_at_z(2 * n - 1),
                          color_array1.at(c).x, color_array1.at(c).y, color_array1.at(c).z);
            c++;
            //half of walls

            for (int i = 0; i < n - 1; i++)
            {
                fill_triangle(prism1.point_at_x(i + n + 1), prism1.point_at_y(i + n + 1), prism1.point_at_z(i + n + 1),
                              prism1.point_at_x(i + 1), prism1.point_at_y(i + 1), prism1.point_at_z(i + 1),
                              prism1.point_at_x(i + n), prism1.point_at_y(i + n), prism1.point_at_z(i + n),
                              color_array1.at(c).x, color_array1.at(c).y, color_array1.at(c).z);
                c++;
            }
            fill_triangle(prism1.point_at_x(2 * n - 1), prism1.point_at_y(2 * n - 1), prism1.point_at_z(2 * n - 1),
                          prism1.point_at_x(0), prism1.point_at_y(0), prism1.point_at_z(0),
                          prism1.point_at_x(n), prism1.point_at_y(n), prism1.point_at_z(n),
                          color_array1.at(c).x, color_array1.at(c).y, color_array1.at(c).z);

        }
        else
        {
            int n = prism2.get_n();
            for (int i = 0; i < 860; i++)
            {
                for (int j = 0; j < 860; j++)
                {
                    zbuffer2[i][j] = INT_MAX;
                }
            }
            for (int i = 0; i < n - 1; i++)
            {
                draw_line(prism2.point_at_x(i), prism2.point_at_y(i), prism2.point_at_z(i), prism2.point_at_x(i + 1), prism2.point_at_y(i + 1), prism2.point_at_z(i + 1), 0.0f, 0.0f, 0.0f);
            }
            draw_line(prism2.point_at_x(n - 1), prism2.point_at_y(n - 1), prism2.point_at_z(n - 1), prism2.point_at_x(0), prism2.point_at_y(0), prism2.point_at_z(0), 0.0f, 0.0f, 0.0f);
            for (int i = n; i < 2 * n - 1; i++)
            {
                draw_line(prism2.point_at_x(i), prism2.point_at_y(i), prism2.point_at_z(i), prism2.point_at_x(i + 1), prism2.point_at_y(i + 1), prism2.point_at_z(i + 1), 0.0f, 0.0f, 0.0f);
            }
            draw_line(prism2.point_at_x(2 * n - 1), prism2.point_at_y(2 * n - 1), prism2.point_at_z(2 * n - 1), prism2.point_at_x(n), prism2.point_at_y(n), prism2.point_at_z(n), 0.0f, 0.0f, 0.0f);
            for (int i = 0; i < n; i++)
            {
               draw_line(prism2.point_at_x(i), prism2.point_at_y(i), prism2.point_at_z(i), prism2.point_at_x(i + n), prism2.point_at_y(i + n), prism2.point_at_z(i + n), 0.0f, 0.0f, 0.0f);
            }
            int c = 0;
            for (int i = 1; i < n - 1; i++)
            {
                fill_triangle(prism2.point_at_x(0), prism2.point_at_y(0), prism2.point_at_z(0),
                              prism2.point_at_x(i), prism2.point_at_y(i), prism2.point_at_z(i),
                              prism2.point_at_x(i + 1), prism2.point_at_y(i + 1), prism2.point_at_z(i + 1),
                              color_array2.at(c).x, color_array2.at(c).y, color_array2.at(c).z);
                c++;
            }

            for (int i = n + 1; i < 2*n - 1; i++)
            {
                fill_triangle(prism2.point_at_x(n), prism2.point_at_y(n), prism2.point_at_z(n),
                              prism2.point_at_x(i), prism2.point_at_y(i), prism2.point_at_z(i),
                              prism2.point_at_x(i + 1), prism2.point_at_y(i + 1), prism2.point_at_z(i + 1),
                              color_array2.at(c).x, color_array2.at(c).y, color_array2.at(c).z);
                c++;
            } //up and down


            for (int i = 0; i < n - 1; i++)
            {
                fill_triangle(prism2.point_at_x(i), prism2.point_at_y(i), prism2.point_at_z(i),
                              prism2.point_at_x(i + 1), prism2.point_at_y(i + 1), prism2.point_at_z(i + 1),
                              prism2.point_at_x(i + n), prism2.point_at_y(i + n), prism2.point_at_z(i + n),
                              color_array2.at(c).x, color_array2.at(c).y, color_array2.at(c).z);
                c++;
            }
            fill_triangle(prism2.point_at_x(n - 1), prism2.point_at_y(n - 1), prism2.point_at_z(n - 1),
                          prism2.point_at_x(0), prism2.point_at_y(0), prism2.point_at_z(0),
                          prism2.point_at_x(2 * n - 1), prism2.point_at_y(2 * n - 1), prism2.point_at_z(2 * n - 1),
                          color_array2.at(c).x, color_array2.at(c).y, color_array2.at(c).z);
            c++;
            //half of walls

            for (int i = 0; i < n - 1; i++)
            {
                fill_triangle(prism2.point_at_x(i + n + 1), prism2.point_at_y(i + n + 1), prism2.point_at_z(i + n + 1),
                              prism2.point_at_x(i + 1), prism2.point_at_y(i + 1), prism2.point_at_z(i + 1),
                              prism2.point_at_x(i + n), prism2.point_at_y(i + n), prism2.point_at_z(i + n),
                              color_array2.at(c).x, color_array2.at(c).y, color_array2.at(c).z);
                c++;
            }
            fill_triangle(prism2.point_at_x(2 * n - 1), prism2.point_at_y(2 * n - 1), prism2.point_at_z(2 * n - 1),
                          prism2.point_at_x(0), prism2.point_at_y(0), prism2.point_at_z(0),
                          prism2.point_at_x(n), prism2.point_at_y(n), prism2.point_at_z(n),
                          color_array2.at(c).x, color_array2.at(c).y, color_array2.at(c).z);
        }
    }

private:
    QVector<glm::vec3> color_array1;
    QVector<glm::vec3> color_array2;
    int zbuffer1[860][860];
    int zbuffer2[860][860];
    glm::mat4x4 turn_phi_z;
    glm::mat4x4 turn_90_phi_y;
    glm::mat4x4 move;
    glm::mat4x4 switch_axis;
    glm::mat4x4 init_turn_phi_z(float phi);
    glm::mat4x4 init_turn_phi_z_val(float cosine, float sine);
    glm::mat4x4 init_turn_90_phi_y(float phi);
    glm::mat4x4 init_turn_90_phi_y_val(float cosine, float sine);
    glm::mat4x4 init_move(float x, float y, float z);
    glm::mat4x4 init_switch_axis();
    void set_view();
    void perspective();
    void fill_triangle(GLint ax, GLint ay, GLint az, GLint bx, GLint by, GLint bz, GLint cx, GLint cy, GLint cz, GLfloat red, GLfloat green, GLfloat blue);
    void expand_color(int mode, int new_n);
    void draw_at(int pixel_x, int pixel_y, int pixel_z, GLfloat red, GLfloat green, GLfloat blue);
    void draw_line (int x1, int y1, int z1, const int x2, const int y2, const int z2, GLfloat red, GLfloat green, GLfloat blue);
};

#endif // CUSTOMQTOPENGLWIDGET_H
