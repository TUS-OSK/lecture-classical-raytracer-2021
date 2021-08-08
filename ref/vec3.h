#ifndef _VEC3_H
#define _VEC3_H

#include <iostream>
#include <cmath>

template <typename type>
struct Vec3
{
	type v[3];

	Vec3()
	{
		v[0] = 0;
		v[1] = 0;
		v[2] = 0;
	}

	Vec3(type inv)
	{
		v[0] = inv;
		v[1] = inv;
		v[2] = inv;
	}

	Vec3(type inv1, type inv2, type inv3)
	{
		v[0] = inv1;
		v[1] = inv2;
		v[2] = inv3;
	}

	void Normalize()
	{
		float nolm = this->Nolm();
		v[0] = v[0] / nolm;
		v[1] = v[1] / nolm;
		v[2] = v[2] / nolm;
	}

	float Nolm() const
	{
		return std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	}
	float Nolm2() const
	{
		return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
	}

	type operator[](unsigned int i) const { return v[i]; }
	type &operator[](unsigned int i) { return v[i]; }

	Vec3 operator-() const { return Vec3(-v[0], -v[1], v[2]); }

	Vec3 &operator-=(const Vec3 &v)
	{
		this->v[0] -= v[0];
		this->v[1] -= v[1];
		this->v[2] -= v[2];
		return *this;
	}

	Vec3 &operator+=(const Vec3 &v)
	{
		this->v[0] += v[0];
		this->v[1] += v[1];
		this->v[2] += v[2];
		return *this;
	}

	Vec3 &operator*=(const Vec3 &v)
	{
		this->v[0] *= v[0];
		this->v[1] *= v[1];
		this->v[2] *= v[2];
		return *this;
	}

	Vec3 &operator/=(const Vec3 &v)
	{
		this->v[0] /= v[0];
		this->v[1] /= v[1];
		this->v[2] /= v[2];
		return *this;
	}
};

//アダマール積
template <typename T>
inline Vec3<T> operator*(const Vec3<T> &v1, const Vec3<T> &v2)
{
	Vec3<T> ret;
	for (int i = 0; i < 3; ++i)
	{
		ret[i] = v1[i] * v2[i];
	}
	return ret;
}

//アダマール積(除算)
template <typename T>
inline Vec3<T> operator/(const Vec3<T> &v1, const Vec3<T> &v2)
{
	Vec3<T> ret;
	for (int i = 0; i < 3; ++i)
	{
		ret[i] = v1[i] / v2[i];
	}
	return ret;
}

template <typename T>
inline Vec3<T> operator+(const Vec3<T> &v1, const Vec3<T> &v2)
{
	Vec3<T> ret;
	for (int i = 0; i < 3; ++i)
	{
		ret[i] = v1[i] + v2[i];
	}
	return ret;
}

template <typename T>
inline Vec3<T> operator-(const Vec3<T> &v1, const Vec3<T> &v2)
{
	Vec3<T> ret;
	for (int i = 0; i < 3; ++i)
	{
		ret[i] = v1[i] - v2[i];
	}
	return ret;
}

template <typename T>
inline Vec3<T> operator*(const Vec3<T> &v1, const T f)
{
	Vec3<T> ret;
	for (int i = 0; i < 3; ++i)
	{
		ret[i] = v1[i] * f;
	}
	return ret;
}

template <typename T>
inline Vec3<T> operator*(const T f, const Vec3<T> &v1)
{
	Vec3<T> ret;
	for (int i = 0; i < 3; ++i)
	{
		ret[i] = v1[i] * f;
	}
	return ret;
}

template <typename T>
inline Vec3<T> operator/(const Vec3<T> &v1, const T f)
{
	Vec3<T> ret;
	for (int i = 0; i < 3; ++i)
	{
		ret[i] = v1[i] / f;
	}
	return ret;
}

template <typename T>
inline Vec3<T> operator/(const T f, const Vec3<T> v1)
{
	Vec3<T> ret;
	for (int i = 0; i < 3; ++i)
	{
		ret[i] = v1[i] / f;
	}
	return ret;
}
template <typename T>
inline float length(const Vec3<T> &v)
{
	float sum = 0;
	for (int i = 0; i < 3; ++i)
	{
		sum += v[i] * v[i];
	}

	return std::sqrt(sum);
}

template <typename T>
inline float length2(const Vec3<T> &v)
{
	float sum = 0;
	for (int i = 0; i < 3; i++)
	{
		sum += v[i] * v[i];
	}

	return sum;
}

template <typename T>
inline Vec3<T> normalize(const Vec3<T> &v)
{
	return v / length(v);
}

template <typename T>
inline T dot(const Vec3<T> &v1, const Vec3<T> &v2)
{
	T ret = 0;
	for (int i = 0; i < 3; ++i)
	{
		ret += v1[i] * v2[i];
	}

	return ret;
}

template <typename T>
inline Vec3<T> cross(const Vec3<T> &v1, const Vec3<T> &v2)
{
	Vec3<T> ret;
	ret[0] = v1[1] * v2[2] - v1[2] * v2[1];
	ret[1] = v1[2] * v2[0] - v1[0] * v2[2];
	ret[2] = v1[0] * v2[1] - v1[1] * v2[0];

	return ret;
}

template <typename T>
inline std::ostream &operator<<(std::ostream &stream, const Vec3<T> &v)
{
	stream << "(" << v[0] << "," << v[1] << "," << v[2] << ")";
	return stream;
}

using Vec3u = Vec3<unsigned int>;
using Vec3f = Vec3<float>;

#endif
