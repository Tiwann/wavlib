#include "generator.h"

wavlib::generators::generator::generator(float amp, float freq, float dur, float phase, unsigned int rate)
	: m_amplitude(amp), m_frequency(freq), m_duration(dur), m_phase(phase), m_sample_rate(rate), m_num_samples(0)
{
	m_num_samples = m_sample_rate * static_cast<unsigned int>(m_duration);
	angle = 0.0f;
	offset = (2 * static_cast<float>(_PI) * m_frequency + m_phase) / static_cast<float>(m_sample_rate);
}

wavlib::wav wavlib::generators::generator::towav()
{
	wav output;
	output.setformat(wav_fmt(
		
	));
	std::vector<int32_t> samples;
	samples.reserve(m_num_samples);
	
	for (int i = 0; i < static_cast<int>(m_num_samples); i++)
	{
		const float sample = gen();
		int32_t intsample = static_cast<int32_t>(sample) * static_cast<int32_t>(std::pow(2, 32) - 1);
		intsample = std::
		samples.push_back();
	}
	output.setdata(samples);
	return output;
}
