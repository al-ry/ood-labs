#pragma once
#include <iostream>
#include <boost/format.hpp>
namespace with_state
{

struct IState
{
	virtual void InsertQuarter() = 0;
	virtual void EjectQuarter() = 0;
	virtual void TurnCrank() = 0;
	virtual void Dispense() = 0;
	virtual void Refill(unsigned ballsCount) = 0;
	virtual std::string ToString() const = 0;
	virtual ~IState() = default;
};

struct IGumballMachine
{
	virtual void ReleaseBall() = 0;
	virtual unsigned GetBallCount() const = 0;

	virtual void SetGamballCount(unsigned count) = 0;
	virtual unsigned GetQuarterCount() const = 0;
	virtual void SpendQuarter() = 0;
	virtual void AddQuarter() = 0;
	virtual void ReturnQuarters() = 0;


	virtual void SetSoldOutState() = 0;
	virtual void SetNoQuarterState() = 0;
	virtual void SetSoldState() = 0;
	virtual void SetHasQuarterState() = 0;

	virtual ~IGumballMachine() = default;
};

class CSoldState : public IState
{
public:
	CSoldState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}
	void InsertQuarter() override
	{
		std::cout << "Please wait, we're already giving you a gumball\n";
	}
	void EjectQuarter() override
	{
		std::cout << "Sorry you already turned the crank\n";
	}
	void TurnCrank() override
	{
		std::cout << "Turning twice doesn't get you another gumball\n";
	}
	void Dispense() override
	{
		m_gumballMachine.ReleaseBall();
		if (m_gumballMachine.GetBallCount() == 0)
		{
			std::cout << "Oops, out of gumballs\n";
			m_gumballMachine.SetSoldOutState();
		}
		else
		{
			if (m_gumballMachine.GetQuarterCount() > 0)
			{
				m_gumballMachine.SetHasQuarterState();
			}
			else
			{
				m_gumballMachine.SetNoQuarterState();
			}
		}
	}
	void Refill(unsigned ballsCount) override
	{
		std::cout << "Cannot refill  while giving a gumball\n";
	}
	std::string ToString() const override
	{
		return "delivering a gumball";
	}

private:
	IGumballMachine& m_gumballMachine;
};

class CSoldOutState : public IState
{
public:
	CSoldOutState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		std::cout << "You can't insert a quarter, the machine is sold out\n";
	}
	void EjectQuarter() override
	{
		m_gumballMachine.ReturnQuarters();
	}
	void TurnCrank() override
	{
		std::cout << "You turned but there's no gumballs\n";
	}
	void Dispense() override
	{
		std::cout << "No gumball dispensed\n";
	}
	std::string ToString() const override
	{
		return "sold out";
	}
	void Refill(unsigned ballsCount) override
	{
		m_gumballMachine.SetGamballCount(ballsCount);
		if (m_gumballMachine.GetBallCount() > 0)
		{
			if (m_gumballMachine.GetQuarterCount() > 0)
			{
				m_gumballMachine.SetHasQuarterState();
			}
			else
			{
				m_gumballMachine.SetNoQuarterState();
			}
		}	
	}

private:
	IGumballMachine& m_gumballMachine;
};

class CHasQuarterState : public IState
{
public:
	CHasQuarterState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		m_gumballMachine.AddQuarter();
	}
	void EjectQuarter() override
	{
		m_gumballMachine.ReturnQuarters();
		m_gumballMachine.SetNoQuarterState();
	}
	void TurnCrank() override
	{
		std::cout << "You turned...\n";
		m_gumballMachine.SpendQuarter();
		m_gumballMachine.SetSoldState();
	}
	void Dispense() override
	{
		std::cout << "No gumball dispensed\n";
	}
	std::string ToString() const override
	{
		return "waiting for turn of crank";
	}

	void Refill(unsigned ballsCount) override
	{
		m_gumballMachine.SetGamballCount(ballsCount);
	}

private:
	IGumballMachine& m_gumballMachine;
};

class CNoQuarterState : public IState
{
public:
	CNoQuarterState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		m_gumballMachine.AddQuarter();
		m_gumballMachine.SetHasQuarterState();
	}
	void EjectQuarter() override
	{
		std::cout << "You haven't inserted a quarter\n";
	}
	void TurnCrank() override
	{
		std::cout << "You turned but there's no quarter\n";
	}
	void Dispense() override
	{
		std::cout << "You need to pay first\n";
	}
	std::string ToString() const override
	{
		return "waiting for quarter";
	}
	void Refill(unsigned ballsCount) override
	{
		m_gumballMachine.SetGamballCount(ballsCount);
	}

private:
	IGumballMachine& m_gumballMachine;
};

class CGumballMachine : private IGumballMachine
{
public:
	CGumballMachine(unsigned numBalls)
		: m_soldState(*this)
		, m_soldOutState(*this)
		, m_noQuarterState(*this)
		, m_hasQuarterState(*this)
		, m_state(&m_soldOutState)
		, m_ballsCount(numBalls)
	{
		if (m_ballsCount > 0)
		{
			m_state = &m_noQuarterState;
		}
	}
	void EjectQuarter()
	{
		m_state->EjectQuarter();
	}
	void Refill(unsigned count)
	{
		m_state->Refill(count);
	}
	void InsertQuarter()
	{
		m_state->InsertQuarter();
	}
	void TurnCrank()
	{
		m_state->TurnCrank();
		m_state->Dispense();
	}
	std::string ToString() const
	{
		auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Contains: %3% quarter%4%
Machine is %5%
)");
		return (fmt % m_ballsCount
			% (m_ballsCount != 1 ? "s" : "")
			% m_quartersCount
			% (m_quartersCount != 1 ? "s" : "")
			% m_state->ToString()).str();
	}

private:
	unsigned GetBallCount() const override
	{
		return m_ballsCount;
	}
	virtual void ReleaseBall() override
	{
		if (m_ballsCount != 0)
		{
			std::cout << "A gumball comes rolling out the slot...\n";
			--m_ballsCount;
		}
	}
	void SetSoldOutState() override
	{
		m_state = &m_soldOutState;
	}
	void SetNoQuarterState() override
	{
		m_state = &m_noQuarterState;
	}
	void SetSoldState() override
	{
		m_state = &m_soldState;
	}
	void SetHasQuarterState() override
	{
		m_state = &m_hasQuarterState;
	}

	void SetGamballCount(unsigned count) override
	{
		m_ballsCount = count;
		if (m_ballsCount == 0)
		{
			m_state = &m_soldOutState;
		}
	}

	unsigned GetQuarterCount() const override
	{
		return m_quartersCount;
	}
	void SpendQuarter() override
	{
		if (m_quartersCount != 0)
		{
			--m_quartersCount;
		}
	}
	void AddQuarter() override
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
	void ReturnQuarters() override
	{
		auto fmt = boost::format("%1% quater%2% returned");
		std::cout << fmt % m_quartersCount % (m_quartersCount != 1 ? "s" : "") << std::endl;
		m_quartersCount = 0;
	}

private:
	unsigned m_ballsCount = 0;
	unsigned m_quartersCount = 0;
	CSoldState m_soldState;
	CSoldOutState m_soldOutState;
	CNoQuarterState m_noQuarterState;
	CHasQuarterState m_hasQuarterState;
	IState* m_state;
};

} // namespace with_state
