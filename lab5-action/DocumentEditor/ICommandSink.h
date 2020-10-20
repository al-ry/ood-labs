#pragma once
#include "ICommand.h"


class ICommandSink
{
public:
	virtual void AddCommand(ICommandPtr&& command) = 0;
	~ICommandSink() = default;
};

typedef std::unique_ptr<ICommandSink> ICommandSinkPtr;