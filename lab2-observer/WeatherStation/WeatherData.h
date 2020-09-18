#pragma once

#include "Observer.h"
#include <algorithm>
#include <climits>
#include <iostream>
#include <memory>
#include <vector>

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

class CDisplay : public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class CStatCalculator
{
public:
	CStatCalculator() = default;
	void Update(double data)
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
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data) override
	{
		m_weatherStatistic.temperatureStat.Update(data.temperature);
		m_weatherStatistic.humidityStat.Update(data.humidity);
		m_weatherStatistic.pressureStat.Update(data.pressure);
		PrintStatistic(m_weatherStatistic);
	}

private:
	void PrintStatistic(const SWeatherStatistic& weatherStatistic)
	{
		PrintSpecificStatistic(weatherStatistic.temperatureStat, "temperature");
		PrintSpecificStatistic(weatherStatistic.humidityStat, "humidity");
		PrintSpecificStatistic(weatherStatistic.pressureStat, "pressure");
		std::cout << "----------------" << std::endl;
	}
	void PrintSpecificStatistic(const CStatCalculator& weatherStatistic, const std::string& name)
	{
		std::cout << "Max " << name << " " << weatherStatistic.GetMaxValue() << std::endl;
		std::cout << "Min " << name << " " << weatherStatistic.GetMinValue() << std::endl;
		std::cout << "Average " << name << " " << weatherStatistic.GetAverageValue() << "" << std::endl;
		std::cout << "----------------" << std::endl;
	}

private:
	SWeatherStatistic m_weatherStatistic;
};

class CWeatherData : public CObservable<SWeatherInfo>
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