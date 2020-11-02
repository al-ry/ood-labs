#pragma once
#include <optional>
#include <memory>
class RGBAColor
{
public:
	RGBAColor(float r, float g, float b, float a)
		: r(r)
		, g(g)
		, b(b)
		, a(a)
	{
	}
	RGBAColor() = default;
	float r = 0, g = 0, b = 0, a;
	bool operator==(const RGBAColor& color) const
	{
		return ((r == color.r) && (g == color.g) && (b == color.b) && (a == color.a));
	}

	bool operator!=(const RGBAColor& color) const
	{
		return !(*this == color);
	}
};


class IStyle
{
public:

	virtual std::optional<bool> IsEnabled() = 0;
	virtual void Enable(bool enable) = 0;

	virtual std::optional<RGBAColor> GetColor() const = 0;
	virtual void SetColor(const RGBAColor& color) = 0;
	virtual ~IStyle() = default;
};

typedef std::shared_ptr<IStyle> StylePtr;