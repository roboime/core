#pragma once

#include <base/gamestate.h>

namespace ime{

class LinearDerivator {
public:
	LinearDerivator();
	~LinearDerivator();
	void derive(Vector2 v, float t);
	bool hasLastState();
	void reset();
private:
	Vector2 lastState_;
	float timeStamp_;

};

class AngularDerivator {
public:
	AngularDerivator();
	~AngularDerivator();
	void derive(float a, float t);
	bool hasLastState();
	void reset();
private:
	float lastState_;
	float timeStamp_;
};

}