#include "DirectXMath/DirectXMath.h"
#include <math.h>

using namespace DirectX;

#pragma once

namespace SKMath {

typedef int32_t bool32_t;
typedef struct vec2 {
	float x, y;
} vec2;
typedef struct vec3 {
	float x, y, z;
} vec3;
typedef struct vec4 {
	float x, y, z, w;
} vec4;
typedef struct quat {
	float x, y, z, w;
} quat;
typedef union matrix {
	vec4 row[4];
	float m[16];
} matrix;
typedef struct rect_t {
	float x, y, w, h;
} rect_t;
typedef struct ray_t {
	vec3 pos;
	vec3 dir;
} ray_t;
typedef struct bounds_t {
	vec3 center;
	vec3 dimensions;
} bounds_t;
typedef struct plane_t {
	vec3  normal;
	float d;
} plane_t;
typedef struct sphere_t {
	vec3  center;
	float radius;
} sphere_t;
typedef struct pose_t {
	vec3 position;
	quat orientation;
} pose_t;

///////////////////////////////////////////

#ifdef __cplusplus

#define sk_default(...) = __VA_ARGS__
#define ref(x) x&
#define ref_arr(x) x*&

static inline vec2  operator*(const vec2 &a, const float b) { return { a.x * b, a.y * b }; }
static inline vec2  operator/(const vec2 &a, const float b) { return { a.x / b, a.y / b }; }
static inline vec2  operator+(const vec2 &a, const vec2 &b) { return { a.x + b.x, a.y + b.y }; }
static inline vec2  operator-(const vec2 &a, const vec2 &b) { return { a.x - b.x, a.y - b.y }; }
static inline vec2  operator*(const vec2 &a, const vec2 &b) { return { a.x * b.x, a.y * b.y }; }
static inline vec2  operator/(const vec2 &a, const vec2 &b) { return { a.x / b.x, a.y / b.y }; }
static inline vec2& operator+=(vec2& a, const vec2& b)     { a.x += b.x; a.y += b.y; return a; }
static inline vec2& operator-=(vec2& a, const vec2& b)     { a.x -= b.x; a.y -= b.y; return a; }
static inline vec2& operator*=(vec2& a, const float b)     { a.x *= b; a.y *= b; return a; }
static inline vec2& operator/=(vec2& a, const float b)     { a.x /= b; a.y /= b; return a; }

static inline vec3  operator*(const vec3 &a, const float b) { return { a.x * b, a.y * b, a.z * b }; }
static inline vec3  operator/(const vec3 &a, const float b) { return { a.x / b, a.y / b, a.z / b }; }
static inline vec3  operator+(const vec3 &a, const vec3 &b) { return { a.x + b.x, a.y + b.y, a.z + b.z }; }
static inline vec3  operator-(const vec3 &a, const vec3 &b) { return { a.x - b.x, a.y - b.y, a.z - b.z }; }
static inline vec3  operator-(const vec3 &a)                { return { -a.x, -a.y, -a.z }; }
static inline vec3  operator*(const vec3 &a, const vec3 &b) { return { a.x * b.x, a.y * b.y, a.z * b.z }; }
static inline vec3  operator/(const vec3 &a, const vec3 &b) { return { a.x / b.x, a.y / b.y, a.z / b.z }; }
static inline vec3& operator+=(vec3& a, const vec3& b)     { a.x += b.x; a.y += b.y; a.z += b.z; return a; }
static inline vec3& operator-=(vec3& a, const vec3& b)     { a.x -= b.x; a.y -= b.y; a.z -= b.z; return a; }
static inline vec3& operator*=(vec3& a, const float b)     { a.x *= b; a.y *= b; a.z *= b; return a; }
static inline vec3& operator/=(vec3& a, const float b)     { a.x /= b; a.y /= b; a.z /= b; return a; }

static quat quat_mul(const quat &a, const quat &b);
static vec3 quat_mul_vec(const quat &a, const vec3 &b);
static void matrix_mul(const ref(matrix) a, const ref(matrix) b, ref(matrix) result);

static inline vec3   operator*(const quat &a, const vec3 &b) { return quat_mul_vec(a, b); }
static inline quat   operator*(const quat &a, const quat &b) { return quat_mul(a, b); }
static inline matrix operator*(const ref(matrix) a, const ref(matrix) b) { matrix result; matrix_mul(a, b, result); return result; }

static inline float vec3_magnitude_sq(const ref(vec3) a) { return a.x * a.x + a.y * a.y + a.z * a.z; }
static inline float vec3_magnitude   (const ref(vec3) a) { return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z); }
static inline vec3  vec3_normalize   (const ref(vec3) a) { return a / vec3_magnitude(a); }
static inline vec3  vec3_lerp        (const ref(vec3) a, const ref(vec3) b, float t) { return a + (b - a)*t; }
static inline float vec3_dot         (const ref(vec3) a, const ref(vec3) b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
static inline vec3  vec3_abs         (const ref(vec3) a) { return { fabsf(a.x), fabsf(a.y), fabsf(a.z) }; }

static inline vec2  vec2_lerp        (const ref(vec2) a, const ref(vec2) b, float t) { return a + (b - a)*t; }
#else
static inline float vec3_magnitude_sq(const ref(vec3) a) { return a->x * a->x + a->y * a->y + a->z * a->z; }
static inline float vec3_magnitude   (const ref(vec3) a) { return sqrtf(a->x * a->x + a->y * a->y + a->z * a->z); }
static inline vec3  vec3_normalize   (const ref(vec3) a) { float mag = 1.0f/vec3_magnitude(a); vec3 result = {a->x*mag, a->y*mag, a->z*mag}; return result; }
static inline vec3  vec3_lerp        (const ref(vec3) a, const ref(vec3) b, float t) { vec3 result = { a->x + (b->x - a->x)*t, a->y + (b->y - a->y)*t, a->z + (b->z - a->z)*t }; return result; }
static inline float vec3_dot         (const ref(vec3) a, const ref(vec3) b) { return a->x*b->x + a->y*b->y + a->z*b->z; }
static inline vec3  vec3_abs         (const ref(vec3) a) { vec3 result = { fabsf(a->x), fabsf(a->y), fabsf(a->z) }; return result; }

static inline vec2  vec2_lerp        (const ref(vec2) a, const ref(vec2) b, float t) { vec2 result = {a->x + (b->x - a->x)*t, a->y + (b->y - a->y)*t}; return result; }
#endif

static const float pi = 3.1415926535898f;
static const float deg2rad = 0.01745329252f;
static const float rad2deg = 57.295779513f;
static const float cm2m = 0.01f;
static const float mm2m = 0.001f;
static const float m2cm = 100.f;
static const float m2mm = 1000.f;

static const vec2 vec2_zero     = { 0,0 };
static const vec2 vec2_one      = { 1,1 };
static const vec3 vec3_one      = { 1,1, 1 };
static const vec3 vec3_zero     = { 0,0, 0 };
static const vec3 vec3_up       = { 0,1, 0 };
static const vec3 vec3_forward  = { 0,0,-1 };
static const vec3 vec3_right    = { 1,0, 0 };
static const quat quat_identity = { 0,0, 0,1 };
static const matrix matrix_identity = { { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} } };

