open Reprocessing;

open EggTypes;

let colourFloat = (color: int): float => {
  float_of_int(color) /. 255.0;
};

let getFigure = (multiplier: int, frame: int): int => {
  let newFigure = (frame / multiplier) mod (512);
  (newFigure > 256) ? 256 - (newFigure mod 256) : newFigure;
};

let getBackgroundColour = (gameState: gameState): fillColour => {
  {
    r: colourFloat(getFigure(6, gameState.currentFrame)),
    g: colourFloat(getFigure(8, gameState.currentFrame)),
    b: colourFloat(getFigure(9, gameState.currentFrame)),
    a: 0.3
  };
};

let clearBackground = (gameStuff: gameStuff, env) => {
  Draw.fill(getBackgroundColour(gameStuff.gameState), env);
  let (width, height) = EggConstants.screenSize;
  Draw.rect(~pos=(0,0), ~width=width, ~height=height, env);
};