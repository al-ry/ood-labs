#include "stdafx.h"
#include "../MultiGamballMachine/NaiveMultiGamballMachine.h"

namespace naive
{
inline std::string GetExpectedMachineInfo(unsigned quartersCount, unsigned ballsCount, const std::string& state)
{
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: %1% gumball%2%
Contains: %3% quarter%4%
Machine is %5%
)");
	return (fmt % ballsCount
		% (ballsCount != 1 ? "s" : "")
		% quartersCount
		% (quartersCount != 1 ? "s" : "")
		% state)
		.str();
}
} // namespace naive

struct when_empty_machine_in_naive_impl_
{
	naive::CGumballMachine machine;
	when_empty_machine_in_naive_impl_()
		: machine(0)
	{
	}
};


BOOST_FIXTURE_TEST_SUITE(when_empty_machine_in_naive_impl, when_empty_machine_in_naive_impl_)
	BOOST_AUTO_TEST_CASE(has_default_decsription)
	{
		auto actual = machine.ToString();
		auto expected = naive::GetExpectedMachineInfo(0, 0, "sold out");
		BOOST_CHECK_EQUAL(actual, expected);
	}
	BOOST_AUTO_TEST_CASE(cant_inserting_quaters)
	{
		machine.InsertQuarter();
		auto actual = machine.ToString();
		auto expected = naive::GetExpectedMachineInfo(0, 0, "sold out");
	}
BOOST_AUTO_TEST_SUITE_END()

struct when_machine_with_balls_in_naive_impl_
{
	naive::CGumballMachine machine;
	when_machine_with_balls_in_naive_impl_()
		: machine(6)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(when_machine_with_balls_in_naive_impl, when_machine_with_balls_in_naive_impl_)
	BOOST_AUTO_TEST_CASE(can_insert_3_quaters)
	{
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		auto actual = machine.ToString();
		auto expected = naive::GetExpectedMachineInfo(3, 6, "waiting for turn of crank");
		BOOST_CHECK_EQUAL(actual, expected);
	}
	BOOST_AUTO_TEST_CASE(cant_insert_greater_than_max_quaters_count)
	{
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();

		auto actual = machine.ToString();
		auto expected = naive::GetExpectedMachineInfo(5, 6, "waiting for turn of crank");
		BOOST_CHECK_EQUAL(actual, expected);
	}
	BOOST_AUTO_TEST_CASE(can_inject_after_inserting)
	{
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.EjectQuarter();
		auto actual = machine.ToString();
		auto expected = naive::GetExpectedMachineInfo(0, 6, "waiting for quarter");
		BOOST_CHECK_EQUAL(actual, expected);
	}
	BOOST_AUTO_TEST_CASE(can_turn_crank_while_there_are_quarters)
	{
		auto actual = machine.ToString();
		auto expected = naive::GetExpectedMachineInfo(0, 6, "waiting for quarter");
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.TurnCrank();
		actual = machine.ToString();
		expected = naive::GetExpectedMachineInfo(1, 5, "waiting for turn of crank");
		machine.TurnCrank();
		actual = machine.ToString();
		expected = naive::GetExpectedMachineInfo(0, 4, "waiting for quarter");
		BOOST_CHECK_EQUAL(actual, expected);
	}

BOOST_AUTO_TEST_SUITE_END()

struct when_quarters_count_greater_than_balls_count_
{
	naive::CGumballMachine machine;
	when_quarters_count_greater_than_balls_count_()
		: machine(2)
	{
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.TurnCrank();
		machine.TurnCrank();
	}
};

BOOST_FIXTURE_TEST_SUITE(when_quarters_count_greater_than_balls_count, when_quarters_count_greater_than_balls_count_)
	BOOST_AUTO_TEST_CASE(can_turn_crank_while_there_are_balls_in_machine)
	{
		auto actual = machine.ToString();
		auto expected = naive::GetExpectedMachineInfo(1, 0, "sold out");
		BOOST_CHECK_EQUAL(actual, expected);
	}
	BOOST_AUTO_TEST_CASE(can_get_quarters)
	{
		auto actual = machine.ToString();
		auto expected = naive::GetExpectedMachineInfo(1, 0, "sold out");
		BOOST_CHECK_EQUAL(actual, expected);

		machine.EjectQuarter();
		actual = machine.ToString();
		expected = naive::GetExpectedMachineInfo(0, 0, "sold out");
		BOOST_CHECK_EQUAL(actual, expected);
	}

	struct after_refill_ : when_quarters_count_greater_than_balls_count_
	{

		after_refill_()
		{
			machine.Refill(5);
		}
	};
	BOOST_FIXTURE_TEST_SUITE(after_refill, after_refill_)
		BOOST_AUTO_TEST_CASE(has_waiting_for_turn_of_crank_state_because_has_one_quarter)
		{
			auto actual = machine.ToString();
			auto expected = naive::GetExpectedMachineInfo(1, 5, "waiting for turn of crank");
			BOOST_CHECK_EQUAL(actual, expected);
		}
		BOOST_AUTO_TEST_CASE(can_turn_crank_again_because_has_one_quarter)
		{
			machine.TurnCrank();
			auto actual = machine.ToString();
			auto expected = naive::GetExpectedMachineInfo(0, 4, "waiting for quarter");
			BOOST_CHECK_EQUAL(actual, expected);
		}
	BOOST_AUTO_TEST_SUITE_END()

		struct after_refill_to_0_ : when_quarters_count_greater_than_balls_count_
	{

		after_refill_to_0_()
		{
			machine.Refill(0);
		}
	};

	BOOST_FIXTURE_TEST_SUITE(after_refill_to_0, after_refill_to_0_)
		BOOST_AUTO_TEST_CASE(has_sold_out_state_because)
		{
			auto actual = machine.ToString();
			auto expected = naive::GetExpectedMachineInfo(1, 0, "sold out");
			BOOST_CHECK_EQUAL(actual, expected);
		}
		BOOST_AUTO_TEST_CASE(cannot_turn_crank_again_because_hasnt_balls)
		{
			machine.TurnCrank();
			auto actual = machine.ToString();
			auto expected = naive::GetExpectedMachineInfo(1, 0, "sold out");
			BOOST_CHECK_EQUAL(actual, expected);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