#define unit_cm(cm) ((cm)*0.01f)
#define unit_mm(mm) ((mm)*0.001f)
#define unit_dmm(dmm, distance) ((dmm)*(distance))

///////////////////////////////////////////

static inline DirectX::XMVECTOR math_vec3_to_fast(const vec3 &vector) {
	return DirectX::XMLoadFloat3((DirectX::XMFLOAT3 *)&vector);
}

///////////////////////////////////////////

static inline DirectX::XMVECTOR math_quat_to_fast(const quat &quaternion) {
	return DirectX::XMLoadFloat4((DirectX::XMFLOAT4 *)&quaternion);
}

///////////////////////////////////////////

static inline vec3 math_fast_to_vec3(const DirectX::XMVECTOR &a) {
	vec3 result;
	DirectX::XMStoreFloat3((DirectX::XMFLOAT3 *)&result, a);
	return result;
}

///////////////////////////////////////////

static inline quat math_fast_to_quat(const DirectX::XMVECTOR &a) {
	quat result;
	DirectX::XMStoreFloat4((DirectX::XMFLOAT4 *)&result, a);
	return result;
}

///////////////////////////////////////////

static inline void math_matrix_to_fast(const matrix &mat, DirectX::XMMATRIX *out_matrix) {
	*out_matrix = DirectX::XMLoadFloat4x4((DirectX::XMFLOAT4X4 *)&mat.row);
}

