open Reprocessing;

open EggTypes;

open EggConstants;

let setup = (env) => {
  let (width, height) = screenSize;
  Env.size(~width, ~height, env);
  let gameState = Setup.defaultGameState(Board.board);
  Setup.setupEnvironment(gameState, env);
};

let nextFrame = (frames, frame): int => frame < frames ? frame + 1 : 1;

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

let updateGameStuff = (gameStuff: gameStuff): gameStuff => {
  ...gameStuff,
  gameState: EggGame.doAction(gameStuff.gameState, 10),
  /* boardAngle: gameStuff.boardAngle +. 0.01, */
  drawAngle: calcDrawAngle(gameStuff.boardAngle)
};

let drawGame = (env, gameStuff: gameStuff) => {
  Render.render(env, gameStuff);
};

let drawNothing = (env, gameStuff: gameStuff): gameStuff => {
  Draw.background(Constants.white, env);
  gameStuff;
};

let rotateBoard = (clockwise: bool, angle: int, env, gameStuff): gameStuff => {
  let boardAngle = (clockwise) ? float_of_int(angle) : float_of_int(-1 * angle);
  let newAngle = angle + 1;
  let newGameAction = clockwise ? RotatingRight(newAngle) : RotatingLeft(newAngle);
  {
    ...gameStuff,
    boardAngle,
    gameState: {
      ...gameStuff.gameState,
      gameAction: newGameAction
    }
  };
};

let draw = (gameStuff: gameStuff, env): gameStuff => {
  let newGameStuff = switch gameStuff.gameState.gameAction {
  | Playing => updateGameStuff(gameStuff)
  | RotatingLeft(angle) => rotateBoard(false, angle, env, gameStuff)
  | RotatingRight(angle) => rotateBoard(true, angle, env, gameStuff)
  | Paused => drawNothing(env, gameStuff)
  };
  drawGame(env, newGameStuff);
  newGameStuff;
};

let keyTyped = (gameStuff: gameStuff, env) => {
  {
    ...gameStuff,
    gameState: EggGame.processRotate(gameStuff.gameState, Env.keyCode(env))
  };
};

run(~setup, ~draw, ~keyTyped, ());
