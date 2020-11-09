#pragma once
#include "MathLib.h"

class vec3 final
{
public:
	vec3()
		:m_V{ 0, 0, 0 }
	{}
	vec3(float x, float y, float z)
		:m_V{ x, y, z }
	{}

	float x() const
	{ 
		return m_V[0]; 
	}
	float y() const
	{ 
		return m_V[1]; 
	}
	float z() const
	{ 
		return m_V[2]; 
	}
	float r() const
	{
		return m_V[0];
	}
	float g() const
	{
		return m_V[1];
	}
	float b() const
	{
		return m_V[2];
	}

	//Swivles
#pragma region Swivles
	vec2 xy() const
	{
		return vec2(m_V[0], m_V[1]);
	}
	vec2 xx() const
	{
		return vec2(m_V[0], m_V[0]);
	}
	vec2 xz() const
	{
		return vec2(m_V[0], m_V[2]);
	}
	vec3 xyz() const
	{
		return vec3(m_V[0], m_V[1], m_V[2]);
	}
	vec3 xzy() const
	{
		return vec3(m_V[0], m_V[2], m_V[1]);
	}
	vec3 xyy() const
	{
		return vec3(m_V[0], m_V[1], m_V[1]);
	}
	vec3 xzz() const
	{
		return vec3(m_V[0], m_V[2], m_V[2]);
	}
	vec3 xxy() const
	{
		return vec3(m_V[0], m_V[0], m_V[1]);
	}
	vec3 xxz() const
	{
		return vec3(m_V[0], m_V[0], m_V[2]);
	}
	vec3 xxx() const
	{
		return vec3(m_V[0], m_V[0], m_V[0]);
	}
	vec3 xyx() const
	{
		return vec3(m_V[0], m_V[1], m_V[0]);
	}
	vec3 xzx() const
	{
		return vec3(m_V[0], m_V[2], m_V[0]);
	}

	vec2 yx() const
	{
		return vec2(m_V[1], m_V[2]);
	}
	vec2 yy() const
	{
		return vec2(m_V[1], m_V[1]);
	}
	vec2 yz() const
	{
		return vec2(m_V[1], m_V[2]);
	}
	vec3 yxz() const
	{
		return vec3(m_V[1], m_V[0], m_V[2]);
	}
	vec3 yzx() const
	{
		return vec3(m_V[1], m_V[2], m_V[0]);
	}
	vec3 yxx() const
	{
		return vec3(m_V[1], m_V[0], m_V[0]);
	}
	vec3 yzz() const
	{
		return vec3(m_V[1], m_V[2], m_V[2]);
	}
	vec3 yyx() const
	{
		return vec3(m_V[1], m_V[1], m_V[0]);
	}
	vec3 yyz() const
	{
		return vec3(m_V[1], m_V[1], m_V[2]);
	}
	vec3 yyy() const
	{
		return vec3(m_V[1], m_V[1], m_V[1]);
	}
	vec3 yxy() const
	{
		return vec3(m_V[1], m_V[0], m_V[1]);
	}
	vec3 yzy() const
	{
		return vec3(m_V[1], m_V[2], m_V[1]);
	}

	vec2 zx() const
	{
		return vec2(m_V[1], m_V[2]);
	}
	vec2 zy() const
	{
		return vec2(m_V[1], m_V[1]);
	}
	vec2 zz() const
	{
		return vec2(m_V[1], m_V[1]);
	}
	vec3 zxy() const
	{
		return vec3(m_V[1], m_V[0], m_V[2]);
	}
	vec3 zyx() const
	{
		return vec3(m_V[1], m_V[2], m_V[0]);
	}
	vec3 zxx() const
	{
		return vec3(m_V[1], m_V[0], m_V[0]);
	}
	vec3 zyy() const
	{
		return vec3(m_V[1], m_V[2], m_V[2]);
	}
	vec3 zzx() const
	{
		return vec3(m_V[2], m_V[2], m_V[0]);
	}
	vec3 zzy() const
	{
		return vec3(m_V[2], m_V[2], m_V[1]);
	}
	vec3 zzz() const
	{
		return vec3(m_V[2], m_V[2], m_V[2]);
	}
	vec3 zxz() const
	{
		return vec3(m_V[2], m_V[0], m_V[2]);
	}
	vec3 zyz() const
	{
		return vec3(m_V[2], m_V[1], m_V[2]);
	}
#pragma endregion

	//Operators
#pragma region Operators
	friend inline std::ostream& operator<<(std::ostream& out, const vec3& u)
	{
		return out << u[0] << ' ' << u[1] << ' ' << u[2];
	}

	inline vec3& operator=(const vec3& vec) 
	{
		this->m_V[0] = vec.m_V[0];
		this->m_V[1] = vec.m_V[1];
		this->m_V[2] = vec.m_V[2];
		return *this;
	}
	inline vec3* operator=(const vec3* pVec)
	{
		this->m_V[0] = pVec->m_V[0];
		this->m_V[1] = pVec->m_V[1];
		this->m_V[2] = pVec->m_V[2];
		return this;
	}

	inline const float operator[](const int i) const
	{
		return m_V[i];
	}
	inline float& operator[](const int i)
	{
		return m_V[i];
	}

	inline vec3 operator-()
	{
		return vec3(-m_V[0], -m_V[1], -m_V[2]);
	}

	inline vec3 operator-(const vec3& o) const
	{
		return vec3(m_V[0] - o[0], m_V[1] - o[1], m_V[2] - o[2]);
	}	
	inline vec3& operator-=(const vec3& o)
	{
		m_V[0] -= o[0];
		m_V[1] -= o[1];
		m_V[2] -= o[2];
		return *this;
	}
	inline vec3 operator+(const vec3& o) const
	{
		return vec3(m_V[0] + o[0], m_V[1] + o[1], m_V[2] + o[2]);
	}
	inline vec3& operator+=(const vec3& o)
	{
		m_V[0] += o[0];
		m_V[1] += o[1];
		m_V[2] += o[2];
		return *this;
	}

