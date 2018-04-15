open EggTypes;

open EggConstants;

let fallingOffLeft = (coords: coords): bool => (
  coords.x === 0 && coords.offsetX < 0
);

let fallingOffRight= (boardSize: int, coords: coords): bool => (
  coords.x >= (boardSize -1) && coords.offsetX > 0
);

let fallingOffTop = (coords: coords): bool => (
  coords.y === 0 && coords.offsetY < 0
);

let fallingOffBottom= (boardSize: int, coords: coords): bool => (
  coords.y >= (boardSize -1) && coords.offsetY > 0
);

let getShadowPlayer = 
(
  boardSize: int,  
  player: player
): option(player) => {
  if (fallingOffLeft(player.coords)) {
    Some({
      ...player,
      coords: {
        ...player.coords,
        x: player.coords.x + boardSize
      }
    });
  } else if (fallingOffRight(boardSize, player.coords)) {
    Some({
      ...player,
      coords: {
        ...player.coords,
        x: -1
      }
    });
  } else if (fallingOffTop(player.coords)) {
    Some({
      ...player,
      coords: {
        ...player.coords,
        y: player.coords.y + boardSize
      }
    });
  } else if (fallingOffBottom(boardSize, player.coords)) {
    Some({
      ...player,
      coords: {
        ...player.coords,
        y: -1
      }
    });
  } else {
    None;
  }
};

let getDrawPlayers = (boardSize: int, player: player): list(player) => {
  switch (getShadowPlayer(boardSize, player)) {
  | Some(shadowPlayer) => [player, shadowPlayer]
  | _ => [player]
  }
};

let loadPlayerImages = (players: list(player), env) =>
  List.map(
    (player: player) => RenderUtils.loadImage(env, player.filename),
    players
  );