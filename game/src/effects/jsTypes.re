open EggTypes;

/* keep all reprocessing-centric stuff here */

type imageAsset = (string, Reprocessing_Types.Types.imageT);

type fillColour = Reprocessing_Types.Types.colorT;

type audioAsset = (string, Reprocessing_Types.Types.soundT);

type gameStuff = {
    playerImages: list(imageAsset),
    tileImages: list(imageAsset),
    boardAngle: float,
    lastAngleChange: float,
    gameState: gameState,
    audioAssets: list(audioAsset)
  };
  
