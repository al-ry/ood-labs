#include "stdafx.h"
#include "ShapeFactory.h"
#include "RegularPolygon.h"
#include "Ellipse.h"
#include "Rectangle.h"
#include "Triangle.h"

CShapeFactory::CShapeFactory()
	: m_actionMap({ { "regular_polygon", bind(&CShapeFactory::MakeRegularPolygon, this, std::placeholders::_1) },
		{ "ellipse", bind(&CShapeFactory::MakeEllipse, this, std::placeholders::_1) },
		{ "rectangle", bind(&CShapeFactory::MakeRectangle, this, std::placeholders::_1) },
		{ "triangle", bind(&CShapeFactory::MakeTriangle, this, std::placeholders::_1) } })
{
}

std::unique_ptr<CShape> CShapeFactory::CreateShape(const std::string& desc)
{
	std::stringstream strm(desc);
	std::string shapeType;
	strm >> shapeType;
	auto it = m_actionMap.find(shapeType);
	if (it != m_actionMap.end())
	{
		ShapeInfo info = ParseShapeInfo(strm);
		return it->second(info);
	}
	throw std::runtime_error("Unknown shape type");
}

ShapeInfo CShapeFactory::ParseShapeInfo(std::istream& args)
{
	std::string arg;
	ShapeInfo info;
	while (args.good())
	{
		args >> arg;
		info.push_back(arg);
	}
	return info;
}

Color CShapeFactory::ParseColor(const std::string& color)
{
	if (color == "red")
	{
		return Color::Red;
	}
	else if (color == "blue")
	{
		return Color::Blue;
	}
	else if (color == "green")
	{
		return Color::Green;
	}
	else if (color == "pink")
	{
		return Color::Pink;
	}
	else if (color == "black")
	{
		return Color::Black;
	}
	else if (color == "yellow")
	{
		return Color::Yellow;
	}
	throw std::runtime_error("Unknown shape color specified");
}

std::unique_ptr<CShape> CShapeFactory::MakeRegularPolygon(const ShapeInfo& info)
{
	if (info.size() != 5)
	{
		throw std::runtime_error("Incorrect parameters count for regular polygon specified");
	}
	Color color = ParseColor(info[0]);
	double centerX = std::stod(info[1]);
	double centerY = std::stod(info[2]);
	CPoint center(centerX, centerY);
	double radius = std::stod(info[3]);
	int vertexCount = std::stoi(info[4]);
	return std::make_unique<CRegularPolygon>(color, center, radius, vertexCount);
}
std::unique_ptr<CShape> CShapeFactory::MakeEllipse(const ShapeInfo& info)
{
	if (info.size() != 5)
	{
		throw std::runtime_error("Incorrect parameters count for ellipse specified");
	}
	Color color = ParseColor(info[0]);
	double centerX = std::stod(info[1]);
	double centerY = std::stod(info[2]);
	CPoint center(centerX, centerY);
	double verticalRadius = std::stod(info[3]);
	double horizontalRadius = std::stod(info[4]);
	return std::make_unique<CEllipse>(color, center, verticalRadius, horizontalRadius);
}

std::unique_ptr<CShape> CShapeFactory::MakeRectangle(const ShapeInfo& info)
{
	if (info.size() != 5)
	{
		throw std::runtime_error("Incorrect parameters count for rectangle specified");
	}
	Color color = ParseColor(info[0]);
	double leftTopX = std::stod(info[1]);
	double leftTopY = std::stod(info[2]);
	CPoint leftTop(leftTopX, leftTopY);
	double width = std::stod(info[3]);
	double height = std::stod(info[4]);
	return std::make_unique<CRectangle>(color, leftTop, width, height);
}

std::unique_ptr<CShape> CShapeFactory::MakeTriangle(const ShapeInfo& info)
{
	if (info.size() != 7)
	{
		throw std::runtime_error("Incorrect parameters count for triangle specified");
	}
	Color color = ParseColor(info[0]);
	double vertexCoordX = std::stod(info[1]);
	double vertexCoordY = std::stod(info[2]);
	CPoint vertex1(vertexCoordX, vertexCoordY);
	vertexCoordX = std::stod(info[3]);
	vertexCoordY = std::stod(info[4]);
	CPoint vertex2(vertexCoordX, vertexCoordY);
	vertexCoordX = std::stod(info[5]);
	vertexCoordY = std::stod(info[6]);
	CPoint vertex3(vertexCoordX, vertexCoordY);
	return std::make_unique<CTriangle>(color, vertex1, vertex2, vertex3);
}


