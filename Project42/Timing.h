#pragma once

namespace Proj42 {
	class FPSLimiter {

	public:
		FPSLimiter();
		void init(float targetFPS);
		void setTargetFPS(float targetFPS);
		void begin();
		float end();		// return the fps

	private:
		void calculateFPS();

		float _targetFPS;
		unsigned int _startTicks;
		float _frameTime;
		float _fps;
	};
};