#include "generator.h"
#include <wavmath.h>
#include <algorithm>


wavlib::generators::generator::generator(float amp, float freq, float dur, float phase, unsigned int rate)
	: m_amplitude(amp), m_frequency(freq), m_duration(dur), m_phase(phase), m_sample_rate(rate), m_num_samples(0)
{
	m_num_samples = static_cast<unsigned int>(static_cast<float>(m_sample_rate) * m_duration);
	m_angle = 0.0f;
	m_offset = (2 * static_cast<float>(S_PI) * m_frequency + m_phase) / static_cast<float>(m_sample_rate);
}

wavlib::wav wavlib::generators::generator::towav()
{
	std::vector<int16_t> samples;
	for (int i = 0; i < static_cast<int>(m_num_samples); i ++)
	{
		const float sample = gen();
		auto intsample = static_cast<int16_t>(sample * INT16_MAX);
		intsample = std::clamp(intsample, (int16_t)INT16_MIN, (int16_t)INT16_MAX);
		samples.push_back(intsample);
	}
	const char* const p_data = (char*)samples.data();
	const int size = 2 * static_cast<int>(samples.size());
	wav output(1, m_sample_rate, 16, std::vector(p_data, p_data + size));
	return output;
}
