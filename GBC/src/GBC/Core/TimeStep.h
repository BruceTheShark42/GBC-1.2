#pragma once

namespace gbc
{
	class TimeStep
	{
	public:
		TimeStep(float time = 0.0f)
			: time(time) {}

		inline operator float() const { return time; }

		inline float seconds() const { return time; }
		inline float millis() const { return time * 1000.0f; }

		inline TimeStep operator-(const TimeStep &step) { return time - step.time; }
	private:
		float time;
	};
}