	inline vec3 operator/(const vec3& o) const
	{
		return vec3(m_V[0] / o[0], m_V[1] / o[1], m_V[2] / o[2]);
	}
	inline vec3& operator/=(const vec3& o)
	{
		m_V[0] /= o[0];
		m_V[1] /= o[1];
		m_V[2] /= o[2];
		return *this;
	}
	inline vec3& operator/=(const float o)
	{
		m_V[0] /= o;
		m_V[1] /= o;
		m_V[2] /= o;
		return *this;
	}
	inline vec3 operator*(const vec3& o) const
	{
		return vec3(m_V[0] * o[0], m_V[1] * o[1], m_V[2] * o[2]);
	}
	inline vec3& operator*=(const vec3& o)
	{
		m_V[0] *= o[0];
		m_V[1] *= o[1];
		m_V[2] *= o[2];
		return *this;
	}
	inline vec3& operator*=(const float o)
	{
		m_V[0] *= o;
		m_V[1] *= o;
		m_V[2] *= o;
		return *this;
	}

	friend inline vec3 operator-(const vec3& v, const float o)
	{
		return vec3(v[0] - o, v[1] - o, v[2] - o);
	}
	friend inline vec3 operator-(const float o, const vec3& v)
	{
		return vec3(v[0] - o, v[1] - o, v[2] - o);
	}
	friend inline vec3 operator+(const vec3& v, const float o)
	{
		return vec3(v[0] + o, v[1] + o, v[2] + o);
	}
	friend inline vec3 operator+(const float o, const vec3& v)
	{
		return vec3(v[0] + o, v[1] + o, v[2] + o);
	}
	

	friend inline vec3 operator*(const vec3& v, const float o)
	{
		return vec3(v[0] * o, v[1] * o, v[2] * o);
	}
	friend inline vec3 operator*(const float o, const vec3& v)
	{
		return vec3(v[0] * o, v[1] * o, v[2] * o);
	}
	friend inline vec3 operator/(const vec3& v, const float o)
	{
		return vec3(v[0] / o, v[1] / o, v[2] / o);
	}
	friend inline vec3 operator/(const float o, const vec3& v)
	{
		return vec3(v[0] / o, v[1] / o, v[2] / o);
	}
#pragma endregion

	//Math
#pragma region Math
	inline vec3& Pow(const float power) 
	{
		m_V[0] = powf(m_V[0], power);
		m_V[0] = powf(m_V[1], power);
		m_V[0] = powf(m_V[2], power);
		return *this;
	}
	inline vec3 GetPow(const float power) const
	{
		return vec3(
			powf(m_V[0], power),
			powf(m_V[1], power),
			powf(m_V[2], power));
	}

	inline float SquareMagnitude() const 
	{
		return m_V[0] * m_V[0] + m_V[1] * m_V[1] + m_V[2] * m_V[2];
	}
	static inline float SquareMagnitude(vec3& v) 
	{
		return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
	}
	inline float Length() const 
	{
		return sqrtf(m_V[0] * m_V[0] + m_V[1] * m_V[1] + m_V[2] * m_V[2]);
	}
	static inline float Length(vec3& v)
	{
		return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	}
	static inline float Length(const vec3& v)
	{
		return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	}
	inline vec3& Normalised()
	{
		*this /= Length();
		return *this;
	}
	inline void Normalise()
	{
		*this /= Length();
	}
	static inline vec3& Normalised(vec3& v)
	{
		return v.Normalised();
	}
	static inline void Normalise(vec3& v)
	{
		v.Normalise();
	}
	
	inline float Dot(const vec3& o) const
	{
		return m_V[0] * o[0] + m_V[1] * o[1] + m_V[2] * o[2];
	}
	static inline float Dot(const vec3& u, const vec3& o)
	{
		return u[0] * o[0] + u[1] * o[1] + u[2] * o[2];
	}
	inline vec3 Cross(const vec3& o) const
	{
		return vec3(m_V[1] * o[2] - m_V[2] * o[1],
					m_V[2] * o[0] - m_V[0] * o[2],
					m_V[0] * o[1] - m_V[1] * o[0]);
	}
	static inline vec3 Cross(const vec3& u, const vec3& o)
	{
		return vec3(u[1] * o[2] - u[2] * o[1],
					u[2] * o[0] - u[0] * o[2],
					u[0] * o[1] - u[1] * o[0]);
	}

	inline bool NearZero() const
	{
		const float min = float(1e-8);
		return (fabs(m_V[0]) < min) && (fabs(m_V[1]) < min) && (fabs(m_V[2]) < min);
	}

	static inline vec3 Reflect(const vec3& v, const vec3& n)
	{
		return v - 2.f * Dot(v, n) * n;
	}
	inline vec3 Reflect(const vec3& n) const 
	{
		return Reflect(xyz(), n);
	}

	static inline vec3 Refract(const vec3& v, const vec3& n, const float refracFrac)
	{
		const float angle = Dot(-1.f * v, n);
		vec3 rayPerp = refracFrac * (v + angle * n);
		vec3 rayPara = -sqrtf(fabs(1.f - rayPerp.SquareMagnitude())) * n;
		return rayPerp + rayPara;
	}
	inline vec3 Refract(const vec3& n, const float refracFrac) const
	{
		return Refract(xyz(), n, refracFrac);
	}
#pragma endregion

private:
	//Value
	float m_V[3];
};