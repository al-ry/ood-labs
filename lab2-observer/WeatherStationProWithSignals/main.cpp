#include "WeatherData.h"


int main(void)
{
	COutsideWeatherData outWD;
	CInsideWeatherData inWD;

	CInsideStatDisplay outStatDisplay(inWD);

	COutsideStatDisplay statDisplay(outWD);
	//inWD.SetMeasurements(1, 1, 1);

	//inWD.SetMeasurements(1, 1, 1);

	outWD.SetMeasurements(1, 1, 1, 1, 1);

	outWD.SetMeasurements(1, 1, 1, 1, 1);
	//CDisplay display(wdIn, wdOut);
	//CStatDisplay displayStat(wdIn, wdOut);
	//wdOut.SetMeasurements({ 0, 99, 0, 0, 0 });
	//wdIn.SetMeasurements({ 10, 10, 10 });
	//CDisplay dis;
	//wd.RegisterObserver(dis, 1);

	//wd.SetMeasurements(0, 0, 0, 0, 0);
	return 0;
}