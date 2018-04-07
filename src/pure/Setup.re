open EggTypes;

let createPlayer = (x: int, y: int, playerType: playerType) : option(player) => {
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
    }, Player.getPlayerByType(playerType));
};

let createPlayers = (board: board): list(player) => {
    List.fold_right((tile: tile, players: list(player)) => {
        let optPlayer = createPlayer(tile.x, tile.y, tile.createPlayer);
        switch (optPlayer) {
        | Some(player) => List.append(players, [player])
        | _ => players
        }
    }, Board.getBoardTiles(board), []);
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