#pragma once
#include "SignallingValue.h"
#include <iostream>
#include <functional>
#define _USE_MATH_DEFINES
#include <math.h>

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

bool operator==(const SWeatherInfoPro& firstOp, const SWeatherInfoPro& secondOp)
{
	return firstOp.basicInfo.humidity == secondOp.basicInfo.humidity
		&& firstOp.basicInfo.pressure == secondOp.basicInfo.pressure
		&& firstOp.basicInfo.temperature == secondOp.basicInfo.temperature
		&& firstOp.wind.direction == secondOp.wind.direction
		&& firstOp.wind.speed == secondOp.wind.speed;
}


bool operator!=(const SWeatherInfoPro& firstOp, const SWeatherInfoPro& secondOp)
{
	return !(firstOp == secondOp);
}

bool operator==(const SWeatherInfo& firstOp, const SWeatherInfo& secondOp)
{
	return firstOp.humidity == secondOp.humidity
		&& firstOp.pressure == secondOp.pressure
		&& firstOp.temperature == secondOp.temperature;
}
bool operator!=(const SWeatherInfo& firstOp, const SWeatherInfo& secondOp)
{
	return !(firstOp == secondOp);
}


template <typename WeatherInfo>
class CWeatherData
{
	using WeatherSignal = Signal<void(const WeatherInfo& data)>;
public:
	CWeatherData() = default;
	void SetMeasurements(const WeatherInfo& data)
	{
		m_signallingValue = data;
	}

	Connection DoOnWeatherChange(typename const WeatherSignal::slot_type& slot)
	{
		return m_signallingValue.Connect1(slot, false);
	}

private:
	SignallingValue<WeatherInfo> m_signallingValue;
};

class IStatisticCalculator
{
public:
	virtual void UpdateStatistic(double value) = 0;
	virtual void PrintStatistic(const std::string& name) = 0;

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

class CStatDisplay
{
public:
	CStatDisplay(CWeatherData<SWeatherInfo>& innerStation, CWeatherData<SWeatherInfoPro>& outerStation)
	{
		m_innerConnection = innerStation.DoOnWeatherChange([this](const SWeatherInfo& innerInfo) {
			CalculateInnerStatistic(innerInfo);
			PrintInnerStatistic();
		});
		m_outerConnection = outerStation.DoOnWeatherChange([this](const SWeatherInfoPro& outerInfo) {
			CalculateOuterStatistic(outerInfo);
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
	void CalculateInnerStatistic(const SWeatherInfo& innerInfo)
	{
		m_innerStatistic.temperatureStat.UpdateStatistic(innerInfo.temperature);
		m_innerStatistic.humidityStat.UpdateStatistic(innerInfo.humidity);
		m_innerStatistic.pressureStat.UpdateStatistic(innerInfo.pressure);
	}
	void PrintOuterStatistic()
	{
		std::cout << "------------Statisitic weather outside----------------\n";
		m_outerStatistic.temperatureStat.PrintStatistic("temperature");
		m_outerStatistic.humidityStat.PrintStatistic("humidity");
		m_outerStatistic.pressureStat.PrintStatistic("pressure");
		m_outerStatistic.windSpeedStat.PrintStatistic("wind speed");
		m_outerStatistic.windDirectionStat.PrintStatistic("wind direction");
		std::cout << "------------Statisitic weather outside----------------\n";
	}
	void PrintInnerStatistic()
	{
		std::cout << "------------Statisitic weather inside----------------\n";
		m_innerStatistic.temperatureStat.PrintStatistic("temperature");
		m_innerStatistic.humidityStat.PrintStatistic("humidity");
		m_innerStatistic.pressureStat.PrintStatistic("pressure");
		std::cout << "------------Statisitic weather inside----------------\n";
	}


	ScopedConnection m_innerConnection;
	ScopedConnection m_outerConnection;

	SWeatherStatisticPro m_outerStatistic;
	SWeatherStatistic m_innerStatistic;
};


class CDisplay
{
public:
	CDisplay(CWeatherData<SWeatherInfo>& innerStation, CWeatherData<SWeatherInfoPro>& outerStation)
	{
		m_innerConnection = innerStation.DoOnWeatherChange([this](const SWeatherInfo& innerInfo) {
			PrintInnerInfo(innerInfo);
		});
		m_outerConnection = outerStation.DoOnWeatherChange([this](const SWeatherInfoPro& outerInfo) {
			PrintOuterInfo(outerInfo);
		});
	}

private:
	void PrintOuterInfo(const SWeatherInfoPro& outerInfo)
	{
		std::cout << "------------Current weather outside----------------\n";
		std::cout << "Current Temp " << outerInfo.basicInfo.temperature << std::endl;
		std::cout << "Current Hum " << outerInfo.basicInfo.humidity << std::endl;
		std::cout << "Current Pressure " << outerInfo.basicInfo.pressure << std::endl;
		std::cout << "Current Wind speed " << outerInfo.wind.speed << std::endl;
		std::cout << "Current Wind direction " << outerInfo.wind.direction << std::endl;
		std::cout << "------------Current weather outside----------------\n";
	}
	void PrintInnerInfo(const SWeatherInfo& innerInfo)
	{
		std::cout << "------------Current weather inside----------------\n";
		std::cout << "Current Temp " << innerInfo.temperature << std::endl;
		std::cout << "Current Hum " << innerInfo.humidity << std::endl;
		std::cout << "Current Pressure " << innerInfo.pressure << std::endl;
		std::cout << "------------Current weather inside----------------\n";
	}
	
	ScopedConnection m_innerConnection;
	ScopedConnection m_outerConnection;
};


