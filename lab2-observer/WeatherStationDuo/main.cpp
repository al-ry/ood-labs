#include "../WeatherStationDuo/WeatherData.h"

int main()
{
	CWeatherData wdIn;
	CWeatherData wdOut;

	CDisplay display(wdIn, wdOut);
	wdIn.RegisterObserver(display, 1);
	wdOut.RegisterObserver(display, 1);

	CStatsDisplay statsDisplay(wdIn, wdOut);
	wdIn.RegisterObserver(statsDisplay, 8);
	wdOut.RegisterObserver(statsDisplay, 8);

	wdOut.SetMeasurements(8, 0.8, 766);
	wdIn.SetMeasurements(25, 0.0, 760);
	wdIn.SetMeasurements(20, 0.1, 761);

	wdOut.SetMeasurements(8, 0.8, 766);

	wdOut.RemoveObserver(statsDisplay);

	wdOut.SetMeasurements(10, 0.8, 761);
	wdOut.SetMeasurements(-10, 0.8, 761);

	return 0;
}