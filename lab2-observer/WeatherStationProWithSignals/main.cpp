#include "WeatherData.h"


int main(void)
{
	CWeatherData<SWeatherInfoPro> wdOut;
	CWeatherData<SWeatherInfo> wdIn;

	
	CDisplay display(wdIn, wdOut);
	CStatDisplay displayStat(wdIn, wdOut);
	wdOut.SetMeasurements({ 0, 99, 0, 0, 0 });
	wdIn.SetMeasurements({ 10, 10, 10 });
	//CDisplay dis;
	//wd.RegisterObserver(dis, 1);

	//wd.SetMeasurements(0, 0, 0, 0, 0);
	return 0;
}