///////////////////////////////////////////

static inline void math_fast_to_matrix(const DirectX::XMMATRIX &mat, matrix *out_matrix) {
	DirectX::XMStoreFloat4x4((DirectX::XMFLOAT4X4 *)out_matrix, mat);
}

///////////////////////////////////////////

static inline int32_t  maxi(int32_t  a, int32_t  b) { return a > b ? a : b; }
static inline uint32_t maxi(uint32_t a, uint32_t b) { return a > b ? a : b; }
static inline int64_t  maxi(int64_t  a, int64_t  b) { return a > b ? a : b; }
static inline uint64_t maxi(uint64_t a, uint64_t b) { return a > b ? a : b; }
static inline int32_t  mini(int32_t  a, int32_t  b) { return a < b ? a : b; }
static inline uint32_t mini(uint32_t a, uint32_t b) { return a < b ? a : b; }
static inline int64_t  mini(int64_t  a, int64_t  b) { return a < b ? a : b; }
static inline uint64_t mini(uint64_t a, uint64_t b) { return a < b ? a : b; }

static inline float math_lerp    (float a, float b, float t) { return a + (b - a) * t; }
static inline float math_lerp_cl (float a, float b, float t) { return a + (b - a) * fminf(1,t); }
static inline float math_saturate(float x)                   { return fmaxf(0, fminf(1, x)); }

static inline float math_ease_overshoot(float a, float b, float overshoot, float t) { t = 1 - t; return math_lerp(a,b, 1-(t*t * ((overshoot + 1) * t - overshoot))); }
static inline float math_ease_hop      (float a, float peak, float t) { return a+(peak-a)*sinf(t*pi); }

///////////////////////////////////////////

matrix matrix_trs(const vec3 &position, const quat &orientation, const vec3 &scale) {
	XMMATRIX mat = XMMatrixAffineTransformation(
		XMLoadFloat3((XMFLOAT3 *)& scale), DirectX::g_XMZero,
		XMLoadFloat4((XMFLOAT4 *)& orientation),
		XMLoadFloat3((XMFLOAT3 *)& position));
	matrix result;
	math_fast_to_matrix(mat, &result);
	return result;
}

///////////////////////////////////////////

void matrix_trs_out(matrix &out_result, const vec3 &position, const quat &orientation, const vec3 &scale) {
	XMMATRIX mat = XMMatrixAffineTransformation(
		XMLoadFloat3((XMFLOAT3 *)& scale), DirectX::g_XMZero,
		XMLoadFloat4((XMFLOAT4 *)& orientation),
		XMLoadFloat3((XMFLOAT3 *)& position));
	math_fast_to_matrix(mat, &out_result);
}

///////////////////////////////////////////

static inline vec3 vec3_cross(const vec3 &a, const vec3 &b) {
	return math_fast_to_vec3( XMVector3Cross(math_vec3_to_fast(a), math_vec3_to_fast(b)) );
}

///////////////////////////////////////////

static inline vec3 quat_mul_vec(const quat &a, const vec3 &b) {
	XMVECTOR rotation = XMVector3Rotate(XMLoadFloat3((XMFLOAT3*)&b), XMLoadFloat4((XMFLOAT4*)&a));
	return math_fast_to_vec3(rotation);
}

///////////////////////////////////////////

static inline quat quat_mul(const quat &a, const quat &b) {
	XMVECTOR rotation = XMQuaternionMultiply(XMLoadFloat4((XMFLOAT4*)&a),XMLoadFloat4((XMFLOAT4*)&b));
	return math_fast_to_quat(rotation);
}

///////////////////////////////////////////

static inline quat quat_difference(const quat &a, const quat &b) {
	XMVECTOR inv        = XMQuaternionInverse (XMLoadFloat4((XMFLOAT4 *)& a));
	XMVECTOR difference = XMQuaternionMultiply(inv, XMLoadFloat4((XMFLOAT4 *)& b));
	//difference = XMQuaternionNormalize(difference);
	return math_fast_to_quat(difference);
}

