#pragma once
#include "data.h"

namespace SaveData {
	class SaveString {
		std::string data;
	public:
		SaveString(std::string save_string);

		void import_string(NodeData* node_data);
	};
}