#pragma once
#include <string>
#include <vector>
#include "LEF.h"
#include "Point.h"
#include "Pin.h"
#include "Obs.h"


namespace LEF {
	class Macro
	{
	public:
		std::string name;
		double width;
		double height;
		Point origin;
		int number_of_pins;
		std::vector<LEF::Pin> pin_array;
		Obs obs;
		Macro();
		void show_data();
	};
};

