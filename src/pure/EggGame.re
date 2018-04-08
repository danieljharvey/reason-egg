open EggTypes;






  /*
let checkNearlyFinished = (
  gameState: gameState
): list(player) => {
  if (Utils.checkLevelIsCompleted(gameState)) {
    return gameState.players.map(player => {
      if (player.value > 0) {
        const maybeNewPlayer = Utils.getPlayerType("rainbow-egg");
        return maybeNewPlayer.map(newPlayer => {
          return player.modify({
            ...newPlayer
          });
        }).valueOr(player)
      }
      return player;
    });
  }
  return gameState.players;
};

*/

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
  
  /*
  let colouredPlayers = sortedPlayers; /*checkNearlyFinished(
    {
      ...newerGameState,
      players: splitPlayers
    }
  );*/

  {
    ...newerGameState,
    players: colouredPlayers
  }*/
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