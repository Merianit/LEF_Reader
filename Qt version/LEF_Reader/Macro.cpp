#include "LEF.h"
#include "Macro.h"
#include <iostream>

namespace LEF {
	Macro::Macro()
	{
		width = 0.0;
		height = 0.0;
		number_of_pins = 0;
	}

	void Macro::show_data()
	{
		std::cout << "Macro.name: " << name << std::endl;
		std::cout << "Macro.width: " << width << std::endl;
		std::cout << "Macro.height: " << height << std::endl;
		std::cout << "Data.origin: " << origin.x << " " << origin.y << std::endl;
		std::cout << "Data.number_of_pins: " << number_of_pins << std::endl;
		for (int i = 0; i < number_of_pins; i++) {
			std::cout << pin_array[i].name << std::endl;
			std::cout << pin_array[i].direction << std::endl;
			std::cout << pin_array[i].type << std::endl;
			for (int j = 0; j < pin_array[i].number_of_ports; j++) {
				std::cout << pin_array[i].port_array[j].pin_layer.name << std::endl;
				std::cout << pin_array[i].port_array[j].port_rect.pt1.x << " " << pin_array[i].port_array[j].port_rect.pt1.y << std::endl;
				std::cout << pin_array[i].port_array[j].port_rect.pt2.x << " " << pin_array[i].port_array[j].port_rect.pt2.y << std::endl;
			}
			std::cout << "\n";
		}
//		std::cout << "OBS data: " << std::endl;
//		for (int i = 0; i < obs.obs_rects.size(); i++) {
//			std::cout << obs.obs_rects[i].pt1.x << " " << obs.obs_rects[i].pt1.y << " " << obs.obs_rects[i].pt2.x << " " << obs.obs_rects[i].pt2.y << std::endl;
//		}
	}

};
