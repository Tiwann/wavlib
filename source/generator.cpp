#include "generator.h"
#include <algorithm>

wavlib::generators::generator::generator(float amp, float freq, float dur, float phase, unsigned int rate)
	: m_amplitude(amp), m_frequency(freq), m_duration(dur), m_phase(phase), m_sample_rate(rate), m_num_samples(0)
{
	m_num_samples = static_cast<unsigned int>(static_cast<float>(m_sample_rate) * m_duration);
	angle = 0.0f;
	offset = (2 * static_cast<float>(_PI) * m_frequency + m_phase) / static_cast<float>(m_sample_rate);
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
	std::vector<char> raw_samples(samples.size() * sizeof(int16_t));
	std::memcpy(raw_samples.data(), samples.data(), samples.size() * sizeof(int16_t));
	wav output(1, m_sample_rate, 16, raw_samples);
	output.header.size = 36 + m_num_samples * sizeof(int16_t);
	output.fmt.format = 1;
	output.data.num_frames = m_num_samples;
	output.data.size = m_num_samples * output.channels() * output.bit_depth() / 8;

	return output;
}
