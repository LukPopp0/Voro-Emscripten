mkdir -p bin
emcc\
  -I ./src\
  -l embind\
  -s MODULARIZE=1\
  -s EXPORT_ES6=1\
  -s 'EXPORT_NAME="voro"'\
  -s ASSERTIONS=1\
  -s TOTAL_MEMORY=256MB\
  -s ALLOW_MEMORY_GROWTH=1\
  -Os\
  --emit-tsd ./voro_raw.d.ts\
  -o ./bin/voro_raw.js\
  ./src/embindings.cc ./src/voro++.cc
