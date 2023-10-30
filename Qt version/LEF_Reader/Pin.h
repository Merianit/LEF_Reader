#pragma once
#include <string>
#include <vector>
#include "LEF.h"
#include "Port.h"

namespace LEF {
	class Pin
	{
	public:
		std::string name;
		std::string direction;
		std::string type;
		std::vector<LEF::Port> port_array;
		int number_of_ports;
		Pin();
	};
};

