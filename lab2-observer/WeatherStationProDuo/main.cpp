#include "../WeatherStationProDuo/WeatherData.h"

int main()
{
	CWeatherDataInside wdIn;
	CWeatherDataOutside wdOut;

	CInsideWeatherDisplay display;
	COutsideWeatherDisplay displayOut;

	wdIn.RegisterObserver(display, 1);
	wdOut.RegisterObserver(displayOut, 1);

	CStatInsideDisplay statsDisplayInside;
	CStatOutsideDisplay statsDisplayOuside;
	wdIn.RegisterObserver(statsDisplayInside, 1);
	wdOut.RegisterObserver(statsDisplayOuside, 1);

	wdOut.SetMeasurements(8, 0.8, 766, 25, 270);
	wdIn.SetMeasurements(25, 0.0, 760);
	wdIn.SetMeasurements(20, 0.1, 761);
	wdOut.SetMeasurements(-5, 0.8, 765, 20, 90);

	wdOut.SetMeasurements(8, 0.8, 766, 20, 90);

	wdOut.RemoveObserver(statsDisplayOuside);

	wdOut.SetMeasurements(10, 0.8, 761, 18, 90);
	wdOut.SetMeasurements(-10, 0.8, 761, 15, 30);

	return 0;
}