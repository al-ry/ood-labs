#pragma once
#include <boost/signals2.hpp>
#include <iostream>
#include <functional>
#define _USE_MATH_DEFINES
#include <math.h>
#include <optional>
using Connection = boost::signals2::connection;
using ScopedConnection = boost::signals2::scoped_connection;


namespace ph = std::placeholders;
struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

struct SWindInfo
{
	double speed = 0;
	double direction = 0;
};

struct SWeatherInfoPro
{
	SWeatherInfo basicInfo;
	SWindInfo wind;
};

struct SOutsideWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	double windSpeed = 0;
	double windDirection = 0;
};

class COutsideWeatherData
{
public:
	using TemperatureChangeSignal = boost::signals2::signal<void(double temperature)>;
	using HumidityChangeSignal = boost::signals2::signal<void(double humidity)>;
	using PressureChangeSignal = boost::signals2::signal<void(double pressure)>;
	using WindSpeedChangeSignal = boost::signals2::signal<void(double windSpeed)>;
	using WindDirectionChangeSignal = boost::signals2::signal<void(double windDirection)>;

	Connection DoOnTemperatureChange(const TemperatureChangeSignal::slot_type& slot)
	{
		return m_temperatureChangeSignal.connect(slot);
	}
	Connection DoOnHumidityChange(const HumidityChangeSignal::slot_type& slot)
	{
		return m_humidityChangeSignal.connect(slot);
	}
	Connection DoOnPressureChange(const PressureChangeSignal::slot_type& slot)
	{
		return m_pressureChangeSignal.connect(slot);
	}
	Connection DoOnWindSpeedChange(const WindSpeedChangeSignal::slot_type& slot)
	{
		return m_windSpeedChangeSignal.connect(slot);
	}
	Connection DoOnWindDirectionChange(const WindDirectionChangeSignal::slot_type& slot)
	{
		return m_windDirectionChangeSignal.connect(slot);
	}

	void SetMeasurements(double temperature, double humidity, double pressure, double windSpeed, double windDirection)
	{
		if (m_temperature != temperature)
		{
			m_temperature = temperature;
			m_temperatureChangeSignal(temperature);
		}

		if (m_humidity != humidity)
		{
			m_humidity = humidity;
			m_humidityChangeSignal(humidity);
		}

		if (m_pressure != pressure)
		{
			m_pressure = pressure;
			m_pressureChangeSignal(pressure);
		}

		if (m_windSpeed != windSpeed)
		{
			m_windSpeed = windSpeed;
			m_windSpeedChangeSignal(windSpeed);
		}

		if (m_windDirection != windDirection)
		{
			m_windDirection = windDirection;
			m_windDirectionChangeSignal(windDirection);
		}
	}

private:
	double m_temperature = 0;
	double m_humidity = 0;
	double m_pressure = 0;
	double m_windSpeed = 0;
	double m_windDirection = 0;

	TemperatureChangeSignal m_temperatureChangeSignal;
	HumidityChangeSignal m_humidityChangeSignal;
	PressureChangeSignal m_pressureChangeSignal;
	WindSpeedChangeSignal m_windSpeedChangeSignal;
	WindDirectionChangeSignal m_windDirectionChangeSignal;
};

class CInsideWeatherData
{
public:
	using TemperatureChangeSignal = boost::signals2::signal<void(double temperature)>;
	using HumidityChangeSignal = boost::signals2::signal<void(double humidity)>;
	using PressureChangeSignal = boost::signals2::signal<void(double pressure)>;

	Connection DoOnTemperatureChange(const TemperatureChangeSignal::slot_type& slot)
	{
		return m_temperatureChangeSignal.connect(slot);
	}
	Connection DoOnHumidityChange(const HumidityChangeSignal::slot_type& slot)
	{
		return m_humidityChangeSignal.connect(slot);
	}
	Connection DoOnPressureChange(const PressureChangeSignal::slot_type& slot)
	{
		return m_pressureChangeSignal.connect(slot);
	}

