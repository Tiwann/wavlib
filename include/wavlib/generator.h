#pragma once

#include "config.h"
#include "wav.h"
#include "wavmath.h"
#include <cmath>
#include <vector>

namespace wavlib
{
	namespace generators
	{
		/* Base class for audio generators */
		class WAVLIB_API generator
		{
		protected:
			float m_angle, m_offset;
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

			wav							towav();
			[[nodiscard]] float			amp()	const { return m_amplitude; }
			[[nodiscard]] float			freq()	const { return m_frequency; }
			[[nodiscard]] float			dur()	const { return m_duration; }
			[[nodiscard]] float			phase()	const { return m_phase; }
			[[nodiscard]] unsigned int	rate()	const { return m_sample_rate; }
			[[nodiscard]] unsigned int	num()	const { return m_num_samples; }
		};


		/* Simple sinewave generator */
		class WAVLIB_API sine : public generator
		{
		public:
			sine(float amp, float freq, float dur, float phase = 0.0f, unsigned int rate = 44100) : generator(amp, freq, dur, phase, rate)
			{}

			float gen() override
			{
				const float sample = m_amplitude * std::sin(m_angle);
				m_angle += m_offset;
				return sample;
			}

		};

		class WAVLIB_API square : public generator
		{
		public:
			square(float amp, float freq, float dur, float phase = 0.0f, unsigned int rate = 44100) : generator(amp, freq, dur, phase, rate){}

			float gen() override
			{
				const float sample = m_amplitude * wavlib::sgn(std::sin(m_angle));
				m_angle += m_offset;
				return sample;
			}

		};

		class WAVLIB_API triangle : public generator
		{
		public:
			triangle(float amp, float freq, float dur, float phase = 0.0f, unsigned int rate = 44100) : generator(amp, freq, dur, phase, rate){}

			float gen() override
			{
				const float sample = m_amplitude * wavlib::triangle(m_angle);
				m_angle += m_offset;
				return sample;
			}
		};

		class WAVLIB_API sawtooth : public generator
		{
		public:
			sawtooth(float amp, float freq, float dur, float phase = 0.0f, unsigned int rate = 44100)
			: generator(amp, freq, dur, phase, rate){}

			float gen() override
			{
				const float sample = m_amplitude * wavlib::sawtooth(m_angle);
				m_angle += m_offset;
				return sample;
			}
		};

		class WAVLIB_API isawtooth : public generator
		{
		public:
			isawtooth(float amp, float freq, float dur, float phase = 0.0f, unsigned int rate = 44100)
			: generator(amp, freq, dur, phase, rate){}

			float gen() override
			{
				const float sample = m_amplitude * wavlib::isawtooth(m_angle);
				m_angle += m_offset;
				return sample;
			}
		};

		class WAVLIB_API powersine : public generator
		{
		private:
			uint32_t power = 0;
		public:
			powersine(uint32_t power, float amp, float freq, float dur, float phase = 0.0f, unsigned int rate = 44100)
			: generator(amp, freq, dur, phase, rate), power(power){}

			float gen() override
			{
				const float sample = m_amplitude * wavlib::powersine(m_angle, power);
				m_angle += m_offset;
				return sample;
			}
		};
	}
}

