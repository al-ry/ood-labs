#pragma once
#include "Observer.h"
#include <algorithm>
#include <climits>
#include <iostream>
#include <memory>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

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

class CWeatherDataOutside: public CObservable<SWeatherInfoPro>
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

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure, double speed, double direction)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		m_wind.speed = speed;
		m_wind.direction = direction;

		MeasurementsChanged();
	}

protected:
	SWeatherInfoPro GetChangedData() const override
	{
		SWeatherInfoPro info;
		info.basicInfo.temperature = GetTemperature();
		info.basicInfo.humidity = GetHumidity();
		info.basicInfo.pressure = GetPressure();
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

class CWeatherDataInside : public CObservable<SWeatherInfo>
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

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}

protected:
	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		return info;
	}

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};

class COutsideWeatherDisplay : public IObserver<SWeatherInfoPro>
{
private:
	void Update(SWeatherInfoPro const& data) override
	{
		std::cout << "------------Current weather outside----------------\n";
		std::cout << "Current Temp " << data.basicInfo.temperature << std::endl;
		std::cout << "Current Hum " << data.basicInfo.humidity << std::endl;
		std::cout << "Current Pressure " << data.basicInfo.pressure << std::endl;
		std::cout << "Current Wind speed " << data.wind.speed << std::endl;
		std::cout << "Current Wind direction " << data.wind.direction << std::endl;
		std::cout << "------------Current weather outside----------------\n";
	}
};

class CInsideWeatherDisplay : public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "------------Current weather inside----------------\n";
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "------------Current weather inside----------------\n";
	}
};

class IStatisticCalculator
{
public:
	virtual void UpdateStatistic(double value) = 0;
	virtual void PrintStatistic(const std::string& name) = 0;

	virtual ~IStatisticCalculator() = default;
};

class CStatCalculator: public IStatisticCalculator
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

class CStatOutsideDisplay : public IObserver<SWeatherInfoPro>
{
private:
	void Update(SWeatherInfoPro const& data) override
	{
		m_outsideStatistic.temperatureStat.UpdateStatistic(data.basicInfo.temperature);
		m_outsideStatistic.humidityStat.UpdateStatistic(data.basicInfo.humidity);
		m_outsideStatistic.pressureStat.UpdateStatistic(data.basicInfo.pressure);
		m_outsideStatistic.windSpeedStat.UpdateStatistic(data.wind.speed);
		m_outsideStatistic.windDirectionStat.UpdateStatistic(data.wind.direction);
		PrintStatistic();
	}
	void PrintStatistic()
	{
		std::cout << "------------Statisitic weather outside----------------\n";
		m_outsideStatistic.temperatureStat.PrintStatistic("temperature");
		m_outsideStatistic.humidityStat.PrintStatistic("humidity");
		m_outsideStatistic.pressureStat.PrintStatistic("pressure");
		m_outsideStatistic.windSpeedStat.PrintStatistic("wind speed");
		m_outsideStatistic.windDirectionStat.PrintStatistic("wind direction");
		std::cout << "------------Statisitic weather outside----------------\n";
	}

private:
	SWeatherStatisticPro m_outsideStatistic;
};

class CStatInsideDisplay : public IObserver<SWeatherInfo>
{

private:
	void Update(SWeatherInfo const& data) override
	{
		m_insideStatistic.temperatureStat.UpdateStatistic(data.temperature);
		m_insideStatistic.humidityStat.UpdateStatistic(data.humidity);
		m_insideStatistic.pressureStat.UpdateStatistic(data.pressure);
		PrintStatistic();
	}
private:
	void PrintStatistic()
	{
		std::cout << "------------Statisitic weather inside----------------\n";
		m_insideStatistic.temperatureStat.PrintStatistic("temperature");
		m_insideStatistic.humidityStat.PrintStatistic("humidity");
		m_insideStatistic.pressureStat.PrintStatistic("pressure");
		std::cout << "------------Statisitic weather inside----------------\n";
	}
private:
	SWeatherStatistic m_insideStatistic;
};
