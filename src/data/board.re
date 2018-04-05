open EggTypes;

let idBoard = One.board;

let setTileLocation = (x: int, y: int, tile: tile) => {...tile, x, y};

let createBoardFromIDs = (idBoard: list(list(int))): list(list(option(tile))) =>
  List.mapi(
    (y, row) =>
      List.mapi(
        (x, item) =>
          EggUtils.optionMap(setTileLocation(x, y), Tiles.getTileByID(item)),
        row
      ),
    idBoard
  );

let cleanBoard = (optBoard: list(list(option(tile)))): board => {
  let validRows = List.map(EggUtils.sequence(Tiles.idTile), optBoard);
  let validBoard = EggUtils.sequence([], validRows);
  switch (validBoard) {
  | Some(board) => board
  | _ => []
  };
};

let board = cleanBoard(createBoardFromIDs(idBoard));

let getBoardTiles = (board: board): list(tile) => {
    List.concat(board);
};

/* replace a tile on the board, return new board */
let changeTile = (newTile: tile, board: board): board => 
  List.mapi((y, row) => 
    List.mapi((x, tile) => {
      (x == newTile.x && y == newTile.y) ? newTile : tile
    }, row), board);

/* get a tile on the board */
let getTile = (x: int, y: int, board: board): option(tile) => {
  let found = List.filter(tile => (tile.x == x && tile.y == y), getBoardTiles(board));
  (List.length(found) > 0) ? Some(List.hd(found)) : None;
};