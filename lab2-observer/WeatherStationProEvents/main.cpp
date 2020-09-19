#include "../WeatherStationProEvents/WeatherData.h"

int main()
{
	CWeatherData wd;

	CDisplay display;

	std::set<WeatherEvent> events = { WeatherEvent::Temperature, WeatherEvent::Pressure };
	std::set<WeatherEvent> events2 = { WeatherEvent::WindSpeed,
										WeatherEvent::Humidity, 
										WeatherEvent::WindDirection,
										WeatherEvent::Temperature,
										WeatherEvent::Pressure };
	wd.RegisterObserver(display, events, 1);
	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay, events2, 8);
	wd.AddEventToSubscriber(display, WeatherEvent::WindDirection);
	wd.UnsubscribeFromEvent(display, WeatherEvent::WindDirection);
	wd.AddEventToSubscriber(statsDisplay, WeatherEvent::WindDirection);
	wd.UnsubscribeFromEvent(statsDisplay, WeatherEvent::Humidity);


	//wd.SetMeasurements(10, 0.9, 760, 20, 90);
	wd.SetMeasurements(4, 0.8, 761, 15, 180);
	wd.SetMeasurements(4, 0.8, 761, 18, 180);
	wd.SetMeasurements(4, 0.8, 761, 15, 180);

	wd.RemoveObserver(statsDisplay);

	//wd.SetMeasurements(10, 0.8, 761);
	//wd.SetMeasurements(-10, 0.8, 761);

	return 0;
}