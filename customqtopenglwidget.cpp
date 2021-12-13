#include <customqtopenglwidget.h>
#include <cmath>

void swap(float *a, float *b)
{
    *a = *a + *b - (*b = *a);
}
void swap(int *a, int *b)
{
    (*a) = (*a) ^ (*b);
    (*b) = (*b) ^ (*a);
    (*a) = (*a) ^ (*b);
}
glm::mat4x4 customqtopenglwidget::init_turn_phi_z(float phi)
{
    return glm::mat4x4(cos(phi * PI / 180.0), sin(phi * PI / 180.0), 0, 0,
                       -1 * sin(phi * PI / 180.0), cos(phi * PI / 180.0), 0, 0,
                       0, 0, 1, 0,
                       0, 0, 0, 1);
}
glm::mat4x4 customqtopenglwidget::init_turn_phi_z_val(float cosine, float sine)
{
    return glm::mat4x4(cosine, sine, 0, 0,
                       -1 * sine, cosine, 0, 0,
                       0, 0, 1, 0,
                       0, 0, 0, 1);
}
glm::mat4x4 customqtopenglwidget::init_turn_90_phi_y(float phi)
{
    return glm::mat4x4(sin(phi * PI / 180.0), 0, -1 * cos(phi * PI / 180.0), 0,
                       0, 1, 0, 0,
                       cos(phi * PI / 180.0), 0, sin(phi * PI / 180.0), 0,
                       0, 0, 0, 1);
}
glm::mat4x4 customqtopenglwidget::init_turn_90_phi_y_val(float cosine, float sine)
{
    return glm::mat4x4(sine, 0, -1 * cosine, 0,
                       0, 1, 0, 0,
                       cosine, 0, sine, 0,
                       0, 0, 0, 1);
}
glm::mat4x4 customqtopenglwidget::init_move(float x, float y, float z)
{
    return glm::mat4x4(1, 0, 0, x,
                       0, 1, 0, y,
                       0, 0, 1, z,
                       0, 0, 0, 1);
}
glm::mat4x4 customqtopenglwidget::init_switch_axis()
{
    return glm::mat4x4(0, 1, 0, 0,
                       0, 0, 1, 0,
                      -1, 0, 0, 0,
                       0, 0, 0, 1);
}
void customqtopenglwidget::set_view()
{
    float ex, ey, ez, modv, mode;
    ex = prism1.get_ex();
    ey = prism1.get_ey();
    ez = prism1.get_ez();
    modv = sqrt(ex * ex + ey * ey);
    mode = sqrt(ex * ex + ey * ey + ez * ez);
    turn_phi_z = init_turn_phi_z_val((ex / modv), (ey / modv));
    turn_90_phi_y = init_turn_90_phi_y_val((ez / mode), (modv / mode));
    move = init_move(-1 * mode, 0, 0);
    switch_axis = init_switch_axis();
    for(int i = 0; i < prism1.get_size(); i++)
    {
        prism1.transform_vertex(turn_phi_z, turn_90_phi_y, move, switch_axis, i);
    }
}
void customqtopenglwidget::perspective()
{
    float ex, ey, ez, modv, mode, d;
    ex = prism2.get_ex();
    ey = prism2.get_ey();
    ez = prism2.get_ez();
    d = prism2.get_d();
    modv = sqrt(ex * ex + ey * ey);
    mode = sqrt(ex * ex + ey * ey + ez * ez);
    turn_phi_z = init_turn_phi_z_val((ex / modv), (ey / modv));
    turn_90_phi_y = init_turn_90_phi_y_val((ez / mode), (modv / mode));
    move = init_move(-1 * mode, 0, 0);
    switch_axis = init_switch_axis();
    for(int i = 0; i < prism2.get_size(); i++)
    {
        prism2.transform_vertex(turn_phi_z, turn_90_phi_y, move, switch_axis, i);
        prism2.transform_vertex(d, i);
    }
}
void customqtopenglwidget::repaint_par()
{
    expand_color(1, 4 * (prism1.get_n() - 1));
    set_view();
    update();
}
void customqtopenglwidget::repaint_per()
{
    expand_color(2, 4 * (prism2.get_n() - 1));
    perspective();
    update();
}
void customqtopenglwidget::fill_triangle(GLint ax, GLint ay, GLint az, GLint bx, GLint by, GLint bz, GLint cx, GLint cy, GLint cz, GLfloat red, GLfloat green, GLfloat blue)
{
    if (ay < by)
    {
        swap(&ay, &by);
        swap(&ax, &bx);
    }
    if (ay < cy)
    {
        swap(&ay, &cy);
        swap(&ax, &cx);
    }
    if (by < cy)
    {
        swap(&by, &cy);
        swap(&bx, &cx);
    }
    int sy = ay;
    do
    {
        if ((cy <= sy) && (sy <= by) && (cy != by) && (cy != ay))   //line intersects with BC and AC
        {
            int bcx = bx + ((sy - by)*(cx - bx)/(cy - by));
            int acx = ax + ((sy - ay)*(cx - ax)/(cy - ay));
            int bcz = bz + ((sy - by)*(cz - bz)/(cy - by));
            int acz = az + ((sy - ay)*(cz - az)/(cy - ay));
            draw_line(acx, sy, acz, bcx, sy, bcz, red, green, blue);


        }
        else        //line intersects with AB and AC
        {
            if ((by != ay) && (cy != ay))
            {
                int abx = ax + ((sy - ay)*(bx - ax)/(by - ay));
                int acx = ax + ((sy - ay)*(cx - ax)/(cy - ay));
                int abz = az + ((sy - ay)*(bz - az)/(by - ay));
                int acz = az + ((sy - ay)*(cz - az)/(cy - ay));
                draw_line(acx, sy, acz, abx, sy, abz, red, green, blue);
            }
        }
        sy -= 1;
    }
    while (sy >= cy);
}
void customqtopenglwidget::expand_color(int mode, int new_n)
{
    if (mode == 1)
    {
        if (color_array1.size() >= new_n)
        {
            return;
        }
        else
        {
            do
            {
            quint32 r = QRandomGenerator::global()->bounded(100);
            quint32 g = QRandomGenerator::global()->bounded(100);
            quint32 b = QRandomGenerator::global()->bounded(100);
            color_array1.append(glm::vec3(r / 100.0, g / 100.0, b / 100.0));
            }
            while (color_array1.size() != new_n);
        }
    }
    else
    {
        if (color_array2.size() >= new_n)
        {
            return;
        }
        else
        {
            do
            {
            quint32 r = QRandomGenerator::global()->bounded(100);
            quint32 g = QRandomGenerator::global()->bounded(100);
            quint32 b = QRandomGenerator::global()->bounded(100);
            color_array2.append(glm::vec3(r / 100.0, g / 100.0, b / 100.0));
            }
            while (color_array2.size() != new_n);
        }
    }
}
void customqtopenglwidget::draw_at(int pixel_x, int pixel_y, int pixel_z, GLfloat red, GLfloat green, GLfloat blue)
{
    if (pixel_x < -430 || pixel_y < -430)
        return;
    float real_x = pixel_x / 430.0;
    float real_y = pixel_y / 430.0;
    if (this->objectName() == "mainOpenGLWidget")
    {
        if (pixel_z < zbuffer1[pixel_x + 430][pixel_y + 430])
        {
            zbuffer1[pixel_x + 430][pixel_y + 430] = pixel_z;
            glBegin(GL_POINTS);
            glColor3f(red, green, blue);
            glVertex2f(real_x, real_y);
            glEnd();
        }
    }
    else
    {
        if (pixel_z < zbuffer2[pixel_x + 430][pixel_y + 430])
        {
            zbuffer2[pixel_x + 430][pixel_y + 430] = pixel_z;
            glBegin(GL_POINTS);
            glColor3f(red, green, blue);
            glVertex2f(real_x, real_y);
            glEnd();
        }
    }
}
void customqtopenglwidget::draw_line(int x1, int y1, int z1, int x2, int y2, int z2, GLfloat red, GLfloat green, GLfloat blue)
{
    int i, dx, dy, dz, l, m, n, x_inc, y_inc, z_inc, err_1, err_2, dx2, dy2, dz2;
    int point[3];
    point[0] = x1;
    point[1] = y1;
    point[2] = z1;
    dx = x2 - x1;
    dy = y2 - y1;
    dz = z2 - z1;
    x_inc = (dx < 0) ? -1 : 1;
    l = abs(dx);
    y_inc = (dy < 0) ? -1 : 1;
    m = abs(dy);
    z_inc = (dz < 0) ? -1 : 1;
    n = abs(dz);
    dx2 = l << 1;
    dy2 = m << 1;
    dz2 = n << 1;

    if ((l >= m) && (l >= n))
    {
        err_1 = dy2 - l;
        err_2 = dz2 - l;
        for (i = 0; i < l; i++)
        {
            draw_at(point[0], point[1], point[2], red, green, blue);
            if (err_1 > 0)
            {
                point[1] += y_inc;
                err_1 -= dx2;
            }
            if (err_2 > 0)
            {
                point[2] += z_inc;
                err_2 -= dx2;
            }
            err_1 += dy2;
            err_2 += dz2;
            point[0] += x_inc;
        }
    } else if ((m >= l) && (m >= n))
    {
        err_1 = dx2 - m;
        err_2 = dz2 - m;
        for (i = 0; i < m; i++)
        {
            draw_at(point[0], point[1], point[2], red, green, blue);
            if (err_1 > 0)
            {
                point[0] += x_inc;
                err_1 -= dy2;
            }
            if (err_2 > 0)
            {
                point[2] += z_inc;
                err_2 -= dy2;
            }
            err_1 += dx2;
            err_2 += dz2;
            point[1] += y_inc;
        }
    }
    else
    {
        err_1 = dy2 - n;
        err_2 = dx2 - n;
        for (i = 0; i < n; i++)
        {
            draw_at(point[0], point[1], point[2], red, green, blue);
            if (err_1 > 0)
            {
                point[1] += y_inc;
                err_1 -= dz2;
            }
            if (err_2 > 0)
            {
                point[0] += x_inc;
                err_2 -= dz2;
            }
            err_1 += dy2;
            err_2 += dx2;
            point[2] += z_inc;
        }
    }
    draw_at(point[0], point[1], point[2], red, green, blue);
}

