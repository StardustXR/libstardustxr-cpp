#pragma once

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

#include <glm/ext/quaternion_common.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/ext/quaternion_exponential.hpp>
#include <glm/ext/quaternion_relational.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/ext/quaternion_float.hpp>

#include "../values.hpp"

namespace StardustXRFusion {

Vec2::Vec2(glm::vec2 const& v)   : Vec2(v.x, v.y) {}
Vec3::Vec3(glm::vec3 const& v)   : Vec3(v.x, v.y, v.z) {}
Quat::Quat(glm::quat const& v)   : Quat(v.x, v.y, v.z, v.w) {}
Color::Color(glm::vec4 const& v) : Color(v.r, v.g, v.b, v.a) {}

Vec2::operator glm::vec2()  const { return glm::vec2(x, y); }
Vec3::operator glm::vec3()  const { return glm::vec3(x, y, z); }
Quat::operator glm::quat()  const { return glm::quat(x, y, z, w); }
Color::operator glm::vec4() const { return glm::vec4(r, g, b, a); }

}

