#pragma once
#include <stdint.h>
#include <vector>
#include <string>
#include "math/Vector3.h"

enum class MapchipType {
	None,
	Wall,
	//Goal,
	//Start,
};

struct MapchipData {
	std::vector<std::vector<MapchipType>> data;
};

class Mapchip {

private:
	MapchipData mapchipData_;


public:
	Mapchip();
	~Mapchip();
	void Initialize();
	void Update();
	static inline const float kBlockWidth = 2.0f;
	static inline const float kBlockHeight = 2.0f;
	static inline const uint32_t kNumBlockHorizontal = 900;
	static inline const uint32_t kNumBlockVertical = 11;
	struct IndexSet {
		uint32_t xIndex;
		uint32_t yIndex;
	};
	struct Rect {
		float left;
		float right;
		float bottom;
		float top;
	};
	void ResetMapchipData();
	void LoadMapchipCsv(const std::string& filePath);
	MapchipType GetMapchipTypeByIndex(uint32_t xIndex, uint32_t yIndex);
	KamataEngine::Vector3 GetMapchipPositionByIndex(uint32_t xIndex, uint32_t yIndex);
	uint32_t GetNumBlockHorizontal() const;
	uint32_t GetNumBlockVertical() const;

	IndexSet GetIndexSetByPosition(const KamataEngine::Vector3& position);
	Rect GetRectByIndex(uint32_t xIndex, uint32_t yIndex);

};
