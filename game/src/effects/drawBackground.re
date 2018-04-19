open Reprocessing;

open EggTypes;
open JsTypes;



let clearBackground = (gameStuff: gameStuff, env) => {
  let fill = Background.getBackgroundColour(gameStuff.gameState); 
  Draw.pushMatrix(env);
  Draw.fill(RenderUtils.convertColor(fill), env);
  let (width, height) = EggConstants.screenSize;
  Draw.rect(~pos=(0,0), ~width=width, ~height=height, env);
  Draw.popMatrix(env);
};