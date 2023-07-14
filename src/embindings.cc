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
  int x_min, x_max, y_min, y_max, z_min, z_max, n_x, n_y, n_z;

  Container()
      : x_min(-10), x_max(10), y_min(-10), y_max(10), z_min(-10), z_max(10),
        n_x(1), n_y(1), n_z(1) {}
  Container(int x_min, int x_max, int y_min, int y_max, int z_min, int z_max,
            int n_x, int n_y, int n_z)
      : x_min(x_min), x_max(x_max), y_min(y_min), y_max(y_max), z_min(z_min),
        z_max(z_max), n_x(n_x), n_y(n_y), n_z(n_z) {}

  std::vector<CellExport> compute_cells(PointStorage points) {
    const int init_mem = 8;

    voro::container con(x_min, x_max, y_min, y_max, z_min, z_max, n_x, n_y, n_z,
                        false, false, false, init_mem);

    assert(points._data.size() % 3 == 0);

    for (int i = 0; i < int(points._data.size() / 3); ++i) {
      con.put(i, points._data[i * 3 + 0], points._data[i * 3 + 1],
              points._data[i * 3 + 2]);
    }

    // con.print_custom("%i | %q | %s | %t | %p", "output.txt");
    std::vector<CellExport> cells;
    con.compute_cell_data(cells);

    return cells;
  }
};

#ifdef EMSCRIPTEN
EMSCRIPTEN_BINDINGS(vorojs) {
  emscripten::register_vector<float>("VectorFloat");
  emscripten::register_vector<int>("VectorInt");
  emscripten::register_vector<std::vector<int>>("VectorVectorInt");
  emscripten::register_vector<CellExport>("VectorCellExport");
  emscripten::class_<CellExport>("CellExport")
      .constructor<>()
      .property("particleID", &CellExport::particleID)
      .property("x", &CellExport::x)
      .property("y", &CellExport::y)
      .property("z", &CellExport::z)
      .property("nFaces", &CellExport::nFaces)
      .property("vertices", &CellExport::vertices)
      .property("faces", &CellExport::faces);
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

#ifndef EMSCRIPTEN
int main() {
  std::vector<float> points{0,
                            -4.99995,
                            0,
                            -3.6899379709983346,
                            -2.5739679448534636,
                            -4.99995,
                            3.576031624417964,
                            -2.546234552807669,
                            -4.99995,
                            4.99995,
                            -2.172426002791485,
                            1.5834713245347982,
                            0.037275242244040996,
                            -2.071104653605047,
                            4.99995,
                            -4.99995,
                            -2.182976164456667,
                            1.665892796700179,
                            -0.03727524224404482,
                            2.071104653605047,
                            -4.99995,
                            4.99995,
                            2.1829761644566674,
                            -1.6658927967001833,
                            3.689937970998336,
                            2.5739679448534636,
                            4.99995,
                            -3.5760316244179706,
                            2.546234552807671,
                            4.99995,
                            -4.99995,
                            2.1724260027914855,
                            -1.5834713245348024,
                            1.974399169327309,
                            4.99995,
                            0.6252871464344901};

  PointStorage p = PointStorage();
  p.add_points(points);
  Container c = Container();
  c.compute_cells(p);

  return 0;
}
#endif
