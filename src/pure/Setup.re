open EggTypes;

let isEggCup = (tile: tile): bool => {
    tile.action === "completeLevel"
};

let createPlayers = (board: board): list(player) => {
    let eggCups = List.filter(isEggCup, Board.getBoardTiles(board));
    List.map((tile: tile) => {
        Player.createPlayer(~filename="sprites/egg-rainbow.png", ~coords={...Player.defaultCoords, x: tile.x, y: tile.y}, ());
    }, eggCups);
};

let setupEnvironment = (board: board, env): gameStuff => 
{
    let players = createPlayers(board);
    {
        players: players,
        tileImages: Tiles.loadTileImages(env),
        playerImages: Player.loadPlayerImages(players, env),
        boardAngle: 0.0,
        drawAngle: 0.0,
        boardSize: List.length(board),
        gameState: Playing,
        board
    };
  };