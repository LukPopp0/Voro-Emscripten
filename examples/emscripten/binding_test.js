import createVoro from "../../bin/voro.js";

console.log("WebAssembly loaded!");

const points = [
  [0, -4.99995, 0],
  [-3.6899379709983346, -2.5739679448534636, -4.99995],
  [3.576031624417964, -2.546234552807669, -4.99995],
  [4.99995, -2.172426002791485, 1.5834713245347982],
  [0.037275242244040996, -2.071104653605047, 4.99995],
  [-4.99995, -2.182976164456667, 1.665892796700179],
  [-0.03727524224404482, 2.071104653605047, -4.99995],
  [4.99995, 2.1829761644566674, -1.6658927967001833],
  [3.689937970998336, 2.5739679448534636, 4.99995],
  [-3.5760316244179706, 2.546234552807671, 4.99995],
  [-4.99995, 2.1724260027914855, -1.5834713245348024],
  [1.974399169327309, 4.99995, 0.6252871464344901],
];

const Voro = await createVoro();

const container = new Voro.Container(-5, 5, -5, 5, -5, 5, 2, 2, 2);
const pointStorage = new Voro.PointStorage();
points.forEach((p) => pointStorage.addPoint(p[0], p[1], p[2]));
const cells = container.computeCells(pointStorage);

console.log({cells})
console.log(cells.size());
console.log(cells.get(0));