///////////////////////////////////////////

static inline quat quat_lookat(const vec3 &from, const vec3 &at) {
	XMMATRIX mat = XMMatrixLookAtRH(math_vec3_to_fast(from), math_vec3_to_fast(at), XMVectorSet(0, 1, 0, 0));
	return math_fast_to_quat(XMQuaternionRotationMatrix(XMMatrixTranspose(mat)));
}

///////////////////////////////////////////

static inline quat quat_lookat_up(const vec3 &from, const vec3 &at, const vec3 &up) {
	XMMATRIX mat = XMMatrixLookAtRH(math_vec3_to_fast(from), math_vec3_to_fast(at), math_vec3_to_fast(up));
	return math_fast_to_quat(XMQuaternionRotationMatrix(XMMatrixTranspose(mat)));
}

///////////////////////////////////////////

static inline quat quat_from_angles(float pitch_x_deg, float yaw_y_deg, float roll_z_deg) {
	XMVECTOR result = XMQuaternionRotationRollPitchYaw(pitch_x_deg * deg2rad, yaw_y_deg * deg2rad, roll_z_deg * deg2rad);
	return math_fast_to_quat(result);
}

///////////////////////////////////////////

static inline quat quat_slerp(const quat &a, const quat &b, float t) {
	XMVECTOR blend = XMQuaternionSlerp(XMLoadFloat4((XMFLOAT4 *)& a), XMLoadFloat4((XMFLOAT4 *)& b), t);
	return math_fast_to_quat(blend);
}

///////////////////////////////////////////

static inline quat quat_normalize(const quat &a) {
	return math_fast_to_quat(XMQuaternionNormalize(math_quat_to_fast(a)));
}

///////////////////////////////////////////

static inline quat quat_inverse(const quat &a) {
	return math_fast_to_quat(XMQuaternionInverse(math_quat_to_fast(a)));
}

///////////////////////////////////////////

static inline void pose_matrix_out(const pose_t &pose, matrix &out_result, vec3 scale) {
	matrix_trs_out(out_result, pose.position, pose.orientation, scale);
}

///////////////////////////////////////////

static inline matrix pose_matrix(const pose_t &pose, vec3 scale) {
	return matrix_trs(pose.position, pose.orientation, scale);
}

///////////////////////////////////////////

static inline bool32_t ray_intersect_plane(ray_t ray, vec3 plane_pt, vec3 plane_normal, float &out_t) {
	float denom = vec3_dot(plane_normal, ray.dir);
	if (denom > 1e-6) {
		vec3 difference = plane_pt - ray.pos;
		out_t = vec3_dot(difference, plane_normal) / denom;
		return (out_t >  1e-6);
	}
	return false;
}

///////////////////////////////////////////

static inline void matrix_inverse(const matrix &a, matrix &out_matrix) {
	XMMATRIX mat_a, mat_result;
	math_matrix_to_fast(a, &mat_a);
	mat_result = XMMatrixInverse(nullptr, mat_a);
	math_fast_to_matrix(mat_result, &out_matrix);
}

///////////////////////////////////////////

static inline void matrix_mul(const matrix &a, const matrix &b, matrix &out_matrix) {
	XMMATRIX mat_a, mat_b, mat_result;
	math_matrix_to_fast(a, &mat_a);
	math_matrix_to_fast(b, &mat_b);
	mat_result = XMMatrixMultiply(mat_a, mat_b);
	math_fast_to_matrix(mat_result, &out_matrix);
}

///////////////////////////////////////////

static inline void matrix_mul(const matrix &a, const matrix &b, DirectX::XMMATRIX &out_matrix) {
	XMMATRIX mat_a, mat_b;
	math_matrix_to_fast(a, &mat_a);
	math_matrix_to_fast(b, &mat_b);
	out_matrix = mat_a * mat_b;
}

///////////////////////////////////////////

static inline void matrix_mul(const matrix &a, const DirectX::XMMATRIX &b, DirectX::XMMATRIX &out_matrix) {
	XMMATRIX mat_a;
	math_matrix_to_fast(a, &mat_a);
	out_matrix = mat_a * b;
}

