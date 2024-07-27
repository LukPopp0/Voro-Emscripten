#pragma once
#include <vector>

struct CellExport {
  int particleID;
  float x;
  float y;
  float z;
  int nFaces;
  std::vector<float> vertices;
  std::vector<std::vector<int>> faces;
  std::vector<int> neighbors;
};
