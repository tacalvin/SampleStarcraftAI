#pragma once

#include <BWAPI.h>
#include <queue>
#include <vector>
#include <BWTA.h>

struct buildingCommand
{
	BWAPI::Unit m_buildingWorker;
	BWAPI::UnitType m_building;
	BWAPI::TilePosition m_buildingLocation;
	int m_lastCommand;
	//forgive this line
	
	buildingCommand(BWAPI::Unit buildingWorker, BWAPI::UnitType building, BWAPI::TilePosition buildingLocation) : m_buildingWorker(buildingWorker), m_building(building), m_buildingLocation(buildingLocation), m_lastCommand(0) {}
};

class BuildingManager
{
public:
	BuildingManager();

	//for when we want to queue a building
	void buildQueue(BWAPI::UnitType building);
	//for when we want to build something now, fuck build orders
	void buildAsync(BWAPI::UnitType building);

	//this is used to REMOVE from the currently building list
	void buildingStarted(BWAPI::Unit building);
	void update();
	int getReservedMinerals();
	int getReservedGas();
	int getAvailableMinerals();
	int getAvailableGas();


	//TODO:: get worker from latest available expansion
	BWAPI::Unit getAvailableWorker();
	BWAPI::Unit getAvailableWorker(BWAPI::Position p);

	void setNextExpansionLocation(BWAPI::TilePosition expand);

	bool isAreaExplored(BWAPI::TilePosition area);

protected:

	BWAPI::TilePosition m_nextExpandLocation;
	void beginConstructingBuilding(BWAPI::UnitType building);
	void beginConstructingBuilding(BWAPI::UnitType building, BWAPI::TilePosition spot);

	int reservedMinerals;
	int reservedGas;

	std::queue<BWAPI::UnitType> m_buildingQueue;
	std::vector<BWAPI::UnitType> m_buildingsToBuild;

	//convert this into a map or something eventually - associative array
	std::vector<buildingCommand> m_currentlyBuilding;

};



