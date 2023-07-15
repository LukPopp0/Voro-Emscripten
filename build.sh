mkdir -p bin
emcc ./src/embindings.cc ./src/voro++.cc\
  --bind\
  -Os\
  -o ./bin/voro_raw.js\
  -I ./src\
  -s EXPORT_ES6=1\
  -s MODULARIZE=1\
  -s 'EXPORT_NAME="voro"'