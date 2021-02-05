#include "Link.hpp"


Link::Link(Point* p1, Point* p2, double length)
{
    m_p1 = p1;
    m_p2 = p2;

    m_length = length;
    if (m_length <= 0)
        m_length = Vec(m_p1, m_p2).norme;

    m_broken = false;
}

void Link::update(double dt, double x, double y)
{
    double vx = m_p2->x - m_p1->x;
    double vy = m_p2->y - m_p1->y;

    double dist = sqrt(vx*vx+vy*vy)+0.0001;

    double f = (dist-m_length)/dist*0.5;

    m_p2->color = sf::Color::White;

    double coeff_mass_1 = m_p2->mass/(m_p1->mass+m_p2->mass);
    double coeff_mass_2 = m_p1->mass/(m_p1->mass+m_p2->mass);

    if (dist > m_length+3)
        m_broken = true;

    if (!m_p1->fixed)
    {
        m_p1->x += vx*(f)*coeff_mass_1;
        m_p1->y += vy*(f)*coeff_mass_1;
    }

    if (!m_p2->fixed)
    {
        m_p2->x -= vx*(f)*coeff_mass_2;
        m_p2->y -= vy*(f)*coeff_mass_2;
    }

    Vec v_mouse = Vec(m_p1->x-x, m_p1->y-y);
    v_mouse.normalize();
    double dist_mouse = v_mouse.norme;

    if (dist_mouse < 7)
    {
        /*double f_mouse = 5000;
        m_p1->ax -= f_mouse*v_mouse.x;
        m_p1->ay -= f_mouse*v_mouse.y;*/
        m_broken = true;
    }

}
