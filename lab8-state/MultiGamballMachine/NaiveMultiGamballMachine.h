#pragma once

#include <boost/format.hpp>
#include <iostream>

namespace naive
{
class CGumballMachine
{
public:
	enum class State
	{
		SoldOut, // Жвачка закончилась
		NoQuarter, // Нет монетки
		HasQuarter, // Есть монетка
		Sold, // Монетка выдана
	};

	CGumballMachine(unsigned count)
		: m_ballsCount(count)
		, m_state(count > 0 ? State::NoQuarter : State::SoldOut)
	{
	}

	void InsertQuarter()
	{
		using namespace std;
		switch (m_state)
		{
		case State::SoldOut:
			cout << "You can't insert a quarter, the machine is sold out\n";
			break;
		case State::NoQuarter:
			m_state = State::HasQuarter;
			AddQuarter();
			break;
		case State::HasQuarter:
			AddQuarter();
			break;
		case State::Sold:
			AddQuarter();
			break;
		}
	}

	void EjectQuarter()
	{
		using namespace std;
		switch (m_state)
		{
		case State::HasQuarter:
			ReturnQuaters();
			m_state = State::NoQuarter;
			break;
		case State::NoQuarter:
			cout << "You haven't inserted a quarter\n";
			break;
		case State::Sold:
			ReturnQuaters();
			break;
		case State::SoldOut:
			ReturnQuaters();
			break;
		}
	}

	void TurnCrank()
	{
		using namespace std;
		switch (m_state)
		{
		case State::SoldOut:
			cout << "You turned but there's no gumballs\n";
			break;
		case State::NoQuarter:
			cout << "You turned but there's no quarter\n";
			break;
		case State::HasQuarter:
			cout << "You turned...\n";
			SpendQuater();
			m_state = State::Sold;
			Dispense();
			break;
		case State::Sold:
			cout << "Turning twice doesn't get you another gumball\n";
			break;
		}
	}

	void Refill(unsigned numBalls)
	{
		m_ballsCount = numBalls;
		m_state = numBalls > 0 ? m_quartersCount > 0 ? State::HasQuarter : State::NoQuarter : State::SoldOut;
	}

	std::string ToString() const
	{
		std::string state = (m_state == State::SoldOut) ? "sold out" : (m_state == State::NoQuarter) ? "waiting for quarter" : (m_state == State::HasQuarter) ? "waiting for turn of crank" : "delivering a gumball";
		auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: %1% gumball%2%
Contains: %3% quarter%4%
Machine is %5%
)");
		return (fmt % m_ballsCount
					% (m_ballsCount != 1 ? "s" : "")
					% m_quartersCount
					% (m_quartersCount != 1 ? "s" : "")
					% state).str();
	}

private:

	void AddQuarter()
	{
		using namespace std;
		if (m_quartersCount < 5)
		{
			++m_quartersCount;
			cout << "You inserted a quarter\n";
		}
		else
		{
			cout << "Machine contains max quarter count\n";
		}
	}

	void SpendQuater()
	{
		if (m_quartersCount != 0)
		{
			--m_quartersCount;
		}
	}

	void ReturnQuaters()
	{
		auto fmt = boost::format("%1% quater%2% returned");
		std::cout << fmt % m_quartersCount % (m_quartersCount != 1 ? "s" : "") << std::endl;
		m_quartersCount = 0;
	}
	void Dispense()
	{
		using namespace std;
		switch (m_state)
		{
		case State::Sold:
			cout << "A gumball comes rolling out the slot\n";
			--m_ballsCount;
			if (m_ballsCount == 0)
			{
				cout << "Oops, out of gumballs\n";
				m_state = State::SoldOut;
			}
			else
			{
				m_quartersCount > 0 ? m_state = State::HasQuarter : m_state = State::NoQuarter;
			}
			break;
		case State::NoQuarter:
			cout << "You need to pay first\n";
			break;
		case State::SoldOut:
		case State::HasQuarter:
			cout << "No gumball dispensed\n";
			break;
		}
	}
	unsigned m_quartersCount = 0;
	unsigned m_ballsCount; // Количество шариков
	State m_state = State::SoldOut;
};
} // namespace naive