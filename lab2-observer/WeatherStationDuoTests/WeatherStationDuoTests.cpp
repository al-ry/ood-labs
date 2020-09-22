#include "stdafx.h"

#include "../WeatherStationDuo/WeatherData.h"
#include "../WeatherStationDuo/Observer.h"

struct DuoWeatherData
{
	CWeatherData in;
	CWeatherData out;
};

class CTestDisplay : public IObserver<SWeatherInfo>
{
public:
	CTestDisplay(CWeatherData& in, CWeatherData& out, std::stringstream& stream)
		: m_outerIndicator(out)
		, m_innerIndicator(in)
		, m_stream(stream)
	{
	}

private:
	void Update(SWeatherInfo const& data, const IObservable<SWeatherInfo>& indicator) override
	{
		if (std::addressof(indicator) == std::addressof(m_outerIndicator))
		{
			m_stream << "Echo from out\n";
		}
		else if (std::addressof(indicator) == std::addressof(m_innerIndicator))
		{
			m_stream << "Echo from in\n";
		}
	};

private:
	CWeatherData& m_outerIndicator;
	CWeatherData& m_innerIndicator;
	std::stringstream& m_stream;
};

BOOST_FIXTURE_TEST_SUITE(Test_two_subjects, DuoWeatherData)
	BOOST_AUTO_TEST_CASE(when_there_are_two_subject_should_define_type_of_notification)
	{
		std::stringstream stream;
		CTestDisplay display(in, out, stream);
		
		in.RegisterObserver(display, 1);
		out.RegisterObserver(display, 1);

		in.SetMeasurements(5, 5, 5);
		out.SetMeasurements(5, 5, 5);

		out.RemoveObserver(display);
		BOOST_CHECK_EQUAL(stream.str(), "Echo from in\nEcho from out\n");

		stream.str("");
		CTestDisplay display2(in, out, stream);
		in.RegisterObserver(display2, 3);
		out.RegisterObserver(display2, 3);

		in.SetMeasurements(5, 5, 5);
		out.SetMeasurements(5, 5, 5);

		BOOST_CHECK(stream.str() == "Echo from in\nEcho from in\nEcho from out\n");
	}
BOOST_AUTO_TEST_SUITE_END()