	void SetMeasurements(double temperature, double humidity, double pressure)
	{
		if (m_temperature != temperature)
		{
			m_temperature = temperature;
			m_temperatureChangeSignal(temperature);
		}

		if (m_humidity != humidity)
		{
			m_humidity = humidity;
			m_humidityChangeSignal(humidity);
		}

		if (m_pressure != pressure)
		{
			m_pressure = pressure;
			m_pressureChangeSignal(pressure);
		}
	}

private:
	double m_temperature = 0;
	double m_humidity = 0;
	double m_pressure = 0;

	TemperatureChangeSignal m_temperatureChangeSignal;
	HumidityChangeSignal m_humidityChangeSignal;
	PressureChangeSignal m_pressureChangeSignal;
};

class IStatisticCalculator
{
public:
	virtual void UpdateStatistic(double value) = 0;
	virtual ~IStatisticCalculator() = default;
};

class CStatCalculator : public IStatisticCalculator
{
public:
	CStatCalculator() = default;
	void UpdateStatistic(double data) override
	{
		if (m_min > data)
		{
			m_min = data;
		}
		if (m_max < data)
		{
			m_max = data;
		}
		m_acc += data;
		++m_countAcc;
	}
	std::optional<double> GetMaxValue() const
	{
		if (m_max == -std::numeric_limits<double>::infinity())
		{
			return std::nullopt;
		}
		return m_max;
	}
	std::optional<double> GetMinValue() const
	{
		if (m_min == std::numeric_limits<double>::infinity())
		{
			return std::nullopt;
		}
		return m_min;
	}
	std::optional<double> GetAverageValue() const
	{
		double avg = m_acc / m_countAcc;
		if (m_countAcc == 0)
		{
			return std::nullopt;
		}
		return m_acc / m_countAcc;
	}

private:
	std::optional<double> m_min = std::numeric_limits<double>::infinity();
	std::optional<double> m_max = -std::numeric_limits<double>::infinity();
	double m_acc = 0;
	unsigned m_countAcc = 0;
};

class CDirectionStatCalculator : public IStatisticCalculator
{
public:
	void UpdateStatistic(double value)
	{
		m_x += std::cos(value * M_PI / 180);
		m_y += std::sin(value * M_PI / 180);
		double avg = std::atan2(m_y, m_x) * 180 / M_PI;
		if (avg >= 0)
		{
			m_average = avg;
		}
		else
		{
			m_average = avg + 360;
		}
	}
	double GetAverageDirection() const
	{
		return m_average;
	}

private:
	double m_x = 0;
	double m_y = 0;
	double m_average = 0;
};

struct SWeatherStatistic
{
	CStatCalculator temperatureStat;
	CStatCalculator humidityStat;
	CStatCalculator pressureStat;
};

struct SWeatherStatisticPro
{
	CStatCalculator temperatureStat;
	CStatCalculator humidityStat;
	CStatCalculator pressureStat;
	CStatCalculator windSpeedStat;
	CDirectionStatCalculator windDirectionStat;
};


