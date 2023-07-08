#include "voro++.hh"

#ifdef EMSCRIPTEN
#include <emscripten/bind.h>
#endif

#include <iostream>
#include <vector>

class PointStorage {
public:
  PointStorage() {}
  ~PointStorage() { _data.clear(); }
  std::vector<float> _data;
  void add_point(float x, float y, float z) {
    _data.push_back(x);
    _data.push_back(y);
    _data.push_back(z);
  }

  void add_points(std::vector<float> pts) {
    _data.insert(_data.end(), pts.begin(), pts.end());
  }
};

class Container {

public:
  int x_min = -10;
  int x_max = -10;
  int y_min = -10;
  int y_max = -10;
  int z_min = -10;
  int z_max = -10;
  int n_x = 1;
  int n_y = 1;
  int n_z = 1;

  Container() {}
  Container(int x_min, int x_max, int y_min, int y_max, int z_min, int z_max,
            int n_x, int n_y, int n_z)
      : x_min(x_min), x_max(x_max), y_min(y_min), y_max(y_max), z_min(z_min),
        z_max(z_max), n_x(n_x), n_y(n_y), n_z(n_z) {}

  void compute_cells(PointStorage points) {
    const int init_mem = 8;

    voro::container con(x_min, x_max, y_min, y_max, z_min, z_max, n_x, n_y, n_z,
                        false, false, false, init_mem);

    assert(points._data.size() % 3 == 0);

    for (int i = 0; i < int(points._data.size() / 3); ++i) {
      std::cout << "Adding: " << points._data[i * 3 + 0] << " \t"
                << points._data[i * 3 + 1] << " \t" << points._data[i * 3 + 2]
                << std::endl;
      con.put(i, points._data[i * 3 + 0], points._data[i * 3 + 1],
              points._data[i * 3 + 2]);
    }

    // con.print_custom("%i | %q | %s | %t | %p", "output.txt");
    std::vector<CellExport> cells;
    con.compute_cell_data(cells);

    for(auto cell : cells) {
      std::cout << cell.particleID << " " << cell.nFaces << std::endl;
    }
  }
};

#ifdef EMSCRIPTEN
EMSCRIPTEN_BINDINGS(vorojs) {
  emscripten::register_vector<float>("VectorFloat");
  emscripten::class_<PointStorage>("PointStorage")
      .constructor<>()
      .property("data", &PointStorage::_data)
      .function("addPoint", &PointStorage::add_point)
      .function("addPoints", &PointStorage::add_points);
  emscripten::class_<Container>("Container")
      .constructor<>()
      .constructor<int, int, int, int, int, int, int, int, int>()
      .property("xMin", &Container::x_min)
      .property("xMax", &Container::x_max)
      .property("yMin", &Container::y_min)
      .property("yMax", &Container::y_max)
      .property("zMin", &Container::z_min)
      .property("zMax", &Container::z_max)
      .property("nX", &Container::n_x)
      .property("nY", &Container::n_y)
      .property("nZ", &Container::n_z)
      .function("computeCells", &Container::compute_cells);
}
#endif

int main() {
  std::cout << "Voro++ loaded." << std::endl;
  return 0;
}
