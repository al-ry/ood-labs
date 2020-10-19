#pragma once
#include <string>
#include <memory>

class IParagraph
{
public:
	virtual std::string GetText()const = 0;
	virtual void SetText(const std::string& text) = 0;
	virtual ~IParagraph() = default;
};

typedef std::shared_ptr<IParagraph> IParagraphPtr;
typedef std::shared_ptr<const IParagraph> IParagraphConstPtr;