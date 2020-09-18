#include "stdafx.h"
#include "../WeatherStation/WeatherData.h"
#include "../WeatherStation/Observer.h"
#include <boost\test\tools\output_test_stream.hpp>


class CTestDisplay : public IObserver<SWeatherInfo>
{
public:
	CTestDisplay(boost::test_tools::output_test_stream& stream)
		: m_stream(stream)
	{
	}

private:
	void Update(const SWeatherInfo& data) override
	{
		m_stream << "TestDisplay info\n";
	}
	boost::test_tools::output_test_stream& m_stream;
};


class CTestStatDisplay : public IObserver<SWeatherInfo>
{
public:
	CTestStatDisplay(boost::test_tools::output_test_stream& stream)
		: m_stream(stream)
	{
	}

private:
	void Update(const SWeatherInfo& data) override
	{
		m_stream << "TestStatDisplay info\n";
	}
	boost::test_tools::output_test_stream& m_stream;
};

struct WeatherData
{
	CWeatherData wd;
	boost::test_tools::output_test_stream stream;
};

struct WithDisplays : WeatherData
{
	CTestDisplay display;
	CTestStatDisplay statDisplay;
	WithDisplays()
		: display(stream)
		, statDisplay(stream)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Test_observers_priority, WithDisplays)
	BOOST_AUTO_TEST_CASE(when_priority_is_set_should_print_info_in_appropiate_order)
	{
	wd.RegisterObserver(display, 1);
	wd.RegisterObserver(statDisplay, 10);
	wd.SetMeasurements(18, 0.4, 766);
	BOOST_CHECK_EQUAL(stream.str(), "TestStatDisplay info\nTestDisplay info\n");

	stream.flush();
	wd.RemoveObserver(statDisplay);
	wd.SetMeasurements(18, 0.4, 764);
	BOOST_CHECK(stream.is_equal("TestDisplay info\n"));

	stream.flush();
	wd.RegisterObserver(statDisplay, 0);
	wd.SetMeasurements(20, 0.8, 765);
	BOOST_CHECK_EQUAL(stream.str(), "TestDisplay info\nTestStatDisplay info\n");
}

BOOST_AUTO_TEST_SUITE_END()