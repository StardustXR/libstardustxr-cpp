#pragma once

namespace StardustXRFusion {

struct Vec2 {
	float x, y;

	Vec2(float x, float y);
#ifdef GLM
	Vec2(glm::vec2 const& v);
	operator glm::vec2() const;
#endif

	Vec2 operator*(float rhs) const;

	static const Vec2 Zero;
	static const Vec2 One;
};


struct Vec3 {
	float x, y, z;

	Vec3(float x, float y, float z);
#ifdef GLM
	Vec3(glm::vec3 const& v);
	operator glm::vec3() const;
#endif

	Vec3 operator*(float rhs) const;

	static const Vec3 Zero;
	static const Vec3 One;
	static const Vec3 Up;
	static const Vec3 Right;
	static const Vec3 Forward;
};


struct Quat {
	float x, y, z, w;

	Quat(float x, float y, float z, float w);
#ifdef GLM
	Quat(glm::quat const& v);
	operator glm::quat() const;
#endif

	static const Quat Identity;
};


struct Pose {
	Vec3 position;
	Quat rotation;

	Pose(Vec3 position, Quat rotation);

	static const Pose Identity;
};


struct Color {
	float r, g, b, a;

	Color(float r, float g, float b, float a);
#ifdef GLM
	Color(glm::vec4 const& v);
	operator glm::vec4() const;
#endif
	static Color FromHSVA(float h, float s, float v, float a);

	static const Color Black;
	static const Color White;
};

}
