#pragma once
#include <iostream>
#include <map>
#include <functional>
#include <string>
#include <vector>
#include <memory>

#include "IShape.h"

class CShapesController
{
public:
	CShapesController(std::istream& input, std::ostream& output);
	void HandleUserInput();

private:
	std::istream& m_input;
	std::ostream& m_output;

	std::vector<std::shared_ptr<IShape>> m_shapes;

	using Handler = std::function<void()>;
	using ActionMap = std::map<std::string, Handler>;
	const ActionMap m_actionMap;

	void AddCircle();
	void AddRectangle();
	void AddTriangle();
	void AddLine();

	uint32_t ColorToInt(const std::string& line);
};
