#include "HistoryAdapter.h"

CHistoryAdapter::CHistoryAdapter(CHistory& history)
	: m_history(history)
{
}

void CHistoryAdapter::AddCommand(ICommandPtr&& command)
{
	m_history.AddAndExecuteCommand(std::move(command));
}
