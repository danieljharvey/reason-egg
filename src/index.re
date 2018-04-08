open Reprocessing;

open EggTypes;

open EggConstants;

let setup = (env) => {
  let (width, height) = screenSize;
  Env.size(~width, ~height, env);
  let gameState = Setup.defaultGameState(Board.board);
  Setup.setupEnvironment(gameState, env);
};

let updateGameStuff = (gameStuff: gameStuff, deltaTime: float): gameStuff => {
  ...gameStuff,
  gameState: EggGame.doAction(gameStuff.gameState, deltaTime),
  boardAngle: gameStuff.boardAngle +. 0.01
};

let drawGame = (env, gameStuff: gameStuff) => {
  Render.render(env, gameStuff);
};

let drawNothing = (env, gameStuff: gameStuff): gameStuff => {
  Draw.background(Constants.white, env);
  gameStuff;
};

let rotateBoardLeft = (angle: float, env, gameStuff, deltaTime): gameStuff => {
  let boardAngle = -1.0 *. angle;
  let newAngle = angle +. (deltaTime *. EggConstants.rotateSpeed);
  let newGameAction = angle > 90.0 ? TurnLeft : RotatingLeft(newAngle);
  {
    ...gameStuff,
    gameState: {
      ...gameStuff.gameState,
      gameAction: newGameAction,
      boardAngle
    }
  };
};

let rotateBoardRight = (angle: float, env, gameStuff, deltaTime): gameStuff => {
  let boardAngle = angle;
  let newAngle = angle +. (deltaTime *. EggConstants.rotateSpeed);
  let newGameAction = angle > 90.0 ? TurnRight : RotatingRight(newAngle);
  {
    ...gameStuff,
    gameState: {
      ...gameStuff.gameState,
      gameAction: newGameAction,
      boardAngle
    }
  };
};


let draw = (gameStuff: gameStuff, env): gameStuff => {
  let deltaTime = Env.deltaTime(env);
  let newGameStuff = switch gameStuff.gameState.gameAction {
  | RotatingLeft(angle) => rotateBoardLeft(angle, env, gameStuff, deltaTime)
  | RotatingRight(angle) => rotateBoardRight(angle, env, gameStuff, deltaTime)
  | Paused => drawNothing(env, gameStuff)
  | _ => updateGameStuff(gameStuff, deltaTime)
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
