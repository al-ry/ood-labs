#include "stdafx.h"

#include "../WeatherStationDuo/WeatherData.h"
#include "../WeatherStationDuo/Observer.h"
#include <boost\test\tools\output_test_stream.hpp>


struct DuoWeatherData
{
	CWeatherData in;
	CWeatherData out;
};

class CTestDisplay : public IObserver<SWeatherInfo>
{
public:
	CTestDisplay(CWeatherData& in, CWeatherData& out, boost::test_tools::output_test_stream& stream)
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
	boost::test_tools::output_test_stream& m_stream;
};

BOOST_FIXTURE_TEST_SUITE(Test_two_subjects, DuoWeatherData)
	BOOST_AUTO_TEST_CASE(when_there_are_two_subject_should_define_type_of_notification)
	{
		boost::test_tools::output_test_stream stream;
		CTestDisplay display(in, out, stream);
		
		in.RegisterObserver(display, 1);
		out.RegisterObserver(display, 1);

		in.SetMeasurements(5, 5, 5);
		out.SetMeasurements(5, 5, 5);

		out.RemoveObserver(display);
		BOOST_CHECK(stream.is_equal("Echo from in\nEcho from out\n"));

		stream.flush();
		CTestDisplay display2(in, out, stream);
		in.RegisterObserver(display2, 3);
		out.RegisterObserver(display2, 3);

		in.SetMeasurements(5, 5, 5);
		out.SetMeasurements(5, 5, 5);

		BOOST_CHECK(stream.is_equal("Echo from in\nEcho from in\nEcho from out\n"));
	}
BOOST_AUTO_TEST_SUITE_END()