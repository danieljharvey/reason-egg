open EggTypes;

let playerIsValid = (player: player): bool => player.value > 0;

let countPlayers = (players: list(player)): int => {
  List.length(List.filter(playerIsValid, players));
};

/* get total outstanding points left to grab on board */
let countCollectable = (board: board): int => {
  List.fold_right((tile: tile, score: int) => {
    switch (tile.action) {
    | Collectable(x) => score + x
    | _ => score
    };
  }, Board.getBoardTiles(board), 0);
};

/* check leftovers on board and whether player is over finish tile */
let checkLevelIsCompleted = (gameState: gameState): bool => {
  let collectable = countCollectable(gameState.board);
  let playerCount: int = countPlayers(gameState.players);
  (collectable < 1 && playerCount < 2);
};

let makeRainbowEgg = (player: player) : player => {
  let maybeNewPlayer = Player.getPlayerByType(RainbowEgg);
  switch (maybeNewPlayer) {
    | Some(rainbowEgg) => {
      {
        ...player,
        frames: rainbowEgg.frames,
        filename: rainbowEgg.filename,
        multiplier: rainbowEgg.multiplier,
        playerType: rainbowEgg.playerType,
        value: rainbowEgg.value
      };
    }
    | _ => player
  };
};

let makeRainbowEggs = (players: list(player)): list(player) => 
    List.map((player: player) => {
        (player.value > 0) ? makeRainbowEgg(player) : player;
      }, players);


let openDoor = (board: board) : board => {
    let doors = List.filter((tile: tile) => tile.action == ClosedDoor, Board.getBoardTiles(board));
    List.fold_right((tile: tile, board: board) => {
        Board.changeTileByID(board, tile.x, tile.y, 26);
    }, doors, board);
};

let levelIsCompletedMode = (gameState: gameState) : gameState => {
    {
        ...gameState,
        players: makeRainbowEggs(gameState.players),
        board: openDoor(gameState.board),
        visualMode: MegaVibes
    };
};

let check = (
  gameState: gameState
): gameState => {
    (checkLevelIsCompleted(gameState)) ? levelIsCompletedMode(gameState) : gameState;
};
  