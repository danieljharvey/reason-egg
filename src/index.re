open Reprocessing;

open Rationale;

let screenSize = (640, 640);



type gameStuff = {
  egg: Tiles.imageAsset,
  tileImages: list(Tiles.imageAsset),
  left: int,
  top: int,
  frames: int,
  frame: int,
  drawAngle: float
};

let setup = env => {
  let (width, height) = screenSize;
  Env.size(~width=width, ~height=height, env);
  Js.log(Tiles.loadTileImages(env));
  {
    egg: Tiles.loadImage(env, "sprites/egg-rainbow.png"),
    tileImages: Tiles.loadTileImages(env),
    left: 64,
    top: 64,
    frames: 18,
    frame: 1,
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

let drawBird = (gameStuff, env): gameStuff => {
  let eggSize = 64; /*getSpriteSize(screenSize, boardSize);*/
  let texPosX = gameStuff.frame * eggSize;
  let (_, eggImage) = gameStuff.egg;
  Draw.subImage(
    eggImage,
    ~pos=(gameStuff.left, gameStuff.top),
    ~width=eggSize,
    ~height=eggSize,
    ~texPos=(texPosX, 0),
    ~texWidth=64,
    ~texHeight=64,
    env
  );
  {...gameStuff, frame: nextFrame(gameStuff.frames, gameStuff.frame)};
};

let drawTile = (gameStuff, env, tile: Tiles.tile) => {
  let tileSize = 64; /*getSpriteSize(screenSize, boardSize);*/
    Option.fmap(tileImage => {
      let (imageTitle, image) = tileImage;
      Draw.subImage(
        image,
        ~pos=(tile.x * tileSize, tile.y * tileSize),
        ~width=tileSize,
        ~height=tileSize,
        ~texPos=(0, 0),
        ~texWidth=tileSize,
        ~texHeight=tileSize,
        env
      );
    },
    Tiles.getTileImageByID(gameStuff.tileImages, tile.filename)
  );
();
};


let perhapsDrawTile = (gameStuff, env, optionTile) => {
  switch (optionTile) {
  | Some(tile) => drawTile(gameStuff, env, tile)
  | _ => ()
  };
};


let drawTiles = (gameStuff, env) => {
  List.iter(
    List.iter(
      perhapsDrawTile(gameStuff, env)
    ), superBoard);
  gameStuff;
};

let clearBackground = env => Draw.background(Constants.black, env);

let getScreenWidth = (screenSize) => {
  let (width, _) = screenSize;
  width;
};

let getCenter = (screenSize): float => {
  float_of_int(getScreenWidth(screenSize)) /. 2.0;
};

let incrementAngle = (gameStuff) => {
  {...gameStuff, drawAngle: gameStuff.drawAngle +. 0.01};
};

let doRotate = (gameStuff, env) => {
 (gameStuff.drawAngle == 0.0) ? gameStuff : {
   let center = getCenter(screenSize);
   Draw.translate(center, center, env);
   Draw.rotate(gameStuff.drawAngle, env);
   Draw.translate(-1.0 *. center, -1.0 *. center, env);
   gameStuff;
 }
};

let draw = (gameStuff, env) => {
  

  let scale = getScreenScale(screenSize, boardSize);
  
  Draw.scale(scale, scale, env);
  
  doRotate(gameStuff, env);
  
  clearBackground(env);
  drawTiles(gameStuff, env);
  let newGameStuff = drawBird(gameStuff, env) |> incrementAngle;
  
  
  
  
  newGameStuff;
};

run(~setup, ~draw, ());
