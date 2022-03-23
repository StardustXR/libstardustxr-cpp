#pragma once

#include <algorithm>
#include <cmath>
#include <functional>

namespace StardustXRFusion {

static float TweenLinear(float t) {
	return t;
}

static float TweenEaseOutElastic(float t) {
	if (t == 0) {
		return 0;
	} if (t == 1) {
		return 1;
	}
	return std::pow(2, -10 * t) * std::sin((t - 0.1) * 5 * 3.14159f) + 1;
}

static float TweenEaseOutBack(float t) {
	const float c1 = 1.70158;
	const float c3 = c1 + 1;

	return 1 + c3 * std::pow(t - 1, 3) + c1 * std::pow(t - 1, 2);
}

static float TweenEaseOutBounce(float t) {
	float x = t;
	const float n1 = 7.5625;
	const float d1 = 2.75;

	if (x < 1 / d1) {
		return n1 * x * x;
	} else if (x < 2 / d1) {
		return n1 * (x -= 1.5 / d1) * x + 0.75;
	} else if (x < 2.5 / d1) {
		return n1 * (x -= 2.25 / d1) * x + 0.9375;
	} else {
		return n1 * (x -= 2.625 / d1) * x + 0.984375;
	}
}

static float TweenEaseOutSine(float t) {
	return std::sin((t * 3.14159f) / 2);
}

static float TweenEaseOutCirc(float t) {
	return std::sqrt(1 - std::pow(t - 1, 2));
}

template<class T>
struct Tween {
	float t = 0;
	float d = 1;
	T start;
	T end;
	float (*curve)(float) = TweenLinear;

	T update(float delta) {
		t += delta;
		t = std::clamp(t, 0.0f, d);
		float m = curve(t/d);

		return ((end - start)*m)+start;
	}
};

}
