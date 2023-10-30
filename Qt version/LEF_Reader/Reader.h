#pragma once
#include <fstream>
#include <string>
#include "LEF.h"


namespace LEF {
	class Reader
	{
	private:
		std::fstream file;
		std::string path;
	public:
        void AssignFilePath();
		uint8_t WriteDatatoObject(LEF::Macro& dest_lef);
	};
};
