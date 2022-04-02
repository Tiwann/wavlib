#include "generator.h"

wavlib::generators::generator::generator(float amp, float freq, float dur, float phase, unsigned int rate)
	: m_amplitude(amp), m_frequency(freq), m_duration(dur), m_phase(phase), m_sample_rate(rate), m_num_samples(0)
{
	m_num_samples = m_sample_rate * m_duration;
	angle = 0.0f;
	offset = (2 * _PI * m_frequency + m_phase) / m_sample_rate;
}

wavlib::wav wavlib::generators::generator::towav()
{
	wav output(1, m_sample_rate, 16, m_num_samples);
	std::vector<float> samples;
	for (int i = 0; i < m_num_samples; i++)
	{
		samples.push_back(gen());
	}
	output.setdata(samples);
	return output;
}
