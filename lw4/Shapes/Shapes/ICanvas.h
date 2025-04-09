#pragma once
#include "CPoint.h"
#include <iostream>
#include <vector>

class ICanvas
{
public:
	virtual void DrawLine(CPoint startPoint, CPoint endPoint, uint32_t lineColor) const = 0;
	virtual void FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor, uint32_t outlineColor) const = 0;
	virtual void FillRect(CPoint coordinates, double width, double height, uint32_t fillColor, uint32_t outlineColor) const = 0;
	virtual void FillCircle(CPoint center, double radius, uint32_t fillColor, uint32_t outlineColor) const = 0;

	virtual ~ICanvas() = default;
};

