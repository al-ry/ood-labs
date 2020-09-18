#pragma once

#include <functional>
#include <map>
/*
��������� ��������� IObserver. ��� ������ ������������� �����,
�������� �������� ����������� �� ���������������� IObservable
���������� ������� �������� ��� ���������,
������������� ����������� � ����� Update
*/

template <typename T>
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
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer, int priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
};

// ���������� ���������� IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, int priority) override
	{
		auto it = std::find_if(m_observers.begin(), m_observers.end(), [&](const auto& pair) {
			return &observer == pair.second;
			});
		if (it == m_observers.end())
		{
			m_observers.emplace(priority, &observer);
		}
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		auto oberversCpy = m_observers;
		for (auto it = oberversCpy.rbegin(); it != oberversCpy.rend(); it++)
		{
			it->second->Update(data);
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		std::erase_if(m_observers, [&](const auto& item) {
			return item.second == std::addressof(observer);
			});
	}

protected:
	// ������-���������� ������ ����������� ������ �����,
	// � ������� ���������� ���������� �� ���������� � �������
	virtual T GetChangedData() const = 0;

private:
	std::multimap<int, ObserverType*> m_observers;
};
