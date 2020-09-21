#include "stdafx.h"
#include "../WeatherStationProWithSignals/WeatherData.h"
#include <boost\test\tools\output_test_stream.hpp>

struct DuoWeatherData
{
	CWeatherData<SWeatherInfo> in;
	CWeatherData<SWeatherInfoPro> out;
};

class CTestDisplay
{
public:
	CTestDisplay(CWeatherData<SWeatherInfo>& in, CWeatherData<SWeatherInfoPro>& out, boost::test_tools::output_test_stream& stream)
		: m_stream(stream)
	{
		m_innerConnection = in.DoOnWeatherChange([this](const SWeatherInfo& innerInfo) {
			UpdateInside();
		});
		m_outerConnection = out.DoOnWeatherChange([this](const SWeatherInfoPro& innerInfo) {
			UpdateOutside();
		});
	}

private:
	void UpdateOutside()
	{
		m_stream << "Outside updated\n";
	};
	void UpdateInside()
	{
		m_stream << "Inside updated\n";
	}
	
private:
	ScopedConnection m_innerConnection;
	ScopedConnection m_outerConnection;

	boost::test_tools::output_test_stream& m_stream;
};


BOOST_FIXTURE_TEST_SUITE(Test_duo_pro_with_signals, DuoWeatherData)
	BOOST_AUTO_TEST_CASE(test_signals)
	{
		boost::test_tools::output_test_stream stream;
		CTestDisplay display(in, out, stream);

		in.SetMeasurements({ 5, 5, 5 });
		out.SetMeasurements({ 5, 5, 5, 8, 8 });
		BOOST_CHECK(stream.is_equal("Inside updated\nOutside updated\n"));

		stream.flush();

		out.SetMeasurements({ 5, 5, 5, 5, 5});
		in.SetMeasurements({ 7, 7, 7 });

		BOOST_CHECK(stream.is_equal("Outside updated\nInside updated\n"));
		stream.flush();

		out.SetMeasurements({ 5, 5, 7, 5, 5 });
		out.SetMeasurements({ 5, 5, 5, 0, 5 });
		BOOST_CHECK(stream.is_equal("Outside updated\nOutside updated\n"));

		stream.flush();
		in.SetMeasurements({ 5, 5, 7});
		in.SetMeasurements({ 5, 5, 5});
		BOOST_CHECK(stream.is_equal("Inside updated\nInside updated\n"));

		stream.flush();
		in.SetMeasurements({ 5, 5, 5 });
		BOOST_CHECK(stream.is_equal(""));
	}
BOOST_AUTO_TEST_SUITE_END()