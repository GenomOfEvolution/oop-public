#define CATCH_CONFIG_MAIN
#define _USE_MATH_DEFINES
#include <math.h>

#include <catch.hpp>
#include <iostream>

#include "CPoint.h"
#include "CCircle.h"
#include "CRectangle.h"
#include "CLineSegment.h";
#include "CTriangle.h"

namespace
{
	constexpr double invalidRadius = -10.2;

	constexpr uint32_t outlineColor = 0xffffff;
	constexpr uint32_t fillColor = 0xababab;
	constexpr double width = 100.0;
	constexpr double height = 50.0;
	constexpr double validRadius = 25.0;
	constexpr double triangleArea = 6.0;
	constexpr double trianglePerimetr = 12;


	CPoint firstPos = CPoint{ 3.0, 0.0 };
	CPoint secondPos = CPoint{ 0.0, 4.0 };
	CPoint thirdPos = CPoint{ 0.0, 0.0 };

	CPoint invalidFirstPos = CPoint{ 0.0, 0.0 };
	CPoint invalidSecondPos = CPoint{ 0.0, 4.0 };
	CPoint invalidThirdPos = CPoint{ 0.0, 0.0 };
}

TEST_CASE("Circle tests")
{
	CCircle circle(firstPos, validRadius, fillColor, outlineColor);
	CHECK(circle.GetCenter().GetX() == firstPos.GetX());
	CHECK(circle.GetCenter().GetY() == firstPos.GetY());

	CHECK(circle.GetArea() == (validRadius * M_PI * validRadius));
	CHECK(circle.GetPerimeter()  == (2 * M_PI * validRadius));

	CHECK(circle.GetFillColor() == fillColor);
	CHECK(circle.GetOutlineColor() == outlineColor);
}

TEST_CASE("Rectangle tests")
{
	CRectangle rect(firstPos, width, height, fillColor, outlineColor);
	CHECK(rect.GetLeftTop().GetX() == firstPos.GetX());
	CHECK(rect.GetLeftTop().GetY() == firstPos.GetY());

	CHECK(rect.GetRightBottom().GetX() == rect.GetLeftTop().GetX() + width);
	CHECK(rect.GetRightBottom().GetY() == rect.GetLeftTop().GetY() + height);

	CHECK(rect.GetHeight() == height);
	CHECK(rect.GetWidth() == width);

	CHECK(rect.GetArea() == height * width);
	CHECK(rect.GetPerimeter() == 2 * (height + width));

	CHECK(rect.GetFillColor() == fillColor);
	CHECK(rect.GetOutlineColor() == outlineColor);
}

TEST_CASE("Line tests")
{
	CLineSegment line(firstPos, secondPos, outlineColor);

	CHECK(line.GetArea() == 0);
	CHECK(line.GetStartPoint().GetX() == firstPos.GetX());
	CHECK(line.GetStartPoint().GetY() == firstPos.GetY());

	CHECK(line.GetEndPoint().GetX() == secondPos.GetX());
	CHECK(line.GetEndPoint().GetY() == secondPos.GetY());

	CHECK(line.GetPerimeter() == firstPos.GetDistanceTo(secondPos));

	CHECK(line.GetOutlineColor() == outlineColor);
}

TEST_CASE("Triangle tests")
{
	CTriangle triangle(firstPos, secondPos, thirdPos, fillColor, outlineColor);

	CHECK(triangle.GetVertex1().GetX() == firstPos.GetX());
	CHECK(triangle.GetVertex1().GetY() == firstPos.GetY());

	CHECK(triangle.GetVertex2().GetX() == secondPos.GetX());
	CHECK(triangle.GetVertex2().GetY() == secondPos.GetY());

	CHECK(triangle.GetVertex3().GetX() == thirdPos.GetX());
	CHECK(triangle.GetVertex3().GetY() == thirdPos.GetY());

	CHECK(triangle.GetArea() == triangleArea);
	CHECK(triangle.GetPerimeter() == trianglePerimetr);

	CHECK(triangle.GetFillColor() == fillColor);
	CHECK(triangle.GetOutlineColor() == outlineColor);

	CHECK_THROWS_AS(CTriangle(invalidFirstPos, invalidSecondPos, invalidThirdPos, fillColor, outlineColor), std::invalid_argument);
}