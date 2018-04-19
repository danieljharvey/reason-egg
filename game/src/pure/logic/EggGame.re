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


let incrementRotations = (clockwise: bool, rotations: (int, int)): (int, int) => 
  (clockwise) ? (fst(rotations), snd(rotations) + 1) : (fst(rotations) + 1, snd(rotations));

/* this rotates board and players it DOES NOT do animation - not our problem */
let doRotate = (gameState: gameState, clockwise: bool): gameState => {
  let rotations = incrementRotations(clockwise, gameState.rotations);

  let boardSize = List.length(gameState.board);

  let newBoard = EggMap.rotateBoard(gameState.board, clockwise);

  let rotatedPlayers = List.map(player => {
    EggMap.rotatePlayer(boardSize, player, clockwise);
  }, gameState.players);

  let drawAngle: float = EggMap.changeRenderAngle(
    gameState.drawAngle,
    clockwise
  );

  {
    ...gameState,
    board: newBoard,
    players: rotatedPlayers,
    drawAngle,
    rotations,
    boardAngle: 0.0,
    gameAction: Playing
  };
};

let resetOutcome = (gameState: gameState) : gameState => {
  ...gameState,
    outcome: ""
};

let doGameMove = (gameState: gameState, deltaTime: float): gameState => {
  resetOutcome(gameState)
  |> EggMovement.doCalcs(deltaTime)
  |> EggAction.checkAllPlayerTileActions
  |> EggCollisions.checkAll
  |> BoardCollisions.checkAll
  |> EggFrames.cycleAll
  |> CompleteLevel.check
};

let doAction = (
  gameState: gameState,
  deltaTime: float
): gameState => {
  switch (gameState.gameAction) {
  | TurnLeft => doRotate(gameState,false)
  | TurnRight => doRotate(gameState, true)
  | Playing => doGameMove(gameState, deltaTime)
  | _ => gameState
  };
};

let processRotate = (gameState: gameState, keyCode: eggKeycode): gameState => {
  (gameState.gameAction === Playing) ? 
    {
      ...gameState,
      gameAction: switch (keyCode) {
        | KeyLeft => RotatingLeft(0.0)
        | KeyRight => RotatingRight(0.0)
        | _ => gameState.gameAction
        }
    } : gameState;
};


let createPlayer = (x: int, y: int, playerType: playerType, id: int) : option(player) => {
  let coords = { ...Player.defaultCoords, x, y };
  let direction = {
      ...Player.defaultCoords,
      x: 1
  };
  Utils.optionMap(player => {
      {
          ...player, 
          coords,  
          direction,
          id   
      }
  }, Player.getPlayerByType(playerType));
};

let createPlayers = (board: board): list(player) => {
  List.fold_right((tile: tile, players: list(player)) => {
      let id = List.length(players) + 1;
      let optPlayer = createPlayer(tile.x, tile.y, tile.createPlayer, id);
      switch (optPlayer) {
      | Some(player) => List.append(players, [player])
      | _ => players
      }
  }, Board.getBoardTiles(board), []);
};

let loadGameState = (levelID: int): gameState => {
  let board = Board.getLevel(levelID);
  {
      players: createPlayers(board),
      board,
      score: 0,
      rotations: (0,0),
      drawAngle: 0.0,
      outcome: "",
      gameAction: Playing,
      boardAngle: 0.0,
      currentFrame: 0,
      visualMode: Tint.getTintForLevelID(levelID),
      levelID
  };
};