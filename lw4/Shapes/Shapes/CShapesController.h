#pragma once
#include <iostream>
#include <map>
#include <functional>
#include <string>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "IShape.h"


class CShapesController
{
public:
	CShapesController(std::istream& input, std::ostream& output);

	void DrawAllShapes(sf::RenderWindow& window);
	void HandleUserInput();
	void PrintTaskResult();

private:
	std::istream& m_input;
	std::ostream& m_output;

	std::vector<std::unique_ptr<IShape>> m_shapes;

	using Handler = std::function<void()>;
	using ActionMap = std::map<std::string, Handler>;
	const ActionMap m_actionMap;

	void AddCircle();
	void AddRectangle();
	void AddTriangle();
	void AddLine();

	// unique ptr
	IShape* GetShapeWithMaxArea() const;
	IShape* GetShapeWithMinPerimeter() const;

	uint32_t ColorToInt(const std::string& line);
};
