open EggTypes;





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

let checkNearlyFinished = (
  gameState: gameState
): gameState => {
  let newPlayers = if (Utils.checkLevelIsCompleted(gameState)) {
    List.map((player: player) => {
      (player.value > 0) ? makeRainbowEgg(player) : player;
    }, gameState.players);
  } else {
    gameState.players;
  };
  {
    ...gameState,
    players: newPlayers
  };
};


/* this rotates board and players it DOES NOT do animation - not our problem */
let doRotate = (gameState: gameState, clockwise: bool): gameState => {
  let rotations = gameState.rotations + 1;

  let boardSize = List.length(gameState.board);

  let newBoard = EggMap.rotateBoard(gameState.board, clockwise);

  let rotatedPlayers = List.map(player => {
    EggMap.rotatePlayer(boardSize, player, clockwise);
  }, gameState.players);

  let rotateAngle: float = EggMap.changeRenderAngle(
    gameState.rotateAngle,
    clockwise
  );

  {
    ...gameState,
    board: newBoard,
    players: rotatedPlayers,
    rotateAngle,
    rotations
  };
};

let resetOutcome = (gameState: gameState) : gameState => {
  ...gameState,
    outcome: ""
};

let doGameMove = (gameState: gameState, timePassed: int): gameState => {
  resetOutcome(gameState)
  |> EggMovement.doCalcs(timePassed)
  |> EggAction.checkAllPlayerTileActions
  |> EggCollisions.checkAll
  |> BoardCollisions.checkAll
  |> checkNearlyFinished
};

let doAction = (
  gameState: gameState,
  action: string,
  timePassed: int
): gameState => {
  if (action === "rotateLeft") {
    doRotate(gameState, false);
  } else if (action === "rotateRight") {
    doRotate(gameState, true);
  } else if (action === "") {
    doGameMove(gameState, timePassed);
  } else {
    gameState;
  };
};