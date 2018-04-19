open EggTypes;
open Utils;

let getVibesBackgroundColour = (gameState: gameState): color => {
  {
    r: colourFloat(getFigure(256, 0.4, gameState.currentFrame)),
    g: colourFloat(getFigure(256, 0.5, gameState.currentFrame)),
    b: colourFloat(getFigure(256, 0.2, gameState.currentFrame)),
    a: 0.05
  };
};

let getNightTimeBackgroundColour = (gameState: gameState): color => {
  {
    r: 0.3 +. colourFloat(getFigure(128, 6.0, gameState.currentFrame)),
    g: 0.3 +. colourFloat(getFigure(128, 5.0, gameState.currentFrame)),
    b: 0.3 +. colourFloat(getFigure(128, 4.0, gameState.currentFrame)),
    a: 0.4
  };
};

let getStandardBackgroundColour = (gameState: gameState): color => {
  {
    r: colourFloat(getFigure(64, 10.0, gameState.currentFrame)),
    g: colourFloat(getFigure(64, 20.0, gameState.currentFrame)),
    b: colourFloat(getFigure(64, 9.0, gameState.currentFrame)),
    a: 0.5
  };
};

let getGreyScaleBackgroundColour = (gameState: gameState): color => {
  let amount = 0.2 +. colourFloat(getFigure(30, 20.0, gameState.currentFrame));
  {
    r: amount,
    g: amount,
    b: amount,
    a: 0.3
  };
};

let getBackgroundColour = (gameState: gameState): color => {
  switch (gameState.visualMode) {
  | Standard => getStandardBackgroundColour(gameState)
  | NightTime => getNightTimeBackgroundColour(gameState)
  | MegaVibes => getVibesBackgroundColour(gameState)
  | GreyScale => getGreyScaleBackgroundColour(gameState)
  }
};
