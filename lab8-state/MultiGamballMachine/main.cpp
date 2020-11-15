#include "MultiGumballMachineWithState.h"
#include "NaiveMultiGamballMachine.h"
#include "Menu.h"
#include <functional>
using namespace std;

using namespace std::placeholders;


template <typename GumballMachineType>
class CGumballMachineCommandHandler
{
public:
	CGumballMachineCommandHandler()
		: m_machine(0)
		, m_menu()
	{
		m_menu.AddItem("InsertQuarter", "Inserting quarter into machine",
			std::bind(&CGumballMachineCommandHandler::InsertQuarter, this, _1));
		m_menu.AddItem("EjectQuarters", "Ejects all inserted quarters",
			std::bind(&CGumballMachineCommandHandler::EjectQuarter, this, _1));

		m_menu.AddItem("TurnCrank", "Turning crunk and gives you a gumball if you insert a quarter",
			std::bind(&CGumballMachineCommandHandler::TurnCrank, this, _1));

		m_menu.AddItem("ToString", "Prints actual machine info",
			std::bind(&CGumballMachineCommandHandler::ToString, this, _1));

		m_menu.AddItem("Refill", "Fill machine with new gumballs",
			std::bind(&CGumballMachineCommandHandler::Refill, this, _1));

		m_menu.AddItem("help", "Show instructions",
			bind(&CMenuFP::ShowInstructions, &m_menu));
		m_menu.AddItem("exit", "Exit from this menu",
			bind(&CMenuFP::Exit, &m_menu));
	}

	void Run()
	{
		m_menu.Run();
	}

private:
	void InsertQuarter(istream&)
	{
		m_machine.InsertQuarter();
	}
	void EjectQuarter(istream&)
	{
		m_machine.EjectQuarter();
	}
	void TurnCrank(istream&)
	{
		m_machine.TurnCrank();
	}
	void Refill(istream& is)
	{
		unsigned count;
		is >> count;
		m_machine.Refill(count);
	}
	void ToString(istream&)
	{
		std::cout << m_machine.ToString();
	}

private:
	GumballMachineType m_machine;
	CMenuFP m_menu;
};

int main()
{
	CMenuFP menu;
	menu.AddItem("with_state", "Gumball machine with state implementation", [&](istream&) {
		CGumballMachineCommandHandler<with_state::CGumballMachine> handler;
		handler.Run();
		menu.ShowInstructions();
	});
	menu.AddItem("naive", "Gumball machine with naive implementation", [&](istream&) {
		CGumballMachineCommandHandler<naive::CGumballMachine> handler;
		handler.Run();
		menu.ShowInstructions();
	});

	menu.AddItem("q", "Exit Program", bind(&CMenuFP::Exit, &menu));
	menu.Run();
	return 0;
}

