open Reprocessing;
open EggTypes;

let screenSize = (640, 640);

let tileSize = 64;

let setup = env => {
  let (width, height) = screenSize;
  Env.size(~width, ~height, env);
  {
    players: Player.players,
    tileImages: Tiles.loadTileImages(env),
    playerImages: Player.loadPlayerImages(env),
    position: {x:1, y:1},
    frames: 18,
    frame: 1,
    boardAngle: 0.0,
    drawAngle: 0.0
  };
};

let tiles = Tiles.tiles;

let superBoard = Board.createBoardFromIDs(Board.idBoard);

let boardSize = List.length(superBoard);

let getScreenScale = (screenSize, boardSize) => {
  let (width, _) = screenSize;
  width / boardSize;
  1.0;
};

let nextFrame = (frames, frame) => frame < frames ? frame + 1 : 1;

let rotateTransform = (x, y, tileSize, angleDegrees, env) => {
  Draw.pushMatrix(env);
  
  let middleLeft = float_of_int((x * tileSize) + (tileSize / 2));
  let middleTop = float_of_int((y * tileSize) + (tileSize / 2));
  Draw.translate(middleLeft, middleTop, env);
  Draw.rotate(EggUtils.degreesToRadians(angleDegrees), env);
  env;
};

let drawPlayer = (env, coords, frame, image, drawAngle) => {
  let texPosX = frame * tileSize;
  
  rotateTransform(coords.x, coords.y, tileSize, -1.0 *. drawAngle, env);

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

let perhapsDrawTile = (gameStuff, env, optionTile) => {
  EggUtils.optionMap(tile => {
    switch (Tiles.getTileImageByID(gameStuff.tileImages, tile.filename)) {
    | Some(image) => drawTile(gameStuff, env, tile, image)
    | _ => ()
    };
  }, optionTile);
  ();
};

let drawTiles = (gameStuff, env) => {
  List.iter(List.iter(perhapsDrawTile(gameStuff, env)), superBoard);
  gameStuff;
};

let clearBackground = env => Draw.background(Constants.black, env);

let getScreenWidth = screenSize => {
  let (width, _) = screenSize;
  width;
};

let getCenter = screenSize : float =>
  float_of_int(getScreenWidth(screenSize)) /. 2.0;

let incrementAngle = gameStuff => {
  ...gameStuff,
  boardAngle: gameStuff.boardAngle +. 0.1
};

let doRotate = (gameStuff, env) =>
  gameStuff.boardAngle == 0.0 ?
    gameStuff :
    {
      let center = getCenter(screenSize);
      Draw.translate(center, center, env);
      Draw.rotate(EggUtils.degreesToRadians(gameStuff.boardAngle), env);
      Draw.translate((-1.0) *. center, (-1.0) *. center, env);
      gameStuff;
    };

let draw = (gameStuff, env) => {
  let scale = getScreenScale(screenSize, boardSize);
  Draw.scale(scale, scale, env);
  doRotate(gameStuff, env);
  clearBackground(env);
  drawTiles(gameStuff, env);
  /*let newGameStuff = drawBird(gameStuff, env) |> incrementAngle;*/
  incrementAngle(gameStuff);
};

run(~setup, ~draw, ());