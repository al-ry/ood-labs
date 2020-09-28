#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string& description)
		: m_description(description)
	{
	}

	std::string GetDescription() const override final
	{
		return m_description;
	}

private:
	std::string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		: CBeverage(description)
	{
	}

	double GetCost() const override
	{
		return 60;
	}
};


enum class CoffeePortion
{
	Standart,
	Double
};

inline std::string CoffeePortionToString(CoffeePortion portion)
{
	switch (portion)
	{
	case CoffeePortion::Standart:
		return "Standart";
	case CoffeePortion::Double:
		return "Double";
	default:
		return "";
	}

}


// Капуччино
class CCappuccino : public CCoffee
{
public:
	CCappuccino(CoffeePortion portion = CoffeePortion::Standart)
		: CCoffee(CoffeePortionToString(portion) + " Cappuccino")
	{
		if (portion == CoffeePortion::Double)
		{
			m_cost = 130;
		}
	}

	double GetCost() const override
	{
		return m_cost;
	}

private:
	double m_cost = 90;
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(CoffeePortion portion = CoffeePortion::Standart)
		: CCoffee(CoffeePortionToString(portion) + " Latte")
	{
		if (portion == CoffeePortion::Double)
		{
			m_cost = 120;
		}
	}

	double GetCost() const override
	{
		return m_cost;
	}

private:
	double m_cost = 80;
};

enum class KindOfTea
{
	Black,
	Green,
	Red,
	Oolong
};

inline std::string KindOfTeaToString(KindOfTea tea)
{
	switch (tea)
	{
	case KindOfTea::Black:
		return "Black";
	case KindOfTea::Green:
		return "Green";
	case KindOfTea::Red:
		return "Red";
	case KindOfTea::Oolong:
		return "Oolong";
	default:
		return "";
	}
}
// Чай
class CTea : public CBeverage
{
public:
	CTea(KindOfTea tea = KindOfTea::Black)
		: CBeverage(KindOfTeaToString(tea) + " Tea")
	{
	}

	double GetCost() const override
	{
		return 30;
	}
};


enum class MilkshakePortion
{
	Small,
	Medium,
	Large
};


inline std::string MilkShakePortionToString(MilkshakePortion portion)
{
	switch (portion)
	{
	case MilkshakePortion::Small:
		return "Small";
	case MilkshakePortion::Medium:
		return "Medium";
	case MilkshakePortion::Large:
		return "Large";
	default:
		return "";
	}
}

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkshakePortion portion = MilkshakePortion::Medium)
		: CBeverage(MilkShakePortionToString(portion) + " Milkshake")
	{
		switch (portion)
		{
		case MilkshakePortion::Small:
			m_cost = 50;
			break;
		case MilkshakePortion::Large:
			m_cost = 80;
			break;
		default:
			break;
		}
	}

	double GetCost() const override
	{
		return m_cost;
	}
private:
	double m_cost = 60;
};
