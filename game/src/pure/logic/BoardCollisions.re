open EggTypes;

type splitItem = {
  value: int,
  direction: coords
};

let playerFromItem = (player: player, item: splitItem): option(player) => {
  EggUtils.optionMap(playerType => {
    {
      ...playerType,
      coords: player.coords,
      direction: item.direction,
      value: item.value,
      lastAction: "split"
    };
  }, Player.getPlayerTypeByValue(item.value));
};

/* how shall we split these eggs */
let getValuesAndDirections = (value: int): list(splitItem) => {
  if (value === 2) {
    [
      {value:1, direction: {...Player.defaultCoords, x: -1}},
      {value:1, direction: {...Player.defaultCoords, x: 1}}
    ];
  } else if (value === 3) {
    [
      {value:1, direction: {...Player.defaultCoords, x: -1}},
      {value:1, direction: {...Player.defaultCoords, x: 1}},
      {value:1, direction: Player.defaultCoords}
    ];
  } else if (value === 4) {
    [
      {value:2, direction: {...Player.defaultCoords, x: -1}},
      {value:2, direction: {...Player.defaultCoords, x: 1}}
    ];
  } else {
    [
      {value:1, direction: {...Player.defaultCoords, x: -1}}
    ];
  }
};

let splitPlayer = (player: player): option(list(player)) => {
  EggUtils.sequence(
    Player.defaultPlayer,  
    List.map(playerFromItem(player),getValuesAndDirections(player.value))
  );
};

let isSplitterTile = (tile: tile) => tile.action === SplitEggs;

let getSplitterTiles = (board: board) => {
  List.filter(isSplitterTile, Board.getBoardTiles(board));
};

let isPlayerOnTile = (player: player, tile: tile): bool => {
  player.coords.x === tile.x && player.coords.y === tile.y;
};

let getCollidedTiles = (board: board, player: player) => {
  List.filter(isPlayerOnTile(player), getSplitterTiles(board));
};

let isPlayerValueHighEnough = (player: player): bool => {
  player.value > 1;
};

let isPlayerInTile = (player: player): bool =>
  player.coords.offsetX === 0 && player.coords.offsetY === 0;

let isCollisionTile = (board: board, player: player): bool => {
  List.length(getCollidedTiles(board, player)) > 0;
};

let isCollision = (board: board, player: player) =>
  isPlayerInTile(player) &&
  isCollisionTile(board)(player) &&
  isPlayerValueHighEnough(player);

let addIDsToPlayers = (players: list(player)): list(player) => {
  List.mapi((index: int, player: player) => {
    ...player,
    id: index
  }, players);
};

let checkPlayerBoardCollision = (board: board, player: player): option(list(player)) => {
  isCollision(board, player)
    ? splitPlayer(player)
    : None
};

let checkBoardCollisions = (
  board: board,
  players: list(player)
): list(player) => {
  addIDsToPlayers(
    List.fold_right((player: player, newPlayers: list(player)) => {
      let maybePlayers = checkPlayerBoardCollision(board, player);
      switch (maybePlayers) {
      | Some (checkedPlayers) => List.concat([newPlayers, checkedPlayers]);
      | None => List.concat([newPlayers, [player]])
      };      
    }, players, [])
  );
};

let checkAll = (gameState: gameState): gameState => {
  {
    ...gameState,
    players: checkBoardCollisions(
      gameState.board,
      gameState.players
    )
  };
}