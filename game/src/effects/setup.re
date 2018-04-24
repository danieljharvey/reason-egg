open EggTypes;
open JsTypes;

let setupEnvironment = (gameState: gameState, env): gameStuff => 
{    
    {
        tileImages: DrawTile.loadTileImages(Tiles.tiles, env),
        playerImages: DrawPlayer.loadPlayerImages(Player.playerTypes, env),
        audioAssets: PlayAudio.loadAudioFiles(PlayAudio.audio, env),
        boardAngle: 0.0,
        gameState: gameState,
        lastAngleChange: 0.0
    };
};