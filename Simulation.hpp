#pragma once
#include "Common.hpp"
#include <unordered_set>

enum class Simulation_Tool {
    Run,
    Set,
    Erase,
};

enum class Simulation_RunState {
    Start,
    Pause,
};

struct CellDelta {
    std::vector<int64_t> liveCells;
    std::vector<int64_t> deadCells;
};

const int dx[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
const int dy[8] = {-1, -1, -1, 0, 1, 1, 1, 0};

CellDelta calculateNextGeneration(const std::unordered_set<int64_t> &liveCells);

void run_Simulation(GameData& data);