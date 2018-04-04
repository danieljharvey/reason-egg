open EggTypes;

/*
import { Board } from "../objects/Board";
import { BoardSize } from "../objects/BoardSize";
import { Coords } from "../objects/Coords";
import { Player } from "../objects/Player";
import { Tile } from "../objects/Tile";
import { Utils } from "./Utils";

import { getTile as getOriginalTile, tiles as allTiles } from "../data/TileSet";

// map is just a class full of functions that is created for manipulating the board
// should not contain any meaningful state of it's own (currently does, but reducing this)

export const calcBoardSize = (board: Board): number => {
  return board.getLength();
};

export const correctForOverflow = (board: Board, coords: Coords): Coords => {
  const boardSize = calcBoardSize(board);
  return Utils.correctForOverflow(coords, new BoardSize(boardSize));
};

// is intended next tile empty / a wall?
// need to make this wrap around the board
export const checkTileIsEmpty = (board: Board, x, y): boolean => {
  const tile = getTile(board, x, y);
  return tile.background;
};

// find random tile of type that is NOT at currentCoords
export const findTile = (board: Board, currentCoords: Coords, id): Tile => {
  const tiles = board.getAllTiles();
  const teleporters = tiles.filter(tile => {
    if (tile.x === currentCoords.x && tile.y === currentCoords.y) {
      return false;
    }
    return tile.id === id;
  });
  if (teleporters.size === 0) {
    return null;
  }
  const chosenID = Math.floor(Math.random() * teleporters.size);

  const newTile = teleporters.get(chosenID); // this is an Immutable list so needs to use their functions
  return newTile;
};

export const shrinkBoard = (board: Board): Board => {
  const boardSize = new BoardSize(board.getLength());
  const shrunkBoardSize = boardSize.shrink();
  return correctBoardSizeChange(board, shrunkBoardSize);
};

export const growBoard = (board: Board): Board => {
  const boardSize = new BoardSize(board.getLength());
  const grownBoardSize = boardSize.grow();
  return correctBoardSizeChange(board, grownBoardSize);
};

// board is current board
// boardSize is intended board size
// returns new Board
export const correctBoardSizeChange = (
  board: Board,
  boardSize: BoardSize
): Board => {
  const newBoard = [];

  const currentWidth = board.getLength();

  const currentHeight = currentWidth;

  for (let x = 0; x < boardSize.width; x++) {
    newBoard[x] = [];
    for (let y = 0; y < boardSize.height; y++) {
      if (x < currentWidth && y < currentHeight) {
        // using current board
        const tile = board.getTile(x, y);
        newBoard[x][y] = tile;
      } else {
        // adding blank tiles
        const tile = cloneTile(1);
        newBoard[x][y] = tile;
      }
    }
  }
  return new Board(newBoard);
};

export const generateBlankBoard = (boardSize: BoardSize): Board => {
  const board = [];

  for (let x = 0; x < boardSize.width; x++) {
    board[x] = [];
    for (let y = 0; y < boardSize.height; y++) {
      const blankTile = cloneTile(1);
      const positionedTile = blankTile.modify({
        x,
        y
      });
      board[x][y] = positionedTile;
    }
  }
  return new Board(board);
};

export const getTileWithCoords = (board: Board, coords: Coords): Tile => {
  const fixedCoords = correctForOverflow(board, coords);
  const { x, y } = fixedCoords;
  return board.getTile(x, y);
};

export const changeTile = (board: Board, coords: Coords, tile: Tile): Board => {
  return board.modify(coords.x, coords.y, tile);
};




export const cloneTile = (id): Tile => {
  const prototypeTile = getPrototypeTile(id);
  return new Tile(prototypeTile); // create new Tile object with these
};

export const getRandomTile = (tiles): Tile => {
  const randomProperty = obj => {
    const randomKey = Utils.getRandomObjectKey(obj);
    return cloneTile(randomKey);
  };

  (Object as any).entries(tiles).filter(([key, tile]) => {
    if (tile.dontAdd) {
      delete tiles[key];
    }
    return true;
  });
  return randomProperty(tiles);
};

// swap two types of tiles on map (used by pink/green switching door things)
export const switchTiles = (board: Board, id1, id2): Board => {
  const tiles = board.getAllTiles();
  return tiles.reduce((currentBoard, tile) => {
    if (tile.id === id1) {
      const newTile = cloneTile(id2);
      const positionTile = newTile.modify({
        x: tile.x,
        y: tile.y
      });
      return currentBoard.modify(tile.x, tile.y, positionTile);
    } else if (tile.id === id2) {
      const newTile = cloneTile(id1);
      const positionTile = newTile.modify({
        x: tile.x,
        y: tile.y
      });
      return currentBoard.modify(tile.x, tile.y, positionTile);
    }
    return currentBoard;
  }, board);
};

*/

