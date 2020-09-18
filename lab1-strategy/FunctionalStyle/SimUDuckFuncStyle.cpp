#include <functional>
#include <iostream>

using DanceBehaviorFn = std::function<void()>;
using FlyBehaviorFn = std::function<void()>;
using QuackBehaviorFn = std::function<void()>;

namespace QuackBehavior
{
void Quack()
{
	std::cout << "Quack Quack!!!" << std::endl;
}
void Squeak()
{
	std::cout << "Squeak!!!" << std::endl;
}
void MuteQuack()
{
}
} // namespace QuackBehavior

namespace DanceBehavior
{
void DanceWaltz()
{
	std::cout << "I'm dancing waltz" << std::endl;
}
void DanceMinuet()
{
	std::cout << "I'm dancing minuet" << std::endl;
}
void DoNotDance()
{
}
} // namespace DanceBehavior

namespace FlyBehavior
{

FlyBehaviorFn MakeFlyWithWings()
{
	int flightCounter = 0;
	return [flightCounter]() mutable
	{
		++flightCounter;
		std::cout << "I'm flying with wings!" << std::endl;
		std::cout << "Flight count: " << flightCounter << std::endl;
	};
}
void FlyNoWay()
{
}
} // namespace FlyBehavior

class Duck
{

public:
	Duck(DanceBehaviorFn const& danceBehavior, FlyBehaviorFn const& flyBehavior,
		QuackBehaviorFn const& quackBehavior)
		: m_danceBehavior(danceBehavior)
		, m_flyBehavior(flyBehavior)
		, m_quackBehavior(quackBehavior)
	{
	}
	virtual ~Duck() = default;
	void Swim()
	{
		std::cout << "I'm swimming" << std::endl;
	}
	void Fly()
	{
		m_flyBehavior();
	}
	void Dance()
	{
		m_danceBehavior();
	}
	void Quack()
	{
		m_quackBehavior();
	}
	void SetFlyBehavior(FlyBehaviorFn const& flyBehavior)
	{
		m_flyBehavior = flyBehavior;
	}
	virtual void Display() const = 0;

private:
	DanceBehaviorFn m_danceBehavior;
	FlyBehaviorFn m_flyBehavior;
	QuackBehaviorFn m_quackBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(DanceBehavior::DanceWaltz, FlyBehavior::MakeFlyWithWings(), QuackBehavior::Quack)
	{
	}
	void Display() const override
	{
		std::cout << "I'm mallard duck!" << std::endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(DanceBehavior::DanceMinuet, FlyBehavior::MakeFlyWithWings(), QuackBehavior::Quack)
	{
	}
	void Display() const override
	{
		std::cout << "I'm redhead duck!" << std::endl;
	}
};

class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(DanceBehavior::DoNotDance, FlyBehavior::FlyNoWay, QuackBehavior::MuteQuack)
	{
	}
	void Display() const override
	{
		std::cout << "I'm decoy duck!" << std::endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(DanceBehavior::DoNotDance, FlyBehavior::FlyNoWay, QuackBehavior::Quack)
	{
	}
	void Display() const override
	{
		std::cout << "I'm model duck!" << std::endl;
	}
};

class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(DanceBehavior::DoNotDance, FlyBehavior::FlyNoWay, QuackBehavior::Squeak)
	{
	}
	void Display() const override
	{
		std::cout << "I'm rubber duck!" << std::endl;
	}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Dance();
	std::cout << std::endl;
}

int main()
{
	MallardDuck mallardDuck;
	PlayWithDuck(mallardDuck);

	mallardDuck.Fly();

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);

	modelDuck.SetFlyBehavior(FlyBehavior::MakeFlyWithWings());

	for (size_t i = 0; i < 5; i++)
	{
		modelDuck.Fly();
	}
	std::cout << std::endl;
	PlayWithDuck(modelDuck);

	modelDuck.SetFlyBehavior(FlyBehavior::FlyNoWay);
	PlayWithDuck(modelDuck);

	modelDuck.SetFlyBehavior(FlyBehavior::MakeFlyWithWings());
	PlayWithDuck(modelDuck);

	return 0;
}
