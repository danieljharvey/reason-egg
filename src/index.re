open Reprocessing;

open Rationale;

type gameStuff = {
  egg: Tiles.imageAsset,
  tileImages: list(Tiles.imageAsset),
  left: int,
  top: int,
  frames: int,
  frame: int
};

let setup = env => {
  Env.size(~width=400, ~height=640, env);
  {
    egg: Tiles.loadImage(env, "sprites/egg-rainbow.png"),
    tileImages: Tiles.loadTileImages(env),
    left: 64,
    top: 64,
    frames: 18,
    frame: 1
  };
};

let tiles = Tiles.tiles;

let superBoard = Board.createBoardFromIDs(Board.idBoard);

let nextFrame = (frames, frame) => frame < frames ? frame + 1 : 1;

let drawBird = (gameStuff, env) => {
  let eggSize = 64;
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
  let tileSize = 64;
  Option.fmap(
    tileImage => {
      Js.log(tileImage);
      let (_, image) = tileImage;
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
};

let drawTiles = (gameStuff, env) => {
  List.map(drawTile(gameStuff, env), tiles);
  gameStuff;
};

let clearBackground = env => Draw.background(Constants.black, env);

let draw = (gameStuff, env) => {
  clearBackground(env);
  drawBird(gameStuff, env);
  /*drawTiles(gameStuff, env);*/
};

run(~setup, ~draw, ());
