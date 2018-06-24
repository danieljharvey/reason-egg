open EggTypes;

let offsetDivide: int = 64;

let playerHasMoved = (
  oldPlayer: player,
  newPlayer: player
): bool => {
  (
    oldPlayer.coords.x !== newPlayer.coords.x ||
    oldPlayer.coords.y !== newPlayer.coords.y ||
    oldPlayer.coords.offsetX !== newPlayer.coords.offsetX ||
    oldPlayer.coords.offsetY !== newPlayer.coords.offsetY
  )
};

/* work out whether player's location has moved since last go */
let markPlayerAsMoved = (oldPlayer: player, newPlayer: player): player => {
  {
    ...newPlayer,
    moved: playerHasMoved(oldPlayer, newPlayer)
  };
};

let playerJustTeleported = (player: player) : bool => (
  player.lastAction === "teleport"
);

/* find another teleport and go to it
// if no others, do nothing */
let teleport = (board: board, player: player): player => {
  if (!playerJustTeleported(player)) {
    let newTile = EggMap.findTile(board, player.coords, 14);
    switch (newTile) {
      | Some(tile) => {
        ...player,
        coords: {
          ...player.coords,
          x: tile.x,
          y: tile.y
        },
        lastAction: "teleport"
      }
      | _ => player
    };
  } else {
    player;
  }
};


let playerIsMidMove = (coords: coords) : bool => (
  coords.offsetX !== 0 || coords.offsetY !== 0
);

let doMovementTiles = (board: board, player: player): player => {
  let tile = Board.getTile(player.coords.x, player.coords.y, board);
  switch (tile.action) {
  | Teleport => teleport(board, player);
  | _ => player
  };
};

let checkForMovementTiles = (board: board, player: player): player => 
  (playerIsMidMove(player.coords)) ? player : doMovementTiles(board, player);

let overflowingRight = (coords: coords) : bool => (
  coords.offsetX >= offsetDivide
);

let overflowingLeft = (coords: coords) : bool => (
  coords.offsetX <= -1 * offsetDivide
);

let overflowingDown = (coords: coords) : bool => (
  coords.offsetY >= offsetDivide
);

let overflowingUp = (coords: coords) : bool => (
  coords.offsetY <= -1 * offsetDivide
);

let correctTileOverflow = (coords: coords): coords => {
  if (overflowingRight(coords)) {
    {
      ...coords,
      offsetX: 0,
      x: coords.x + 1
    };
  } else if (overflowingLeft(coords)) {
    {
      ...coords,
      offsetX: 0,
      x: coords.x - 1
    };
  } else if (overflowingDown(coords)) {  
    {
      ...coords,
      offsetY: 0,
      y: coords.y + 1
    };
  } else if (overflowingUp(coords)) {
    {
      ...coords,
      offsetY: 0,
      y: coords.y - 1
    };
  } else {
    coords;
  };
};

let correctPlayerOverflow = (board: board, player: player): player => {
  let newCoords = correctTileOverflow(player.coords);
  let loopedCoords = EggMap.correctForOverflow(board, newCoords);
  if (
    loopedCoords.x !== player.coords.x ||
    loopedCoords.y !== player.coords.y
  ) {
    {
      ...player,
      coords: loopedCoords,
      lastAction: ""
    };
  } else {
    {
      ...player,
      coords: loopedCoords
    };
  };

};

let playerTurningLeft = (player: player): bool => (
  player.direction.x < 0 ||
  player.oldDirection.x < 0 ||
  player.direction.y < 0 ||
  player.oldDirection.y < 0
);

let playerTurningRight = (player: player): bool => (
  player.direction.x > 0 ||
  player.oldDirection.x > 0 ||
  player.direction.y > 0 ||
  player.oldDirection.y > 0
);

let playerIsStill = (player: player): bool => (
  player.direction.x === 0 &&
  player.direction.y === 0 &&
  player.currentFrame === 0
);

let incrementPlayerFrame = (player: player): player => {
  
  /* if going left, reduce frame */
  let newFrame = if (playerTurningLeft(player)) {
    (player.currentFrame > 0) ? player.currentFrame - 1 : player.frames - 1;
  } else if (playerTurningRight(player)) {
    (player.currentFrame >= player.frames - 1) ? 0 : player.currentFrame + 1;
  } else {
    player.currentFrame;
  };

  if (playerIsStill(player)) {
    /* if we're still, and have returned to main frame, disregard old movement */
    {
      ...player,
      oldDirection: Player.defaultCoords
    };
  } else {
    {
      ...player,
      currentFrame: newFrame
    };
  };
};

let calcMoveAmount = (
  moveSpeed: int,
  deltaTime: float
): int => {
  let moveAmount: float = float_of_int(moveSpeed);
  let frameRateAdjusted: float = moveAmount *. deltaTime *. EggConstants.gameSpeed;
  (deltaTime === 0.) ? 0 : int_of_float(frameRateAdjusted);
};

