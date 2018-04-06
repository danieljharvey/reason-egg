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
      Draw.translate(center, center , env);
      Draw.rotate(EggUtils.degreesToRadians(gameStuff.boardAngle), env);
      Draw.translate((-1.0) *. center, (-1.0) *. center, env);
      gameStuff;
    };

let rotateTransform = (coords: coords, tileSize, angleDegrees, env) => {
  let left = (coords.x * tileSize) + coords.offsetX;
  let top = (coords.y * tileSize) + coords.offsetY;
  let middleLeft = float_of_int(left + tileSize / 2);
  let middleTop = float_of_int(top + tileSize / 2);
  Draw.translate(middleLeft, middleTop, env);
  Draw.rotate(EggUtils.degreesToRadians(angleDegrees), env);
  env;
};

let drawPlayer =
    (
      env,
      coords: EggTypes.coords,
      frame: int,
      imageAsset: imageAsset,
      drawAngle: float
    ) => {
  let texPosX = frame * tileSize;
  Draw.pushMatrix(env);
  rotateTransform(coords, tileSize, (-1.0) *. drawAngle, env);
  let (_, image) = imageAsset;
  let offset = (-1) * tileSize / 2;
  Draw.subImage(
    image,
    ~pos=(offset + coords.offsetX, offset + coords.offsetY),
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
  switch (Tiles.getTileImageByID(gameStuff.tileImages, tile.filename)) {
  | Some(image) => drawTile(gameStuff, env, tile, image)
  | _ => ()
  };

let perhapsDrawPlayer = (gameStuff: gameStuff, env, player: player) => {
  switch (Tiles.getTileImageByID(gameStuff.playerImages, player.filename)) {
  | Some(image) =>
    drawPlayer(
      env,
      player.coords,
      player.currentFrame,
      image,
      gameStuff.drawAngle
    )
  | _ => ()
  };
  ();
};

let drawTiles = (gameStuff, env) => {
  List.iter(List.iter(perhapsDrawTile(gameStuff, env)), gameStuff.gameState.board);
  gameStuff;
};

let drawPlayers = (gameStuff, env) =>
  List.iter(perhapsDrawPlayer(gameStuff, env), gameStuff.gameState.players);

let clearBackground = env => Draw.background(Constants.white, env);