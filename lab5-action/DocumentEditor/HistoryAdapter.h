#pragma once
#include"ICommandSink.h"
#include "History.h"

class CHistoryAdapter: public ICommandSink
{
public:
	CHistoryAdapter(CHistory& history);
	void AddCommand(ICommandPtr&& command) override;

private:
	CHistory& m_history;
};