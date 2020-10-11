#pragma once
#include <iosfwd>
#include "IDesigner.h"
class CPictureDraft;

struct IShapeFactory;

class CDesigner : public IDesigner
{
public:
	CDesigner(IShapeFactory & factory);
	~CDesigner();
	CPictureDraft CreateDraft(std::istream & inputData) override;
private:
	IShapeFactory & m_factory;
};

