#include "stdafx.h"
#include "../WeatherStationProWithSignals/WeatherData.h"
#include <boost\test\tools\output_test_stream.hpp>

struct DuoWeatherData
{
	CInsideWeatherData in;
	COutsideWeatherData out;
};

class CTestDisplay
{
public:
	CTestDisplay(COutsideWeatherData& out, std::stringstream& stream)
		: m_stream(stream)
	{
		m_temperatureChangeConnection = out.DoOnTemperatureChange([this](double val) {
			m_stream << "temp\n";
		});
		m_humidityChangeConnection = out.DoOnHumidityChange([this](double val) {
			m_stream << "hum\n";
		});
		m_pressureChangeConnection = out.DoOnPressureChange([this](double val) {
			m_stream << "pres\n";
		});
		m_windDirectionChangeConnection = out.DoOnWindDirectionChange([this](double val) {
			m_stream << "dir\n";
		});
		m_windSpeedChangeConnection = out.DoOnWindSpeedChange([this](double val) {
			m_stream << "speed\n";
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
	ScopedConnection m_temperatureChangeConnection;
	ScopedConnection m_humidityChangeConnection;
	ScopedConnection m_pressureChangeConnection;
	ScopedConnection m_windSpeedChangeConnection;
	ScopedConnection m_windDirectionChangeConnection;

	std::stringstream& m_stream;
};


BOOST_FIXTURE_TEST_SUITE(Test_duo_pro_with_signals, DuoWeatherData)
	BOOST_AUTO_TEST_CASE(test_signals)
	{
		std::stringstream stream;
		CTestDisplay display(out, stream);

		out.SetMeasurements(1,1,1,1,1);
		BOOST_CHECK_EQUAL(stream.str(), "temp\nhum\npres\nspeed\ndir\n");


		stream.str("");
		out.SetMeasurements(1, 2, 1, 1, 2);
		BOOST_CHECK_EQUAL(stream.str(), "hum\ndir\n");
	}
BOOST_AUTO_TEST_SUITE_END()