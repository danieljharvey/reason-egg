open Reprocessing;

open EggTypes;
open JsTypes;

open EggConstants;

let pi = 3.14159265358979323846;

let degreesToRadians = (degrees: float) : float =>
  degrees /. 360.0 *. (pi *. 2.0);

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
      Draw.rotate(degreesToRadians(boardAngle), env);
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
  Draw.rotate(degreesToRadians(angleDegrees), env);
  env;
};

let texPosX = (frame: int) => frame * tileSize;

let offset = (-1) * tileSize / 2;

let renderGeneric =
    (
      imageAsset: imageAsset,
      coords: coords,
      size: float,
      drawAngle: float,
      frame: int,
      env
    ) => {

  Draw.pushMatrix(env);
  rotateTransform(coords, tileSize, (-1.0) *. drawAngle, env);
  Draw.scale(~x=size, ~y=size, env);
  
  let (_, image) = imageAsset;

  Draw.subImage(
    image,
    ~pos=(offset, offset),
    ~width=tileSize,
    ~height=tileSize,
    ~texPos=(texPosX(frame), 0),
    ~texWidth=tileSize,
    ~texHeight=tileSize,
    env
  );
  Draw.popMatrix(env);
  ();
};


let renderPlayer = (drawAngle: float, gameStuff: gameStuff, env, player: player) => 
  switch (DrawTile.getTileImageByID(gameStuff.playerImages, player.filename)) {
  | Some(imageAsset) => {
    List.iter(drawPlayer => {
      renderGeneric(imageAsset, drawPlayer.coords, drawPlayer.size, drawAngle, drawPlayer.currentFrame, env);
    }, DrawPlayer.getDrawPlayers(
      Board.getBoardSize(gameStuff.gameState.board),
      player
    ));
  }
  | _ => ()
  };

let drawPlayers = (drawAngle: float, gameStuff, env) =>
  List.map(renderPlayer(drawAngle, gameStuff, env), gameStuff.gameState.players);


let renderTile = (drawAngle: float, gameStuff, env, tile: tile) => {
  switch (DrawTile.getTileImageByID(gameStuff.tileImages, tile.filename)) {
  | Some(imageAsset) => {
    let tileCoords = {
      ...Player.defaultCoords,
      x: tile.x, 
      y: tile.y
    };
    renderGeneric(imageAsset, tileCoords, 1.0, drawAngle, tile.currentFrame, env);
  }
  | _ => ()
  };
};

let drawTiles = (drawAngle: float, gameStuff, env) => {
  List.map(renderTile(drawAngle, gameStuff, env), Board.getDrawTiles(gameStuff.gameState.board));
  gameStuff;
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