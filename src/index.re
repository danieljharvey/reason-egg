open Reprocessing;

open EggTypes;

open EggConstants;

let setup = (env) => {
  let (width, height) = screenSize;
  Env.size(~width, ~height, env);
  Setup.setupEnvironment(Board.board, env);
};

let nextFrame = (frames, frame) => frame < frames ? frame + 1 : 1;

let incrementPlayerFrame = (player: player) : player => {
  ...player,
  currentFrame: nextFrame(player.frames, player.currentFrame)
};

let calcDrawAngle = (boardAngle: float) : float =>
  if (boardAngle > 270.0) {
    270.0;
  } else if (boardAngle > 180.0) {
    180.0;
  } else if (boardAngle > 90.0) {
    90.0;
  } else {
    0.0;
  };

let changeAngle = (newAngle: float) : float =>
  if (newAngle > 360.0) {
    newAngle -. 360.0;
  } else if (newAngle < 0.0) {
    newAngle +. 360.0;
  } else {
    newAngle;
  };

let updateGameStuff = (gameStuff: gameStuff) => {
  ...gameStuff,
  /*boardAngle: changeAngle(gameStuff.boardAngle -. 1.1),*/
  players: List.map(incrementPlayerFrame, gameStuff.players),
  drawAngle: calcDrawAngle(gameStuff.boardAngle)
};

let drawGame = (gameStuff: gameStuff, env) => {
  let scale = Render.getScreenScale(screenSize, gameStuff.boardSize);
  Draw.pushMatrix(env);
  Render.doRotate(gameStuff, env);
  Draw.scale(scale, scale, env);
  /*Render.clearBackground(env);*/
  /*let offset = -1.0 *. (float_of_int(tileSize) /. 2.0);
    Draw.translate(offset,offset, env);*/
  Render.drawTiles(gameStuff, env);
  Render.drawPlayers(gameStuff, env);
  Draw.popMatrix(env);
  /*let newGameStuff = drawBird(gameStuff, env) |> incrementAngle;*/
  updateGameStuff(gameStuff);
};

let drawNothing = (gameStuff: gameStuff, env) => {
  let clearBackground = env => Draw.background(Constants.white, env);
  gameStuff;
};

let draw = (gameStuff: gameStuff, env) => {
  switch gameStuff.gameState {
  | Playing => drawGame(gameStuff, env)
  | Loading => drawNothing(gameStuff, env)
  };
};

run(~setup, ~draw, ());