let playerFalling = (deltaTime: float, player: player): player => {
  
  let fallAmount: int = calcMoveAmount(player.fallSpeed, deltaTime);
  
  let newCoords = {
    ...player.coords,
    offsetY: player.coords.offsetY + fallAmount
  };
  {
    ...player,
    coords: newCoords
  };
};

let playerRegularRolling = (deltaTime: float, player: player): player => {
  let moveAmount = calcMoveAmount(player.moveSpeed, deltaTime);

  let coords = player.coords;

  /* X axis movement */

  if (player.direction.x < 0) {
    /* move left */
    {
      ...player,
      coords: {
        ...coords,
        offsetX: coords.offsetX - moveAmount
      }
    };
  } else if (player.direction.x > 0) {
    /* move right */
    {
      ...player,
      coords: {
        ...coords,
        offsetX: coords.offsetX + moveAmount
      }
    };
  } else if (player.direction.y < 0) {
      /* move left */
      {
        ...player,
        coords: {
          ...coords,
          offsetY: coords.offsetY - moveAmount
        }
      };
    } else if (player.direction.y > 0) {
      /* move right */
      {
        ...player,
        coords: {
          ...coords,
          offsetY: coords.offsetY + moveAmount
        }
      };
  } else {
    player;
  };
};

let correctOffsetWhenStopped = (deltaTime: float, player: player): player => {
  /* if we've stopped and ended up not quite squared up, correct this */
  /*
  if (player.direction.x === 0) {
    if (coords.offsetX > 0) {
      // shuffle left
      const newOffsetX = coords.offsetX - moveAmount;

      return player.modify({
        coords: coords.modify({
          offsetX: newOffsetX
        })
      });
    } else if (coords.offsetX < 0) {
      // shuffle right
      const newOffsetX = coords.offsetX + moveAmount;

      return player.modify({
        coords: coords.modify({
          offsetX: newOffsetX
        })
      });
    }
  }

  // Y axis movement

  if (player.direction.y < 0) {
    // move up
    const newOffsetY = coords.offsetY - moveAmount;
    return player.modify({
      coords: coords.modify({
        offsetY: newOffsetY
      })
    });
  } else if (player.direction.y > 0) {
    // move down
    const newOffsetY = coords.offsetY + moveAmount;

    return player.modify({
      coords: coords.modify({
        offsetY: newOffsetY
      })
    });
  }

  // if we've stopped and ended up not quite squared up, correct this
  if (player.direction.y === 0) {
    if (coords.offsetY > 0) {
      // shuffle up
      const newOffsetY = coords.offsetY - moveAmount;

      return player.modify({
        coords: coords.modify({
          offsetY: newOffsetY
        })
      });
    } else if (coords.offsetY < 0) {
      // shuffle down
      const newOffsetY = coords.offsetY + moveAmount;

      return player.modify({
        coords: coords.modify({
          offsetY: newOffsetY
        })
      });
    }
  }
  */

  player;
};

/* this does the left/right moving, but does not care if walls are there as that is the responsibility of checkPlayerDirection */
let incrementPlayerDirection = (deltaTime: float, player: player): player => {
  if (player.falling) {
    playerFalling(deltaTime, player);
  } else if (player.moveSpeed === 0 || player.stop !== false) {
    correctOffsetWhenStopped(deltaTime, player);
  } else {
    playerRegularRolling(deltaTime, player);
  };
};

let playerIsTrapped = (board: board, player: player): bool => (
  player.direction.x !== 0 &&
  player.falling === false &&
  !EggMap.checkTileIsEmpty(player.coords.x - 1, player.coords.y, board) &&
  !EggMap.checkTileIsEmpty(player.coords.x + 1, player.coords.y, board)
);

let playerCanGoLeft = (board: board, player: player): bool => (
  player.direction.x < 0 &&
    player.falling === false && 
    !EggMap.checkTileIsEmpty(player.coords.x - 1, player.coords.y, board)
);

let playerCanGoRight = (board: board, player: player): bool => (
  player.direction.x > 0 && 
    player.falling === false && 
    !EggMap.checkTileIsEmpty(player.coords.x + 1, player.coords.y, board)
);

let checkStandardPlayerDirection = (board: board, player: player): player => {
  if (playerIsTrapped(board, player)) {
    {
      ...player,
      stop: true
    };
  } else if (playerCanGoLeft(board, player)) {
    {
      ...player,
      coords: {
        ...player.coords,
        offsetX: 0
      },
      direction: {
        ...player.direction,
        x: 1
      },
      stop: false
    };
  } else if (playerCanGoRight(board, player)) {
    {
      ...player,
      coords: {
        ...player.coords,
        offsetX: 0
      },
      direction: {
        ...player.direction,
        x: -1
      },
      stop: false
    };
  } else {
    {
      ...player,
      stop: false
    };
  };  
};


