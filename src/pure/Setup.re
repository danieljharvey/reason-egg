open EggTypes;

let isEggCup = (tile: tile): bool => {
    tile.action === "completeLevel"
};

let createPlayer = (x: int, y: int, playerType: string) : option(player) => {
    let coords = { ...Player.defaultCoords, x, y };
    let direction = {
        ...Player.defaultCoords,
        x: 1
    };
    EggUtils.optionMap(player => {
        {
            ...player, 
            coords,  
            direction   
        }
    }, Player.getPlayerByType("egg"));
};

let createPlayers = (board: board): list(player) => {
    let eggCups = List.filter(isEggCup, Board.getBoardTiles(board));
    List.fold_right((tile: tile, players: list(player)) => {
        let optPlayer = createPlayer(tile.x, tile.y, "egg");
        switch (optPlayer) {
        | Some(player) => List.append(players, [player])
        | _ => players
        }
    }, eggCups, []);
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