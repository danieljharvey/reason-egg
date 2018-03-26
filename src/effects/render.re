open Reprocessing;
open EggTypes;
open EggConstants;

let rotateTransform = (x, y, tileSize, angleDegrees, env) => {
    Draw.pushMatrix(env);
    
    let middleLeft = float_of_int((x * tileSize) + (tileSize / 2));
    let middleTop = float_of_int((y * tileSize) + (tileSize / 2));
    Draw.translate(middleLeft, middleTop, env);
    Draw.rotate(EggUtils.degreesToRadians(angleDegrees), env);
    env;
  };
  
  let drawPlayer = (env, coords: EggTypes.coords, frame: int, imageAsset: imageAsset, drawAngle: float) => {
    let texPosX = frame * tileSize;
    
    rotateTransform(coords.x, coords.y, tileSize, -1.0 *. drawAngle, env);
  
    let (_,image) = imageAsset;
  
    Draw.subImage(
      image,
      ~pos=(-1 * tileSize, -1 * tileSize),
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
      
    rotateTransform(tile.x, tile.y, tileSize, -1.0 *. gameStuff.drawAngle, env);
    
    let (_,image) = imageAsset;
  
    Draw.subImage(
      image,
      ~pos=(-1 * tileSize, -1 * tileSize),
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
  
  let perhapsDrawTile = (gameStuff: gameStuff, env, optionTile) => {
    EggUtils.optionMap(tile => {
      switch (Tiles.getTileImageByID(gameStuff.tileImages, tile.filename)) {
      | Some(image) => drawTile(gameStuff, env, tile, image)
      | _ => ()
      };
    }, optionTile);
    ();
  };
  
  let perhapsDrawPlayer = (gameStuff: gameStuff, env, player: player) => {
    switch (Tiles.getTileImageByID(gameStuff.playerImages, player.filename)) {
      | Some(image) => drawPlayer(env, player.coords, player.currentFrame, image, gameStuff.drawAngle)
      | _ => ()
      };
    ();
  };
  
  let drawTiles = (gameStuff, env) => {
    List.iter(List.iter(perhapsDrawTile(gameStuff, env)), Board.superBoard);
    gameStuff;
  };
  
  let drawPlayers = (gameStuff, env) => {
    List.iter(perhapsDrawPlayer(gameStuff, env), gameStuff.players);
  };
  
  let clearBackground = env => Draw.background(Constants.black, env);
  