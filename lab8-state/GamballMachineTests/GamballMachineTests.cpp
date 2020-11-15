#include "stdafx.h"
#include "../GamballMachine/GamballMachine.h"

struct when_empty_machine_
{
	CGumballMachine machine;
	when_empty_machine_()
		: machine(0)
	{
	}
};

std::string GetExpectedMachineInfo(int expectedBalls, const std::string& state)
{
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Machine is %3%
)");
	return (fmt % expectedBalls % (expectedBalls != 1 ? "s" : "") % state).str();
}

BOOST_FIXTURE_TEST_SUITE(when_empty_machine, when_empty_machine_)
	BOOST_AUTO_TEST_CASE(has_sold_out_state)
	{
		auto expected = GetExpectedMachineInfo(0, "sold out");
		auto actual = machine.ToString();
		BOOST_CHECK(expected == actual);
	}
	BOOST_AUTO_TEST_SUITE(when_insert_quarter)
		BOOST_AUTO_TEST_CASE(machine_state_shouldnt_change)
		{
			machine.InsertQuarter();
			auto expected = GetExpectedMachineInfo(0, "sold out");
			auto actual = machine.ToString();
			BOOST_CHECK(expected == actual);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(when_eject_quarter)
		BOOST_AUTO_TEST_CASE(machine_state_shouldnt_change)
		{
			machine.EjectQuarter();

			auto expected = GetExpectedMachineInfo(0, "sold out");
			auto actual = machine.ToString();
			BOOST_CHECK(expected == actual);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(when_turn_crank_quarter)
		BOOST_AUTO_TEST_CASE(machine_state_shouldnt_change)
		{
			machine.TurnCrank();
			auto expected = GetExpectedMachineInfo(0, "sold out");
			auto actual = machine.ToString();
			BOOST_CHECK(expected == actual);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()


struct when_has_balls_
{
	CGumballMachine machine;
	when_has_balls_()
		: machine(5)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(when_has_balls, when_has_balls_)
	BOOST_AUTO_TEST_CASE(has_no_quarter_state_and_5_balls)
	{
		auto expected = GetExpectedMachineInfo(5, "waiting for quarter");
		auto actual = machine.ToString();
		BOOST_CHECK(expected == actual);
	}
	BOOST_AUTO_TEST_SUITE(when_turn_crank_quarter)
		BOOST_AUTO_TEST_CASE(machine_state_shouldnt_change)
		{
			machine.TurnCrank();
			auto expected = GetExpectedMachineInfo(5, "waiting for quarter");
			auto actual = machine.ToString();
			BOOST_CHECK(expected == actual);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(when_enject_quarter)
		BOOST_AUTO_TEST_CASE(machine_state_shouldnt_change)
		{
			machine.EjectQuarter();
			auto expected = GetExpectedMachineInfo(5, "waiting for quarter");
			auto actual = machine.ToString();
			BOOST_CHECK(expected == actual);
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct after_insertin_quarter_: when_has_balls_
	{
		after_insertin_quarter_()
		{
			machine.InsertQuarter();
		}
	};
	BOOST_FIXTURE_TEST_SUITE(after_insertin_quarter, after_insertin_quarter_)
		BOOST_AUTO_TEST_CASE(should_change_state)
		{
			auto expected = GetExpectedMachineInfo(5, "waiting for turn of crank");
			auto actual = machine.ToString();
			BOOST_CHECK_EQUAL(expected, actual);
		}

		BOOST_AUTO_TEST_SUITE(when_inserting_quarter_again)
			BOOST_AUTO_TEST_CASE(machine_state_shouldnt_change)
			{
				machine.InsertQuarter();
				auto expected = GetExpectedMachineInfo(5, "waiting for turn of crank");
				auto actual = machine.ToString();
				BOOST_CHECK(expected == actual);
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_CASE(can_eject)
		{
			machine.EjectQuarter();
			auto expected = GetExpectedMachineInfo(5, "waiting for quarter");
			auto actual = machine.ToString();
			BOOST_CHECK(expected == actual);
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct when_turning_crank_ :after_insertin_quarter_
	{
		when_turning_crank_()
		{
			machine.TurnCrank();
		}
	};

	BOOST_FIXTURE_TEST_SUITE(when_turning_crank, when_turning_crank_)
		BOOST_AUTO_TEST_CASE(should_decrease_ball_count_and_change_state)
		{
			auto expected = GetExpectedMachineInfo(4, "waiting for quarter");
			auto actual = machine.ToString();
			BOOST_CHECK(expected == actual);
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct when_machine_with_one_ball_
	{
		CGumballMachine machine;
		when_machine_with_one_ball_()
			: machine(1)
		{
		}
	};

	BOOST_FIXTURE_TEST_SUITE(when_machine_with_one_ball, when_machine_with_one_ball_)
		BOOST_AUTO_TEST_CASE(should_change_state_to_sold_out_after_turn_crank)
		{
			machine.InsertQuarter();
			machine.TurnCrank();
			auto expected = GetExpectedMachineInfo(0, "sold out");
			auto actual = machine.ToString();
			BOOST_CHECK(expected == actual);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
