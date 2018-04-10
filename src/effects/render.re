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

let doRotate = (boardAngle: float, env) =>
  boardAngle == 0.0 ?
    () :
    {
      let center = getCenter(screenSize);
      Draw.translate(
        ~x=center,
        ~y=center,
        env
      );
      Draw.rotate(EggUtils.degreesToRadians(boardAngle), env);
      Draw.translate(
        ~x=(-1.0) *. center,
        ~y=(-1.0) *. center,
        env
      );
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

let drawTile = (drawAngle: float, gameStuff, env, tile: tile, imageAsset: imageAsset) => {
  Draw.pushMatrix(env);
  let tileCoords = {
    ...Player.defaultCoords,
    x: tile.x, 
    y: tile.y
  };
  rotateTransform(
    tileCoords,
    tileSize,
    (-1.0) *. drawAngle,
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

let perhapsDrawTile = (drawAngle: float, gameStuff: gameStuff, env, tile: tile) => 
  EggUtils.optionMap(
    image => drawTile(drawAngle, gameStuff, env, tile, image),
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


let perhapsDrawPlayer = (drawAngle: float, gameStuff: gameStuff, env, player: player) => {
  EggUtils.optionMap(image =>
    {
      drawPlayer(
        env,
        player,
        image,
        drawAngle
      );
      drawShadowPlayer(
        env,
        player,
        image,
        drawAngle,
        List.length(gameStuff.gameState.board)
      );
    },
    Tiles.getTileImageByID(gameStuff.playerImages, player.filename)
  );
};

let drawTiles = (drawAngle: float, gameStuff, env) => {
  List.map(perhapsDrawTile(drawAngle, gameStuff, env), Board.getDrawTiles(gameStuff.gameState.board));
  gameStuff;
};

let drawPlayers = (drawAngle: float, gameStuff, env) =>
  List.map(perhapsDrawPlayer(drawAngle, gameStuff, env), gameStuff.gameState.players);

let clearBackground = (gameStuff: gameStuff, env) => {
  Draw.fill({
    r: 0.0,
    g: 0.0,
    b: 0.0,
    a: 0.3
  }, env);
  let (width, height) = EggConstants.screenSize;
  Draw.rect(~pos=(0,0), ~width=width, ~height=height, env);
};

let render = (env, gameStuff: gameStuff) => {
  let boardSize = List.length(gameStuff.gameState.board);
  let scale = getScreenScale(screenSize, boardSize);
  let boardAngle = gameStuff.boardAngle +. gameStuff.gameState.boardAngle;
  let drawAngle = -1.0 *. gameStuff.gameState.drawAngle;

  Draw.pushMatrix(env);
  Background.clearBackground(gameStuff, env);

  doRotate(boardAngle, env);
  Draw.scale(~x=scale, ~y=scale, env);
  
  drawTiles(drawAngle, gameStuff, env) |> ignore;
  drawPlayers(0.0, gameStuff, env) |> ignore;
  
  Draw.popMatrix(env);
};