let checkFlyingPlayerDirection = (board: board, player: player): player => {
  let coords = player.coords;

  /*
  if (player.direction.y < 0) {
    if (!Map.checkTileIsEmpty(board, coords.x, coords.y - 1)) {
      // turn around
      return player.modify({
        coords: coords.modify({
          offsetY: 0
        }),
        direction: player.direction.modify({
          x: 1,
          y: 0
        }),
        stop: false
      });
    }
  }

  if (player.direction.y > 0) {
    if (!Map.checkTileIsEmpty(board, coords.x, coords.y + 1)) {
      // turn around
      return player.modify({
        coords: coords.modify({
          offsetY: 0
        }),
        direction: player.direction.modify({
          x: -1,
          y: 0
        }),
        stop: false
      });
    }
  }

  if (player.direction.x < 0) {
    if (!Map.checkTileIsEmpty(board, coords.x - 1, coords.y)) {
      // turn around
      return player.modify({
        coords: coords.modify({
          offsetX: 0
        }),
        direction: player.direction.modify({
          x: 0,
          y: -1
        }),
        stop: false
      });
    }
  }

  if (player.direction.x > 0) {
    if (!Map.checkTileIsEmpty(board, coords.x + 1, coords.y)) {
      // turn around
      return player.modify({
        coords: coords.modify({
          offsetX: 0
        }),
        direction: player.direction.modify({
          x: 0,
          y: 1
        }),
        stop: false
      });
    }
  } */

  {
    ...player,
    stop: false
  };
};

let checkPlayerDirection = (board: board, player: player): player => {
  player.flying === true
    ? checkFlyingPlayerDirection(board, player)
    : checkStandardPlayerDirection(board, player);
};

let checkFloorBelowPlayer = (board: board, player: player): player => {
  /*
  if (player.coords.offsetX !== 0) {
    return player;
  }

  if (player.flying === true) {
    return player.modify({
      falling: false
    });
  }
  */
  let coords = player.coords;

  let belowCoords = EggMap.correctForOverflow(
    board,
    { ...coords, y: coords.y + 1 }
  );

  let tile = Board.getTile(belowCoords.x, belowCoords.y, board);
  
  if (tile.background) {
    /* gap below, start falling down it */
    {
      ...player,
      falling: true
    };
  } else if (tile.breakable && player.falling) {
    player;
  } else {
    {
      ...player,
      falling: false
    };
  };
};

let getSeekEggMoves = (
  oldPlayer: player,
  board: board,
  deltaTime: float,
  players: list(player),
  player: player
) => {
  
  /*
  pathFinding(board, players)
  |> checkPlayerDirection(board) 
  |> incrementPlayerDirection(timePassed)
  */

  /* for now */
  oldPlayer;
};

let getEggMoves = (
  oldPlayer: player,
  board: board,
  deltaTime: float,
  player: player
) => {
  player
  |> checkFloorBelowPlayer(board)
  |> checkPlayerDirection(board) 
  |> incrementPlayerDirection(deltaTime)
};

let getPlayerSpecificMoves = (
  player: player,
  board: board,
  deltaTime: float,
  players: list(player)
) => {
  (player.movePattern === SeekEgg) ? getSeekEggMoves(player, board, deltaTime, players) : getEggMoves(player, board, deltaTime);
};

let doPlayerCalcs = (
  board: board,
  deltaTime: float,
  players: list(player),
  player: player
) => {
  
  let playerSpecific = getPlayerSpecificMoves(
    player,
    board,
    deltaTime,
    players
  );
  
  player
  |> incrementPlayerFrame
  |> playerSpecific
  |> correctPlayerOverflow(board)
  |> checkForMovementTiles(board)
  |> markPlayerAsMoved(player);
};

let doCalcs = (
  deltaTime: float,  
  gameState: gameState
): gameState => {
  {
    ...gameState,
    players: List.map(doPlayerCalcs(gameState.board, deltaTime, gameState.players), gameState.players)
  };
};
/*















// decide on next direction to follow based on closest egg to chase
export const pathFinding = (board: Board, players: Player[]) => (
  player: Player
) => {
  // only move when at actual place
  if (player.coords.offsetX !== 0 || player.coords.offsetY !== 0) {
    return player;
  }
  const pathMap = RenderMap.createPathFindingMapFromBoard(board);
  const maybe = PathFinder.findClosestPath(pathMap)(player.coords)(
    getAllCoords(players)
  );

  return maybe.map(PathFinder.findNextDirection).caseOf({
    just: val =>
      player.modify({
        direction: new Coords(val)
      }),
    nothing: () => player
  });
};

const getAllCoords = (players: Player[]): List<Coords> => {
  return fromJS(
    players
      .filter(player => {
        return player.value > 0;
      })
      .map(player => {
        return player.coords;
      })
  );
};



*/