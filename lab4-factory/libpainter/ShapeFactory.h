#pragma once
#include "stdafx.h"
#include "Point.h"
#include "IShapeFactory.h"
#include "Color.h"

typedef std::vector<std::string> ShapeInfo;

class CShapeFactory : public IShapeFactory
{
public:
	CShapeFactory();
	std::unique_ptr<CShape> CreateShape(const std::string& desc) override;

private:
	using ShapeCreator = std::function<std::unique_ptr<CShape>(const ShapeInfo &info)>;
	using ActionMap = std::map<std::string, ShapeCreator>;

	static ShapeInfo ParseShapeInfo(std::istream& args);
	static Color ParseColor(const std::string& color);
	std::unique_ptr<CShape> MakeRegularPolygon(const ShapeInfo& info);
	std::unique_ptr<CShape> MakeEllipse(const ShapeInfo& info);
	std::unique_ptr<CShape> MakeRectangle(const ShapeInfo& info);
	std::unique_ptr<CShape> MakeTriangle(const ShapeInfo& info);

private:
	ActionMap m_actionMap;
};