///////////////////////////////////////////

static inline vec3 matrix_mul_point(const matrix &transform, const vec3 &point) {
	XMMATRIX mat;
	math_matrix_to_fast(transform, &mat);
	return math_fast_to_vec3( XMVector3Transform(math_vec3_to_fast(point), mat) );
}

///////////////////////////////////////////

static inline vec3 matrix_mul_point(const XMMATRIX &transform, const vec3 &point) {
	return math_fast_to_vec3( XMVector3Transform(math_vec3_to_fast(point), transform) );
}

///////////////////////////////////////////

static inline vec3 matrix_mul_direction(const matrix &transform, const vec3 &direction) {
	XMMATRIX mat;
	math_matrix_to_fast(transform, &mat);
	return math_fast_to_vec3( XMVector3TransformNormal(math_vec3_to_fast(direction), mat) );
}

///////////////////////////////////////////

static inline vec3 matrix_mul_direction(const XMMATRIX &transform, const vec3 &direction) {
	return math_fast_to_vec3( XMVector3TransformNormal(math_vec3_to_fast(direction), transform) );
}

///////////////////////////////////////////

static inline quat matrix_mul_rotation(const matrix& transform, const quat& orientation) {
	XMMATRIX mat = XMMatrixRotationQuaternion(math_quat_to_fast(orientation));
	XMMATRIX fast_transform;
	math_matrix_to_fast(transform, &fast_transform);
	return math_fast_to_quat(XMQuaternionRotationMatrix(XMMatrixMultiply(mat, fast_transform)));
}

///////////////////////////////////////////

static inline void matrix_decompose(const matrix &transform, vec3 &out_position, vec3 &out_scale, quat &out_orientation) {
	XMVECTOR pos, scale, rot;
	XMMATRIX mat;
	math_matrix_to_fast(transform, &mat);
	XMMatrixDecompose(&scale, &rot, &pos, mat);

	out_position    = math_fast_to_vec3(pos);
	out_scale       = math_fast_to_vec3(scale);
	out_orientation = math_fast_to_quat(rot);
}

///////////////////////////////////////////

static inline vec3 matrix_to_angles(const matrix &transform) {
	// see: https://stackoverflow.com/questions/1996957/conversion-euler-to-matrix-and-matrix-to-euler
	vec3 result;
	result.x = asinf(-transform.m[9]); // _32
	if (cosf(result.x) > 0.0001f) {
		result.y = atan2f(transform.m[8], transform.m[10]); // _31, _33
		result.z = atan2f(transform.m[1], transform.m[5] ); // _12, _22
	} else {
		result.y = 0.0f;
		result.z = atan2f(-transform.m[4], transform.m[0]); // _21, _11
	}
	return result * rad2deg;
}

///////////////////////////////////////////

static inline vec3 bounds_corner(const bounds_t &bounds, int32_t index8) {
	// Sign generates a pattern like this:
	// -1, -1, -1
	// -1, -1,  1
	// -1,  1, -1
	// -1,  1,  1
	//  1, -1, -1
	//  1, -1,  1
	//  1,  1, -1
	//  1,  1,  1
	vec3 sign = {
		(float)( (index8 / 4) * 2 - 1),
		(float)(((index8 / 2) % 2) * 2 - 1),
		(float)( (index8 % 2) * 2 - 1) };
	vec3 half = bounds.dimensions / 2;
	return bounds.center + half * sign;
}

///////////////////////////////////////////

static inline vec3 math_cubemap_corner(int i) {
	float neg = (float)((i / 4) % 2 ? -1 : 1);
	int nx  = ((i+24) / 16) % 2;
	int ny  = (i / 8)       % 2;
	int nz  = (i / 16)      % 2;
	int u   = ((i+1) / 2)   % 2; // U: 0,1,1,0
	int v   = (i / 2)       % 2; // V: 0,0,1,1

	return {
		(nx ? neg : ny ? (u?-1:1)*neg : (u?1:-1)*neg),
		(nx || nz ? (v?1:-1) : neg),
		(nx ? (u?-1:1)*neg : ny ? (v?1:-1) : neg)
	};
}

}
