open Reprocessing;

open EggTypes;

open EggConstants;

let setup = (env) => {
  let (width, height) = screenSize;
  Env.size(~width, ~height, env);
  let gameState = Setup.defaultGameState(Board.board);
  Setup.setupEnvironment(gameState, env);
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
  gameState: EggGame.doAction(gameStuff.gameState, "", 10),
  boardAngle: gameStuff.boardAngle +. 0.01,
  drawAngle: calcDrawAngle(gameStuff.boardAngle)
};

let drawGame = (env, gameStuff: gameStuff) => {
  Render.render(env, gameStuff);
  updateGameStuff(gameStuff);
};

let drawNothing = (env, gameStuff: gameStuff) => {
  Draw.background(Constants.white, env);
  gameStuff;
};

let draw = (gameStuff: gameStuff, env) => {
  switch gameStuff.programState {
  | Playing => drawGame(env, gameStuff)
  | Loading => drawNothing(env, gameStuff)
  };
};

run(~setup, ~draw, ());
