type board = list(list(Tiles.tile));

let idBoard = [
  [1, 2, 3, 4, 12, 1, 2, 3, 4],
  [1, 2, 3, 4, 12, 1, 2, 3, 4],
  [1, 2, 3, 4, 12, 1, 2, 3, 4],
  [1, 2, 3, 4, 12, 1, 2, 3, 4],
  [1, 2, 3, 4, 12, 1, 2, 3, 4],
  [1, 2, 3, 4, 12, 1, 2, 3, 4],
  [1, 2, 3, 4, 12, 1, 2, 3, 4]
];

let createBoardFromIDs = (idBoard: list(list(int))) =>
  List.map(_row => List.map(item => Tiles.getTileByID(item)), idBoard);