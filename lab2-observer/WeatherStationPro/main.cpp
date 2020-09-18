#include "../WeatherStationPro/WeatherData.h"

int main()
{
	CWeatherData wd;

	CDisplay display;
	wd.RegisterObserver(display, 1);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay, 8);

	wd.SetMeasurements(10, 0.9, 760, 20, 90);
	wd.SetMeasurements(4, 0.8, 761, 15, 180);
	wd.SetMeasurements(4, 0.8, 761, 15, 270);
	wd.SetMeasurements(4, 0.8, 761, 15, 360);

	wd.RemoveObserver(statsDisplay);

	//wd.SetMeasurements(10, 0.8, 761);
	//wd.SetMeasurements(-10, 0.8, 761);

	return 0;
}