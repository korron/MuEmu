#pragma once

#define MAX_MINI_MAP 63

void InitMiniMap();
void MiniMapCore();
void MiniMapLoad();
bool MiniMapCheck(int map);
bool MiniMapFileCheck(int map);
