#include "Mapchip.h"
#include <map>
#include <fstream>
#include <sstream>
#include <cassert>

using namespace KamataEngine;

Mapchip::Mapchip() {}

Mapchip::~Mapchip() {}

void Mapchip::Initialize() {}
void Mapchip::Update() {}

namespace {
std::map<std::string, MapchipType> mapchipTable = {
    {"0", MapchipType::None },
    {"1", MapchipType::Wall },
    //{"2", MapchipType::Goal },
    //{"3", MapchipType::Start},
};
}

uint32_t Mapchip::GetNumBlockHorizontal() const { return kNumBlockHorizontal; }
uint32_t Mapchip::GetNumBlockVertical() const { return kNumBlockVertical; }

void Mapchip::ResetMapchipData() {
	mapchipData_.data.clear();
	mapchipData_.data.resize(kNumBlockVertical);
	for (std::vector<MapchipType>& mapChipDataLine : mapchipData_.data) {
		mapChipDataLine.resize(kNumBlockHorizontal);
	}
}

void Mapchip::LoadMapchipCsv(const std::string& filePath) { 
	ResetMapchipData();
	std::ifstream file;
	file.open(filePath);
	assert(file.is_open());

	std::stringstream mapChipCsv;

	mapChipCsv << file.rdbuf();
	file.close();

	for (uint32_t i = 0; i < kNumBlockVertical; ++i) {
		std::string line;
		std::getline(mapChipCsv, line);
		std::istringstream line_stream(line);
		
		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
			
			std::string word;
			getline(line_stream, word, ',');

			if (mapchipTable.contains(word)) {
				mapchipData_.data[i][j] = mapchipTable[word];
			} 
			//else {
			//	mapchipData_.data[i][j] = MapchipType::None; // Default to None if not found
			//}
			
		}
	}
}

MapchipType Mapchip::GetMapchipTypeByIndex(uint32_t xIndex, uint32_t yIndex) {
	if (xIndex < 0 || kNumBlockHorizontal - 1 < xIndex) {
		return MapchipType::None; // Out of bounds
	}
	if (yIndex < 0 || kNumBlockVertical - 1 < yIndex) {
		return MapchipType::None; // Out of bounds
	}
	return mapchipData_.data[yIndex][xIndex];
}

KamataEngine::Vector3 Mapchip::GetMapchipPositionByIndex(uint32_t xIndex, uint32_t yIndex) { 
	return Vector3(kBlockWidth * xIndex, kBlockHeight * (kNumBlockVertical - 1 - yIndex), 0);
}



//std::map<MapchipType, std::string> mapchipTypeToTexturePath = {
//	{MapchipType::None, "uvChecker.png"},
//	{MapchipType::Wall, "uvChecker.png"},
//	{MapchipType::Goal, "uvChecker.png"},
//	{MapchipType::Start, "uvChecker.png"},
//};