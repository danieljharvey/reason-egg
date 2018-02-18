open Reprocessing;

type gameStuff = {
  egg: Reprocessing_Types.Types.imageT,
  left: int,
  top: int,
  frames: int,
  frame: int
};

let loadRainbowEgg = env =>
  Draw.loadImage(~filename="assets/egg-rainbow.png", ~isPixel=true, env);

let setup = env => {
  Env.size(~width=400, ~height=640, env);
  {egg: loadRainbowEgg(env), left: 20, top: 20, frames: 18, frame: 1};
};

let tiles = Tiles.tiles;

let superBoard = Board.createBoardFromIDs(Board.idBoard);

Js.log(superBoard);

let nextFrame = (frames, frame) => frame < frames ? frame + 1 : 1;

let drawBird = (gameStuff, env) => {
  let eggSize = 64;
  let texPosX = gameStuff.frame * eggSize;
  Draw.subImage(
    gameStuff.egg,
    ~pos=(gameStuff.left, gameStuff.top),
    ~width=eggSize,
    ~height=eggSize,
    ~texPos=(texPosX, 0),
    ~texWidth=64,
    ~texHeight=64,
    env
  );
  {
    ...gameStuff,
    left: gameStuff.left + 1,
    top: gameStuff.top + 1,
    frame: nextFrame(gameStuff.frames, gameStuff.frame)
  };
};

let draw = (gameStuff, env) => drawBird(gameStuff, env);

run(~setup, ~draw, ());