class COutsideStatDisplay
{
public:
	COutsideStatDisplay(COutsideWeatherData& outerStation)
	{
		m_temperatureChangeConnection = outerStation.DoOnTemperatureChange([this](double value) {
			m_outerStatistic.temperatureStat.UpdateStatistic(value);
			PrintOuterStatistic();
		});
		m_humidityChangeConnection = outerStation.DoOnHumidityChange([this](double value) {
			m_outerStatistic.humidityStat.UpdateStatistic(value);
			PrintOuterStatistic();
		});
		m_pressureChangeConnection = outerStation.DoOnPressureChange([this](double value) {
			m_outerStatistic.pressureStat.UpdateStatistic(value);
			PrintOuterStatistic();
		});
		m_windSpeedChangeConnection = outerStation.DoOnWindSpeedChange([this](double value) {
			m_outerStatistic.windSpeedStat.UpdateStatistic(value);
			PrintOuterStatistic();
		});
		m_windDirectionChangeConnection = outerStation.DoOnWindDirectionChange([this](double value) {
			m_outerStatistic.windDirectionStat.UpdateStatistic(value);
			PrintOuterStatistic();
		});
	}

private:
	void CalculateOuterStatistic(const SWeatherInfoPro& outerInfo)
	{
		m_outerStatistic.temperatureStat.UpdateStatistic(outerInfo.basicInfo.temperature);
		m_outerStatistic.humidityStat.UpdateStatistic(outerInfo.basicInfo.humidity);
		m_outerStatistic.pressureStat.UpdateStatistic(outerInfo.basicInfo.pressure);
		m_outerStatistic.windSpeedStat.UpdateStatistic(outerInfo.wind.speed);
		m_outerStatistic.windDirectionStat.UpdateStatistic(outerInfo.wind.direction);
	}
	void PrintOuterStatistic()
	{
		std::cout << "------------Statisitic weather outside----------------\n";
		PrintSpecificStatistic("temperature", m_outerStatistic.temperatureStat);
		PrintSpecificStatistic("humidity", m_outerStatistic.humidityStat);
		PrintSpecificStatistic("pressure", m_outerStatistic.pressureStat);
		PrintSpecificStatistic("wind speed", m_outerStatistic.windSpeedStat);
		PrintWindDirectionStatistic("wind direction", m_outerStatistic.windDirectionStat);
		std::cout << "------------Statisitic weather outside----------------\n";
	}
	void PrintSpecificStatistic(const std::string name, const CStatCalculator& value)
	{
			std::cout << "Max " << name << " " << (value.GetMaxValue().has_value() ? std::to_string(value.GetMaxValue().value()) : "-")  << std::endl;
			std::cout << "Min " << name << " " << (value.GetMinValue().has_value() ? std::to_string(value.GetMinValue().value()) : "-") << std::endl;
			std::cout << "Average " << name << " " << (value.GetAverageValue().has_value() ? std::to_string(value.GetAverageValue().value()) : "-") << "" << std::endl;
			std::cout << "----------------" << std::endl;
	}
	void PrintWindDirectionStatistic(const std::string name, const CDirectionStatCalculator& value)
	{
		std::cout << "Average " << name << " " << value.GetAverageDirection() << "" << std::endl;
		std::cout << "----------------" << std::endl;
	}

private:

	ScopedConnection m_temperatureChangeConnection;
	ScopedConnection m_humidityChangeConnection;
	ScopedConnection m_pressureChangeConnection;
	ScopedConnection m_windSpeedChangeConnection;
	ScopedConnection m_windDirectionChangeConnection;

	SWeatherStatisticPro m_outerStatistic;
};

class CInsideStatDisplay
{
public:
	CInsideStatDisplay(CInsideWeatherData& innerStation)
	{
		m_temperatureChangeConnection = innerStation.DoOnTemperatureChange([this](double value) {
			m_innerStatistic.temperatureStat.UpdateStatistic(value);
			PrintInnerStatistic();
		});
		m_humidityChangeConnection = innerStation.DoOnHumidityChange([this](double value) {
			m_innerStatistic.humidityStat.UpdateStatistic(value);
			PrintInnerStatistic();
		});
		m_pressureChangeConnection = innerStation.DoOnPressureChange([this](double value) {
			m_innerStatistic.pressureStat.UpdateStatistic(value);
			PrintInnerStatistic();
		});
	}

private:

	void PrintInnerStatistic()
	{
		std::cout << "------------Statisitic weather inside----------------\n";
		PrintSpecificStatistic("temperature", m_innerStatistic.temperatureStat);
		PrintSpecificStatistic("humidity", m_innerStatistic.humidityStat);
		PrintSpecificStatistic("pressure", m_innerStatistic.pressureStat);
		std::cout << "------------Statisitic weather inside----------------\n";
	}

	void PrintSpecificStatistic(const std::string name, const CStatCalculator& value)
	{
		std::cout << "Max " << name << " " << (value.GetMaxValue().has_value() ? std::to_string(value.GetMaxValue().value()) : "-") << std::endl;
		std::cout << "Min " << name << " " << (value.GetMinValue().has_value() ? std::to_string(value.GetMinValue().value()) : "-") << std::endl;
		std::cout << "Average " << name << " " << (value.GetAverageValue().has_value() ? std::to_string(value.GetAverageValue().value()) : "-") << "" << std::endl;
		std::cout << "----------------" << std::endl;
	}



	ScopedConnection m_temperatureChangeConnection;
	ScopedConnection m_humidityChangeConnection;
	ScopedConnection m_pressureChangeConnection;

	SWeatherStatistic m_innerStatistic;
};


