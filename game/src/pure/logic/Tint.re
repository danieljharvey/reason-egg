open EggTypes;
open Utils;

let standardTint: color = {
    r: 0.0,
    g: 0.0,
    b: 0.0,
    a: 1.0
};

let nightTime: color = {
    r: 0.1,
    g: 0.1,
    b: 0.15,
    a: 0.8
};

let greyScale: color = {
    r: 0.6,
    g: 0.6,
    b: 0.6,
    a: 0.8
};

let vibesTint = (gameState: gameState): color => {
    {
        r: 1.0 -. colourFloat(getFigure(256, 0.4, gameState.currentFrame)),
        g: 1.0 -. colourFloat(getFigure(256, 0.5, gameState.currentFrame)),
        b: 1.0 -. colourFloat(getFigure(256, 0.2, gameState.currentFrame)),
        a: 0.2
    };
};

let getTint = (gameState: gameState) : option(color) => 
    switch gameState.visualMode {
    | NightTime => Some(nightTime)
    | GreyScale => Some(greyScale)
    | MegaVibes => Some(vibesTint(gameState))
    | _ => None
    };

let getTintForLevelID = (levelID: int): visualMode => {
    (levelID mod 3 == 0) ? NightTime : (levelID mod 2 == 0) ? GreyScale : Standard;
};