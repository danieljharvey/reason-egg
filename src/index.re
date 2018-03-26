open Reprocessing;
open EggTypes;
open EggConstants;

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

let boardSize = List.length(Board.superBoard);

let getScreenScale = (screenSize, boardSize) => {
  let (width, _) = screenSize;
  width / boardSize;
  1.0;
};

let nextFrame = (frames, frame) => frame < frames ? frame + 1 : 1;

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
      Draw.translate(center, center, env);
      Draw.rotate(EggUtils.degreesToRadians(gameStuff.boardAngle), env);
      Draw.translate((-1.0) *. center, (-1.0) *. center, env);
      gameStuff;
    };


let incrementPlayerFrame = (player: player): player => 
  {
    ...player,
    currentFrame: nextFrame(player.frames, player.currentFrame)
  };

let updateGameStuff = (gameStuff: gameStuff) => {
  {
    ...gameStuff,
    boardAngle: gameStuff.boardAngle +. 0.1,
    players: List.map(incrementPlayerFrame, gameStuff.players)
  };
};

let draw = (gameStuff, env) => {
  let scale = getScreenScale(screenSize, boardSize);
  Draw.scale(scale, scale, env);
  doRotate(gameStuff, env);
  Render.clearBackground(env);
  Render.drawTiles(gameStuff, env);
  Render.drawPlayers(gameStuff, env);

  /*let newGameStuff = drawBird(gameStuff, env) |> incrementAngle;*/
  updateGameStuff(gameStuff);
};

run(~setup, ~draw, ());