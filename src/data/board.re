open Rationale;

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

let setTileLocation = (x: int, y: int, tile: Tiles.tile) => {...tile, x, y};

let createBoardFromIDs = (idBoard: list(list(int))) =>
  List.mapi(
    (y, row) =>
      List.mapi(
        (x, item) =>
          Option.fmap(setTileLocation(x, y), Tiles.getTileByID(item)),
        row
      ),
    idBoard
  );