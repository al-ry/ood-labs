#pragma once
#include "../DocumentEditor/ICommandSink.h"
#include "../DocumentEditor/AbstractCommand.h"
#include <string>
#include <sstream>


class MockAdapter : public ICommandSink
{
public:
	MockAdapter(std::stringstream& ss)
		: m_sstrm(ss)
	{
	}
	void AddCommand(ICommandPtr&& command)
	{
		m_sstrm << "Command Added\n";
	}

private:
	std::stringstream& m_sstrm;
};