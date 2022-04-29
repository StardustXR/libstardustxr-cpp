#pragma once

#ifdef NO_GLM_PRESENT
#error <stardustxr/values/glm.hpp> included after <stardustxr/values.hpp> or "GLM" not defined.
#endif

#define GLM
#define GLM_FORCE_SINGLE_ONLY
#define GLM_FORCE_SWIZZLE
#undef  GLM_FORCE_LEFT_HANDED

#include <glm/ext/vector_common.hpp>
#include <glm/ext/vector_relational.hpp>
#include <glm/ext/vector_ulp.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>

#include <glm/gtc/quaternion.hpp>

#include "../values.hpp"

namespace StardustXRFusion {

inline Vec2::Vec2(glm::vec2 const& v)   : Vec2(v.x, v.y) {}
inline Vec3::Vec3(glm::vec3 const& v)   : Vec3(v.x, v.y, v.z) {}
inline Quat::Quat(glm::quat const& v)   : Quat(v.x, v.y, v.z, v.w) {}
inline Color::Color(glm::vec4 const& v) : Color(v.r, v.g, v.b, v.a) {}

inline Vec2::operator glm::vec2()  const { return glm::vec2(x, y); }
inline Vec3::operator glm::vec3()  const { return glm::vec3(x, y, z); }
inline Quat::operator glm::quat()  const { return glm::quat(x, y, z, w); }
inline Color::operator glm::vec4() const { return glm::vec4(r, g, b, a); }

}

