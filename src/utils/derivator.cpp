#include <utils/vector2.h>
#include <cmath>

namespace ime{
LinearDerivator::
LinearDerivator():timeStamp_{0.0f}{}

LinearDerivator::
~LinearDerivator() {}

void LinearDerivator::
derive(Vector2 v, float t){
	Vector2 result = Vector2();
	if (hasLastState()){
		result = (lastState_ - v)/(timeStamp_ - t)
	}
	timeStamp_ = t;
	lastState_ = v;
	return result;
}

bool LinearDerivator::
hasLastState(){
	return timeStamp_ == 0;
}

void LinearDerivator::
reset(){
	timeStamp_ = 0;
}

AngularDerivator::
AngularDerivator():timeStamp_{0.0f} {}

AngularDerivator::
~AngularDerivator() {}

void AngularDerivator::
derive(float a, float t){
	float result = 0.0f;
	period = t - timeStamp_;
	dif = a - lastState_;
	if (hasLastState()){
		if (std::abs(dif) < M_PI){
			result = dif/period;
		}
		else{
			result = (2*M_PI + dif)/period;
			if (lastState_ < a){
				result = -result;
			}
		}
	}
	timeStamp_ = t;
	lastState_ = v;
	return result;
}

bool AngularDerivator::
hasLastState(){
	return timeStamp_ == 0;
}

void AngularDerivator::
reset(){
	timeStamp_ = 0;
}
}