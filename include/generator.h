#pragma once
#define WAVLIB_IMPLEMENTATION

#include <wavlib.h>
#include <cmath>
#include <vector>

#include "wav.h"
#include "smath.h"

namespace wavlib
{
	namespace generators
	{
		/* Base class for audio generators */
		class WAVLIB_API generator
		{
		protected:
			float angle, offset;
			float m_amplitude;
			float m_frequency;
			float m_duration;
			float m_phase;
			unsigned int m_sample_rate;
			unsigned int m_num_samples;

			generator(float amp, float freq, float dur, float phase = 0.0f, unsigned int rate = 44100);

		public:
			generator() = delete;
			virtual ~generator() = default;
			virtual float gen() = 0;

			wav				towav();
			float			amp()	const { return m_amplitude; }
			float			freq()	const { return m_frequency; }
			float			dur()	const { return m_duration; }
			float			phase()	const { return m_phase; }
			unsigned int	rate()	const { return m_sample_rate; }
			unsigned int	num()	const { return m_num_samples; }
		};


		/* Simple sinewave generator */
		class WAVLIB_API sine : public generator
		{
		public:
			sine(float amp, float freq, float dur, float phase = 0.0f, unsigned int rate = 44100) : generator(amp, freq, dur, phase, rate)
			{}

			float gen() override
			{
				const float sample = m_amplitude * std::sin(angle);
				angle += offset;
				return sample;
			}

		};

		class WAVLIB_API square : public generator
		{
		public:
			square(float amp, float freq, float dur, float phase = 0.0f, unsigned int rate = 44100) : generator(amp, freq, dur, phase, rate){}

			float gen() override
			{
				const float sample = m_amplitude * wavlib::sgn(std::sin(angle));
				angle += offset;
				return sample;
			}

		};

		class WAVLIB_API triangle : public generator
		{
		public:
			triangle(float amp, float freq, float dur, float phase = 0.0f, unsigned int rate = 44100) : generator(amp, freq, dur, phase, rate){}

			float gen() override
			{
				const float sample = m_amplitude * wavlib::triangle(angle);
				angle += offset;
				return sample;
			}
		};
	}
}

