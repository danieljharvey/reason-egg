open Reprocessing;

open EggTypes;

let colourFloat = (color: int): float => {
  float_of_int(color) /. 255.0;
};

let getFigure = (maximum: int, multiplier: float, frame: int): int => {
  let newFigure = int_of_float(float_of_int(frame) /. multiplier) mod (maximum * 2);
  (newFigure > maximum) ? maximum - (newFigure mod maximum) : newFigure;
};

let getVibesBackgroundColour = (gameState: gameState): fillColour => {
  {
    r: colourFloat(getFigure(256, 0.4, gameState.currentFrame)),
    g: colourFloat(getFigure(256, 0.5, gameState.currentFrame)),
    b: colourFloat(getFigure(256, 0.2, gameState.currentFrame)),
    a: 0.05
  };
};

let getStandardBackgroundColour = (gameState: gameState): fillColour => {
  {
    r: colourFloat(getFigure(64, 10.0, gameState.currentFrame)),
    g: colourFloat(getFigure(64, 20.0, gameState.currentFrame)),
    b: colourFloat(getFigure(64, 9.0, gameState.currentFrame)),
    a: 0.5
  };
};

let getBackgroundColour = (gameState: gameState): fillColour => {
  gameState.visualMode == Standard ? getStandardBackgroundColour(gameState) : getVibesBackgroundColour(gameState)
};

let clearBackground = (gameStuff: gameStuff, env) => {
  Draw.fill(getBackgroundColour(gameStuff.gameState), env);
  let (width, height) = EggConstants.screenSize;
  Draw.rect(~pos=(0,0), ~width=width, ~height=height, env);
};