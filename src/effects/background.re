open Reprocessing;

open EggTypes;

let clearBackground = (gameStuff: gameStuff, env) => {
  Draw.fill({
    r: 0.0,
    g: 0.0,
    b: 0.0,
    a: 0.3
  }, env);
  let (width, height) = EggConstants.screenSize;
  Draw.rect(~pos=(0,0), ~width=width, ~height=height, env);
};