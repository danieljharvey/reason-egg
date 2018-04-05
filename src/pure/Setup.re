open EggTypes;

let isEggCup = (tile: tile): bool => {
    tile.action === "completeLevel"
};

let createPlayers = (board: board): list(player) => {
    let eggCups = List.filter(isEggCup, Board.getBoardTiles(board));
    List.map((tile: tile) => {
        Player.createPlayer(~filename="sprites/egg-rainbow.png", ~coords={...Player.defaultCoords, x: tile.x, y: tile.y}, ~direction={...Player.defaultCoords, x: 1}, ());
    }, eggCups);
};

let defaultGameState = (board: board): gameState => {
    {
        players: createPlayers(board),
        board,
        score: 0,
        rotations: 0,
        rotateAngle: 0.0,
        outcome: ""
    };
};

let setupEnvironment = (gameState: gameState, env): gameStuff => 
{    
    {
        tileImages: Tiles.loadTileImages(env),
        playerImages: Player.loadPlayerImages(gameState.players, env),
        boardAngle: 0.0,
        drawAngle: 0.0,
        gameState: gameState,
        programState: Playing
    };
};