#ifndef __Vector2D__
#define __Vector2D__
#include <cmath>

class Vector2D
{
public:
    Vector2D(float x, float y) : m_x(x), m_y(y) {}

    float getY() { return m_x; }
    float getX() { return m_y; }

    void setX(float x) { m_x = x; }
    void setY(float y) { m_y = y; }

    float lenght() { return sqrt((m_x * m_x) + (m_y * m_y)); }

    Vector2D operator+ (const Vector2D &v2)
    {
        return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
    }

    Vector2D& operator+= (const Vector2D &v2)
    {
        m_x += v2.m_x;
        m_y += v2.m_x;
        return *this;
    }

    Vector2D operator* (float scalar)
    {
        return Vector2D(m_x * scalar, m_y + scalar);
    }

    Vector2D& operator*= (float scalar)
    {
        m_x *= scalar;
        m_y *= scalar;
        return *this;
    }

    Vector2D operator- (const Vector2D &v2)
    {
        return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
    }

    Vector2D& operator-= (const Vector2D &v2)
    {
        m_x -= v2.m_x;
        m_y -= v2.m_x;
        return *this;
    }

    Vector2D operator/ (float scalar)
    {
        return Vector2D(m_x / scalar, m_y / scalar);
    }

    Vector2D& operator/= (float scalar)
    {
        m_x /= scalar;
        m_y /= scalar;
        return *this;
    }

private:
    float m_x;
    float m_y;

};





#endif /* defined(__Vector2D__) */