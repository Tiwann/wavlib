#include "generator.h"
#include <algorithm>

wavlib::generators::generator::generator(float amp, float freq, float dur, float phase, unsigned int rate)
	: m_amplitude(amp), m_frequency(freq), m_duration(dur), m_phase(phase), m_sample_rate(rate), m_num_samples(0)
{
	m_num_samples = m_sample_rate * static_cast<unsigned int>(m_duration);
	angle = 0.0f;
	offset = (2 * static_cast<float>(_PI) * m_frequency + m_phase) / static_cast<float>(m_sample_rate);
}

wavlib::wav wavlib::generators::generator::towav()
{
	const int16_t max = static_cast<int16_t>(std::pow(2, 16) - 1);
	const int16_t min = -max - 1;
	std::vector<char> samples;
	samples.reserve(m_num_samples * sizeof(int16_t));
	for (int i = 0; i < static_cast<int>(m_num_samples); i += sizeof(int16_t))
	{
		const float sample = gen();
		int16_t intsample = static_cast<int16_t>(sample) * static_cast<int16_t>(std::pow(2, 16) - 1);
		intsample = std::clamp(intsample, min, max);
		std::memcpy(&samples[i], &intsample, sizeof(int16_t));
	}
	wav output(1, m_sample_rate, 16, samples);
	return output;
}
