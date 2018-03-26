open EggTypes;

let idBoard = [
  [1, 2, 3, 4, 12, 1, 2, 3,1,1],
  [1, 2, 3, 4, 12, 1, 2, 3,1,1],
  [1, 2, 3, 4, 12, 1, 2, 3,1,1],
  [1, 2, 3, 4, 12, 1, 2, 3,1,1],
  [1, 2, 3, 4, 12, 1, 2, 3,1,1],
  [1, 2, 3, 4, 12, 1, 2, 3,1,1],
  [1, 2, 3, 4, 12, 1, 2, 3,1,1],
  [1, 2, 3, 4, 12, 1, 2, 3,1,1],
  [1, 2, 3, 4, 12, 1, 2, 3,1,1],
  [1, 2, 3, 4, 12, 1, 2, 3,1,1]
];

let setTileLocation = (x: int, y: int, tile: tile) => {
  {...tile, x, y};
};


let createBoardFromIDs = (idBoard: list(list(int))) =>
  List.mapi(
    (y, row) =>
      List.mapi(
        (x, item) => {
          EggUtils.optionMap(setTileLocation(x, y), Tiles.getTileByID(item))
        },
        row
      ),
    idBoard
  );