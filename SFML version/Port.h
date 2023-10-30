#pragma once
#include "LEF.h"
#include "Layer.h"
#include "Rect.h"


namespace LEF {
	class Port
	{
	public:
		Layer pin_layer;
		Rect port_rect;
		//Port();
	};
};