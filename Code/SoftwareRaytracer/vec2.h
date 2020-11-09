#pragma once
#include "MathLib.h"

class vec2 final
{
public:
	vec2()
		:m_V{ 0, 0 }
	{}
	vec2(float x, float y)
		:m_V{ x, y }
	{}

	float x() const
	{
		return m_V[0];
	}
	float y() const
	{
		return m_V[1];
	}

	//Swivles
#pragma region Swivles
	vec2 xy() const
	{
		return vec2(m_V[0], m_V[1]);
	}
	vec2 yx() const
	{
		return vec2(m_V[1], m_V[0]);
	}
	vec2 xx() const
	{
		return vec2(m_V[0], m_V[0]);
	}
	vec2 yy() const
	{
		return vec2(m_V[1], m_V[1]);
	}
#pragma endregion

	//Operators
#pragma region Operators
	friend inline std::ostream& operator<<(std::ostream& out, const vec2& u)
	{
		return out << u[0] << ' ' << u[1];
	}

	inline float operator[](const int i) const
	{
		return m_V[i];
	}
	inline float& operator[](const int i)
	{
		return m_V[i];
	}

	inline vec2 operator-()
	{
		return vec2(-m_V[0], -m_V[1]);
	}

	inline vec2 operator-(const vec2& o) const
	{
		return vec2(m_V[0] - o[0], m_V[1] - o[1]);
	}
	inline vec2& operator-=(const vec2& o)
	{
		m_V[0] -= o[0];
		m_V[1] -= o[1];
		return *this;
	}
	inline vec2 operator+(const vec2& o) const
	{
		return vec2(m_V[0] + o[0], m_V[1] + o[1]);
	}
	inline vec2& operator+=(const vec2& o)
	{
		m_V[0] += o[0];
		m_V[1] += o[1];
		return *this;
	}

	inline vec2 operator/(const vec2& o) const
	{
		return vec2(m_V[0] / o[0], m_V[1] / o[1]);
	}
	inline vec2& operator/=(const vec2& o)
	{
		m_V[0] /= o[0];
		m_V[1] /= o[1];
		return *this;
	}
	inline vec2 operator*(const vec2& o) const
	{
		return vec2(m_V[0] * o[0], m_V[1] * o[1]);
	}
	inline vec2& operator*=(const vec2& o)
	{
		m_V[0] *= o[0];
		m_V[1] *= o[1];
		return *this;
	}

	friend inline vec2 operator-(const vec2& v, const float o)
	{
		return vec2(v[0] - o, v[1] - o);
	}
	friend inline vec2 operator-(const float o, const vec2& v)
	{
		return vec2(v[0] - o, v[1] - o);
	}
	friend inline vec2 operator+(const vec2& v, const float o)
	{
		return vec2(v[0] + o, v[1] + o);
	}
	friend inline vec2 operator+(const float o, const vec2& v)
	{
		return vec2(v[0] + o, v[1] + o);
	}


	friend inline vec2 operator*(const vec2& v, const float o)
	{
		return vec2(v[0] * o, v[1] * o);
	}
	friend inline vec2 operator*(const float o, const vec2& v)
	{
		return vec2(v[0] * o, v[1] * o);
	}
	friend inline vec2 operator/(const vec2& v, const float o)
	{
		return vec2(v[0] / o, v[1] / o);
	}
	friend inline vec2 operator/(const float o, const vec2& v)
	{
		return vec2(v[0] / o, v[1] / o);
	}
#pragma endregion

	//Math
#pragma region Math
	inline float Length() const
	{
		return sqrtf(m_V[0] * m_V[0] + m_V[1] * m_V[1]);
	}
	inline vec2 Unit()
	{
		return *this / Length();
	}

	inline float Dot(const vec2& o) const
	{
		return m_V[0] * o[0] + m_V[1] * o[1];
	}
	inline float Dot(const vec2& u, const vec2& o) const
	{
		return u[0] * o[0] + u[1] * o[1];
	}
	inline float Cross(const vec2& o) const
	{
		return float(m_V[0] * o[1] - m_V[1] * o[0]);
	}
	inline float Cross(const vec2& u, const vec2& o) const
	{
		return float(u[0] * o[1] - u[1] * o[0]);
	}
#pragma endregion

private:
	//Value
	float m_V[2];
};
