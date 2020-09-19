#pragma once
#include "Observer.h"
#include <algorithm>
#include <climits>
#include <iostream>
#include <memory>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

enum class WeatherEvent
{
	Temperature,
	Humidity,
	Pressure,
	WindSpeed,
	WindDirection
};


struct SWindInfo
{
	double speed = 0;
	double direction = 0;
};

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	SWindInfo wind;
};

class CDisplay : public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "------------Current----------------\n";
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "Current Wind speed " << data.wind.speed << std::endl;
		std::cout << "Current Wind direction " << data.wind.direction << std::endl;
		std::cout << "------------Current----------------\n";
	}
};

class IStatisticCalculator
{
public:
	virtual void UpdateStatistic(double value) = 0;
	virtual void PrintStatistic(const std::string& name) = 0;

	virtual ~IStatisticCalculator() = default;
};
class CDirectionStatCalculator : public IStatisticCalculator
{
public:
	void UpdateStatistic(double value) override
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
	void PrintStatistic(const std::string& name) override
	{
		std::cout << "Average " << name << " " << m_average << std::endl;
		std::cout << "----------------" << std::endl;
	}

private:
	double m_x = 0;
	double m_y = 0;
	double m_average = 0;
};

class CStatCalculator : public IStatisticCalculator
{
public:
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
	void PrintStatistic(const std::string& name) override
	{
		std::cout << "Max " << name << " " << GetMaxValue() << std::endl;
		std::cout << "Min " << name << " " << GetMinValue() << std::endl;
		std::cout << "Average " << name << " " << GetAverageValue() << "" << std::endl;
		std::cout << "----------------" << std::endl;
	}
	double GetMaxValue() const
	{
		return m_max;
	}
	double GetMinValue() const
	{
		return m_min;
	}
	double GetAverageValue() const
	{
		return m_acc / m_countAcc;
	}

private:
	std::string m_statisticType;
	double m_min = std::numeric_limits<double>::infinity();
	double m_max = -std::numeric_limits<double>::infinity();
	double m_acc = 0;
	unsigned m_countAcc = 0;
};

struct SWeatherStatistic
{
	CStatCalculator temperatureStat;
	CStatCalculator humidityStat;
	CStatCalculator pressureStat;
	CStatCalculator windSpeedStat;
	CDirectionStatCalculator windDirectionStat;
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data) override
	{
		m_weatherStatistic.temperatureStat.UpdateStatistic(data.temperature);
		m_weatherStatistic.humidityStat.UpdateStatistic(data.humidity);
		m_weatherStatistic.pressureStat.UpdateStatistic(data.pressure);
		m_weatherStatistic.windSpeedStat.UpdateStatistic(data.wind.speed);
		m_weatherStatistic.windDirectionStat.UpdateStatistic(data.wind.direction);
		PrintStatistic();
	}

private:
	void PrintStatistic()
	{
		std::cout << "------------Statistic----------------\n";
		m_weatherStatistic.temperatureStat.PrintStatistic("temperature");
		m_weatherStatistic.humidityStat.PrintStatistic("humidity");
		m_weatherStatistic.pressureStat.PrintStatistic("pressure");
		m_weatherStatistic.windSpeedStat.PrintStatistic("wind speed");
		m_weatherStatistic.windDirectionStat.PrintStatistic("wind direction");
		std::cout << "------------Statistic----------------\n";
	}

private:
	SWeatherStatistic m_weatherStatistic;
};

class CWeatherData : public CObservable<SWeatherInfo, WeatherEvent>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature() const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity() const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure() const
	{
		return m_pressure;
	}

	double GetWindSpeed() const
	{
		return m_wind.speed;
	}

	double GetWindDirection() const
	{
		return m_wind.direction;
	}

	void MeasurementsChanged(const std::set<WeatherEvent>& changedEvents)
	{
		NotifyObservers(changedEvents);
	}

	void SetMeasurements(double temp, double humidity, double pressure, double windSpeed, double windDirection)
	{
		std::set<WeatherEvent> changedEvents;
		if (m_humidity != humidity)
		{
			m_humidity = humidity;
			changedEvents.emplace(WeatherEvent::Humidity);
		}
		if (m_temperature != temp)
		{
			m_temperature = temp;
			changedEvents.emplace(WeatherEvent::Temperature);
		}
		if (m_pressure != pressure)
		{
			m_pressure = pressure;
			changedEvents.emplace(WeatherEvent::Temperature);
		}
		if (m_wind.speed != windSpeed)
		{
			m_wind.speed = windSpeed;
			changedEvents.emplace(WeatherEvent::WindSpeed);
		}
		if (m_wind.direction != windDirection)
		{
			m_wind.direction = windDirection;
			changedEvents.emplace(WeatherEvent::WindDirection);
		}
		MeasurementsChanged(changedEvents);
	}

protected:
	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.wind.speed = GetWindSpeed();
		info.wind.direction = GetWindDirection();
		return info;
	}

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	SWindInfo m_wind;
};