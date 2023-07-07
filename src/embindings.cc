// #include "emscripten/bind.h"
#include "voro++.hh"
#include <emscripten/bind.h>
#include <iostream>
#include <vector>

class PointStorage {
public:
  PointStorage() {}
  ~PointStorage() { _data.clear(); }
  std::vector<float> _data;
  void add_point(float x, float y, float z) {
    _data.insert(_data.end(), {x, y, z});
  }

  void add_points(std::vector<float> pts) {
    _data.insert(_data.end(), pts.begin(), pts.end());
  }
};

void compute_voro_cells(PointStorage points, int x_min = -10, int x_max = 10,
                        int y_min = -10, int y_max = 10, int z_min = -10,
                        int z_max = 10, int n_x = 2, int n_y = 2, int n_z = 2) {
  const int init_mem = 8;

  voro::container con(x_min, x_max, y_min, y_max, z_min, z_max, n_x, n_y, n_z,
                      false, false, false, init_mem);

  assert(points._data.size() % 3 == 0);

  for (int i = 0; i < points._data.size() / 3; ++i) {
    std::cout << "Adding: " << points._data[i * 3 + 0] << " \t"
              << points._data[i * 3 + 1] << " \t" << points._data[i * 3 + 2]
              << std::endl;
    con.put(i, points._data[i * 3 + 0], points._data[i * 3 + 1],
            points._data[i * 3 + 2]);
  }

  return con.compute_all_cells();
}

#ifdef EMSCRIPTEN
EMSCRIPTEN_BINDINGS(vorojs) {
  emscripten::register_vector<float>("VectorFloat");
  emscripten::class_<PointStorage>("PointStorage")
      .constructor<>()
      .property("data", &PointStorage::_data)
      .function("addPoint", &PointStorage::add_point)
      .function("addPoints", &PointStorage::add_points);
  emscripten::function("computeVoroCells", &compute_voro_cells);
}
#endif

int main() {
  std::cout << "Voro++ loaded." << std::endl;
  return 0;
}