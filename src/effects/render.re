open Reprocessing;

open EggTypes;

open EggConstants;

let getScreenScale = (screenSize, boardSize) => {
  let (width, _) = screenSize;
  float_of_int(width) /. float_of_int(boardSize * EggConstants.tileSize);
};

let getScreenWidth = screenSize => {
  let (width, _) = screenSize;
  width;
};

let getCenter = screenSize : float =>
  float_of_int(getScreenWidth(screenSize)) /. 2.0;

let doRotate = (gameStuff, env) =>
  gameStuff.boardAngle == 0.0 ?
    gameStuff :
    {
      let center = getCenter(screenSize);
      Draw.translate(
        ~x=center,
        ~y=center,
        env
      );
      Draw.rotate(EggUtils.degreesToRadians(gameStuff.boardAngle), env);
      Draw.translate(
        ~x=(-1.0) *. center,
        ~y=(-1.0) *. center,
        env
      );
      gameStuff;
    };

let rotateTransform = (coords: coords, tileSize, angleDegrees, env) => {
  let left = (coords.x * tileSize) + coords.offsetX;
  let top = (coords.y * tileSize) + coords.offsetY;
  let middleLeft = float_of_int(left + tileSize / 2);
  let middleTop = float_of_int(top + tileSize / 2);
  Draw.translate(
    ~x=middleLeft,
    ~y=middleTop,env
  );
  Draw.rotate(EggUtils.degreesToRadians(angleDegrees), env);
  env;
};

let drawPlayer =
    (
      env,
      player: player,
      imageAsset: imageAsset,
      drawAngle: float
    ) => {
  let texPosX = player.currentFrame * tileSize;
  Draw.pushMatrix(env);
  rotateTransform(player.coords, tileSize, (-1.0) *. drawAngle, env);
  let (_, image) = imageAsset;
  let offset = (-1) * tileSize / 2;
  Draw.subImage(
    image,
    ~pos=(offset, offset),
    ~width=tileSize,
    ~height=tileSize,
    ~texPos=(texPosX, 0),
    ~texWidth=tileSize,
    ~texHeight=tileSize,
    env
  );
  Draw.popMatrix(env);
  ();
};

let drawTile = (gameStuff, env, tile: tile, imageAsset: imageAsset) => {
  Draw.pushMatrix(env);
  let tileCoords = {
    ...Player.defaultCoords,
    x: tile.x, 
    y: tile.y
  };
  rotateTransform(
    tileCoords,
    tileSize,
    (-1.0) *. gameStuff.drawAngle,
    env
  );
  let (_, image) = imageAsset;
  let offset = (-1) * tileSize / 2;
  Draw.subImage(
    image,
    ~pos=(offset, offset),
    ~width=tileSize,
    ~height=tileSize,
    ~texPos=(0, 0),
    ~texWidth=tileSize,
    ~texHeight=tileSize,
    env
  );
  Draw.popMatrix(env);
  ();
};

let perhapsDrawTile = (gameStuff: gameStuff, env, tile: tile) => 
  EggUtils.optionMap(
    image => drawTile(gameStuff, env, tile, image),
    Tiles.getTileImageByID(gameStuff.tileImages, tile.filename));

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

let drawShadowPlayer = 
(
  env,
  player: player,
  imageAsset: imageAsset,
  drawAngle: float,
  boardSize: int
) => {
  if (fallingOffLeft(player.coords)) {
    let shadowPlayer = {
      ...player,
      coords: {
        ...player.coords,
        x: player.coords.x + boardSize
      }
    };
    drawPlayer(env, shadowPlayer, imageAsset, drawAngle)
  } else if (fallingOffRight(boardSize, player.coords)) {
    let shadowPlayer = {
      ...player,
      coords: {
        ...player.coords,
        x: -1
      }
    };
    drawPlayer(env, shadowPlayer, imageAsset, drawAngle);
  } else if (fallingOffTop(player.coords)) {
    let shadowPlayer = {
      ...player,
      coords: {
        ...player.coords,
        y: player.coords.y + boardSize
      }
    };
    drawPlayer(env, shadowPlayer, imageAsset, drawAngle);
  } else if (fallingOffBottom(boardSize, player.coords)) {
    let shadowPlayer = {
      ...player,
      coords: {
        ...player.coords,
        y: -1
      }
    };
    drawPlayer(env, shadowPlayer, imageAsset, drawAngle);
  };
  ();
};


let perhapsDrawPlayer = (gameStuff: gameStuff, env, player: player) => {
  EggUtils.optionMap(image =>
    {
      drawPlayer(
        env,
        player,
        image,
        gameStuff.drawAngle
      );
      drawShadowPlayer(
        env,
        player,
        image,
        gameStuff.drawAngle,
        List.length(gameStuff.gameState.board)
      );
    },
    Tiles.getTileImageByID(gameStuff.playerImages, player.filename)
  );
};

let drawTiles = (gameStuff, env) => {
  List.map(perhapsDrawTile(gameStuff, env), Board.getBoardTiles(gameStuff.gameState.board));
  gameStuff;
};

let drawPlayers = (gameStuff, env) =>
  List.map(perhapsDrawPlayer(gameStuff, env), gameStuff.gameState.players);

let clearBackground = env => Draw.background(Constants.black, env);

let render = (env, gameStuff: gameStuff) => {
  let boardSize = List.length(gameStuff.gameState.board);
  let scale = getScreenScale(screenSize, boardSize);

  Draw.pushMatrix(env);
  doRotate(gameStuff, env) |> ignore;
  Draw.scale(~x=scale, ~y=scale, env);
  clearBackground(env);

  drawTiles(gameStuff, env) |> ignore;
  drawPlayers(gameStuff, env) |> ignore;
  
  Draw.popMatrix(env);
};