let getNewPlayerDirection = (direction: coords, clockwise: bool): coords => {
  if (direction.x !== 0 || direction.y !== 0) {
    direction;
  } else {
    clockwise ? { ...Player.defaultCoords,  x: 1 } : { ...Player.defaultCoords,  x: -1 };
  };
};


let translateRotation = (
  boardSize: int,
  coords: coords,
  clockwise: bool
): coords => {
  let width = boardSize - 1;
  let height = boardSize - 1;

  if (clockwise) {
    /* 0,0 -> 9,0
    // 9,0 -> 9,9
    // 9,9 -> 0,9
    // 0,9 -> 0,0 */
    {
      ...coords,
      x: width - coords.y,
      y: coords.x
    };
  } else {
    /* 0,0 -> 0,9
    // 0,9 -> 9,9
    // 9,9 -> 9,0
    // 9,0 -> 0,0 */
    {
      ...coords,
      x: coords.y,
      y: height - coords.x
    };
  };
};


let rotatePlayer = (
  boardSize: int,
  player: player,
  clockwise: bool
): player => {
  let newCoords = translateRotation(boardSize, player.coords, clockwise);

  {
    ...player,
    coords: {
      ...newCoords,
      offsetX: 0,
      offsetY: 0
    },
    direction: getNewPlayerDirection(player.direction, clockwise)
  };
};

/*// rotates board, returns new board and new renderAngle
// really should be two functions */
let rotateBoard = (board: board, clockwise: bool): board => {
  let tiles = Board.getBoardTiles(board);

  let boardSize = List.length(board) - 1;

  let rotatedBoard = List.fold_right((tile, currentBoard) => {
    let coords: coords = { ...Player.defaultCoords, x: tile.x, y: tile.y };
    let newCoords = translateRotation(boardSize, coords, clockwise);
    let newTile = {
      ...tile,
      x: newCoords.x,
      y: newCoords.y
    };
    Board.changeTile(newTile, currentBoard);
  }, tiles, board);

  rotatedBoard;
};


let changeRenderAngle = (renderAngle: float, clockwise: bool): float => {
  if (clockwise) {
    let clockwiseAngle = renderAngle +. 90.0;
    (clockwiseAngle > 360.0) ? clockwiseAngle -. 360.0 : clockwiseAngle;
  } else {
    let antiClockwiseAngle = renderAngle -. 90.0;
    (antiClockwiseAngle < 0.0) ? 360.0 +. antiClockwiseAngle : antiClockwiseAngle;
  };
};

/*
export const makeBoardFromArray = (boardArray: Tile[][] = []): Board => {
  const newBoard = boardArray.map((column, mapX) => {
    return column.map((item, mapY) => {
      const newTile = cloneTile(item.id);
      return newTile.modify({
        x: mapX,
        y: mapY
      });
    });
  });
  return new Board(newBoard);
};

export const generateRandomBoard = (boardSize: BoardSize): Board => {
  const boardArray = [];

  for (let x = 0; x < boardSize.width; x++) {
    boardArray[x] = [];
    for (let y = 0; y < boardSize.height; y++) {
      const blankTile = getRandomTile(allTiles);
      const positionedTile = blankTile.modify({
        x,
        y
      });
      boardArray[x][y] = blankTile;
    }
  }
  return new Board(boardArray);
};

export const getTile = (board: Board, x: number, y: number) => {
  const coords = new Coords({ x, y });
  return getTileWithCoords(board, coords);
};

export const getPrototypeTile = (id: number): object => {
  return getOriginalTile(id);
};



*/