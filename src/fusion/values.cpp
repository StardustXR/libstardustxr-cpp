#include "values.hpp"
#include <cmath>

namespace StardustXRFusion {

inline float lerp(float t, float a, float b){
	return (1-t)*a + t*b;
}

const Vec2 Vec2::Zero = {0,0};
const Vec2 Vec2::One  = {1,1};

const Vec3 Vec3::Zero    = {0,0,0};
const Vec3 Vec3::One     = {1,1,1};
const Vec3 Vec3::Up      = {0,1,0};
const Vec3 Vec3::Right   = {1,0,0};
const Vec3 Vec3::Forward = {0,0,-1};

const Quat Quat::Identity = {0,0,0,1};
const Pose Pose::Identity = {Vec3::Zero, Quat::Identity};

const Color Color::Black = {0,0,0,1};
const Color Color::White = {1,1,1,1};


Vec2::Vec2(float x, float y)                     : x(x), y(y) {}
Vec3::Vec3(float x, float y, float z)            : x(x), y(y), z(z) {}
Quat::Quat(float x, float y, float z, float w)   : x(x), y(y), z(z), w(w) {}
Pose::Pose(Vec3 position, Quat rotation)         : position(position), rotation(rotation) {}
Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

Vec2::Vec2() : Vec2(0,0) {}
Vec3::Vec3() : Vec3(0,0,0) {}
Quat::Quat() : Quat(Quat::Identity) {}
Pose::Pose() : Pose(Pose::Identity) {}
Color::Color() : Color(Color::White) {}

Vec2 Vec2::operator-() const {
	return { -x, -y };
}
Vec2 Vec2::operator+(Vec2 const rhs) const {
	return {
		x + rhs.x,
		y + rhs.y
	};
}
Vec2 Vec2::operator-(Vec2 const rhs) const {
	return {
		x - rhs.x,
		y - rhs.y
	};
}
Vec2 Vec2::operator*(float rhs) const {
	return {
		x * rhs,
		y * rhs
	};
}
Vec2 Vec2::operator/(float rhs) const {
	return {
		x / rhs,
		y / rhs
	};
}


Vec3 Vec3::operator-() const {
	return { -x, -y, -z };
}
Vec3 Vec3::operator+(Vec3 const rhs) const {
	return {
		x + rhs.x,
		y + rhs.y,
		z + rhs.z
	};
}
Vec3 Vec3::operator-(Vec3 const rhs) const {
	return {
		x - rhs.x,
		y - rhs.y,
		z - rhs.z
	};
}
Vec3 Vec3::operator*(float rhs) const {
	return {
		x * rhs,
		y * rhs,
		z * rhs
	};
}
Vec3 Vec3::operator/(float rhs) const {
	return {
		x / rhs,
		y / rhs,
		z / rhs
	};
}


Color Color::FromHSVA(float h, float s, float v, float a) {
	const float Kx = 1.0f;
	const float Ky = 2.0f / 3.0f;
	const float Kz = 1.0f / 3.0f;
	const float Kw = 3.0f;
	Vec3 p = {
		fabsf(((h + Kx) - floorf(h + Kx)) * 6.0f - Kw),
		fabsf(((h + Ky) - floorf(h + Ky)) * 6.0f - Kw),
		fabsf(((h + Kz) - floorf(h + Kz)) * 6.0f - Kw)
	};
	return {
		lerp(Kx, fmaxf(0,fminf(p.x - Kx, 1.0f)), s) * v,
		lerp(Kx, fmaxf(0,fminf(p.y - Kx, 1.0f)), s) * v,
		lerp(Kx, fmaxf(0,fminf(p.z - Kx, 1.0f)), s) * v,
		a
	};
}

}
