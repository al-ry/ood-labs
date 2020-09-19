#pragma once

#include <functional>
#include <map>
#include <set>
#include <algorithm>
/*
��������� ��������� IObserver. ��� ������ ������������� �����,
�������� �������� ����������� �� ���������������� IObservable
���������� ������� �������� ��� ���������,
������������� ����������� � ����� Update
*/

template <typename T, typename EventType>
class IObservable;

template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;
	virtual ~IObserver() = default;
};

/*
��������� ��������� IObservable. ��������� ����������� � ���������� �� ����������, � �����
������������ �������� ����������� ������������������ ������������.
*/
template <typename T, typename EventType>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer, const std::set<EventType>& events, int priority) = 0;
	virtual void NotifyObservers(const std::set<EventType>& changedEvents) = 0;
	virtual void UnsubscribeFromEvent(IObserver<T>& observer, const EventType& event) = 0;
	virtual void AddEventToSubscriber(IObserver<T>& observer, const EventType& event) = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
};

// ���������� ���������� IObservable
template <class T, typename EventType>
class CObservable : public IObservable<T, EventType>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, const std::set<EventType>& events, int priority) override
	{
		auto it = std::find_if(m_observers.begin(), m_observers.end(), [&](const auto& pair) {
			return &observer == pair.second;
		});
		if (it == m_observers.end())
		{
			m_observers.emplace(priority, &observer);
			m_eventSubscribers.emplace(&observer, events);
		}
	}

	void NotifyObservers(const std::set<EventType>& changedEvents) override
	{
		T data = GetChangedData();
		auto oberversCpy = m_observers;
		for (auto it = oberversCpy.rbegin(); it != oberversCpy.rend(); it++)
		{
			auto found = m_eventSubscribers.find(it->second);
			bool isSubscriber = std::any_of(changedEvents.begin(), changedEvents.end(), [&](auto event) {
				return found->second.find(event) != found->second.end();
			});
			if (isSubscriber)
			{
				it->second->Update(data);
			}
		}
	}

	void UnsubscribeFromEvent(IObserver<T>& observer, const EventType& event) override
	{
		auto found = m_eventSubscribers.find(&observer);
		if (found != m_eventSubscribers.end())
		{
			found->second.erase(event);
		}
	}

	void AddEventToSubscriber(IObserver<T>& observer, const EventType& event)
	{
		auto found = m_eventSubscribers.find(&observer);
		if (found != m_eventSubscribers.end())
		{
			found->second.emplace(event);
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		std::erase_if(m_observers, [&](const auto& item) {
			return item.second == std::addressof(observer);
		});
		std::erase_if(m_eventSubscribers, [&](const auto& item) {
			return item.first == std::addressof(observer);
		});
	}

protected:
	// ������-���������� ������ ����������� ������ �����,
	// � ������� ���������� ���������� �� ���������� � �������
	virtual T GetChangedData() const = 0;

private:
	std::multimap<int, ObserverType*> m_observers;
	std::map<ObserverType*, std::set<EventType>> m_eventSubscribers;
};
