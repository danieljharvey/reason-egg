open EggTypes;

let setTileLocation = (x: int, y: int, tile: tile) => {...tile, x, y};

let createBoardFromIDs = (idBoard: list(list(int))): list(list(option(tile))) =>
  List.mapi(
    (x, row) =>
      List.mapi(
        (y, item) =>
          Utils.optionMap(setTileLocation(x, y), Tiles.getTileByID(item)),
        row
      ),
    idBoard
  );

let cleanBoard = (optBoard: list(list(option(tile)))): board => {
  let validRows = List.map(Utils.sequence(Tiles.idTile), optBoard);
  let validBoard = Utils.sequence([], validRows);
  switch (validBoard) {
  | Some(board) => board
  | _ => []
  };
};

let getLevel = (levelID: int): board => {
  let numLevels = List.length(EggLevels.levels);
  let chooseLevelID = (levelID < 0 || levelID >= numLevels) ? 0 : levelID;
  cleanBoard(createBoardFromIDs(List.nth(EggLevels.levels, chooseLevelID)));
};

let getRandomLevelID = (): int => {
  let numLevels = List.length(EggLevels.levels);
  Random.int(numLevels);
};

let getBoardTiles = (board: board): list(tile) => {
    List.concat(board);
};

let getDrawTiles = (board: board): list(tile) => List.filter((tile: tile) => {tile.render}, getBoardTiles(board));

let getBoardSize = (board: board): int => List.length(board);

/* replace a tile on the board, return new board */
let changeTile = (board: board, newTile: tile): board => 
  List.mapi((x, row) => 
    List.mapi((y, tile) => {
      (x == newTile.x && y == newTile.y) ? newTile : tile
    }, row), board);

/* get a tile on the board */
let getTile = (x: int, y: int, board: board): tile => {
  let boardSize = List.length(board);
  let nX = (x + boardSize) mod boardSize;
  let nY = (y + boardSize) mod boardSize;
  List.find(tile => (tile.x == nX && tile.y == nY), getBoardTiles(board));
};

let changeTileByID = (board: board, x: int, y: int, id: int): board => {
  let newTile = Tiles.getTileByID(id);
  switch newTile {
  | Some(tile) => {
    let positionTile = {
      ...tile,
      x: x,
      y: y
    };
    changeTile(board, positionTile);
  }
  | _ => board
  };
};

type fullCoords = {
  x: int,
  y: int
};

let getActualPosition = (coords: coords) : fullCoords => {
  {
    x: (coords.x * EggConstants.tileSize) + coords.offsetX,
    y: (coords.y * EggConstants.tileSize) + coords.offsetY
  };
};
