open EggTypes;

let createPlayer = (x: int, y: int, playerType: playerType, id: int) : option(player) => {
    let coords = { ...Player.defaultCoords, x, y };
    let direction = {
        ...Player.defaultCoords,
        x: 1
    };
    EggUtils.optionMap(player => {
        {
            ...player, 
            coords,  
            direction,
            id   
        }
    }, Player.getPlayerByType(playerType));
};

let createPlayers = (board: board): list(player) => {
    List.fold_right((tile: tile, players: list(player)) => {
        let id = List.length(players) + 1;
        let optPlayer = createPlayer(tile.x, tile.y, tile.createPlayer, id);
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
        rotations: (0,0),
        drawAngle: 0.0,
        outcome: "",
        gameAction: Playing,
        boardAngle: 0.0,
        currentFrame: 0,
        visualMode: Standard
    };
};

let setupEnvironment = (gameState: gameState, env): gameStuff => 
{    
    {
        tileImages: Tiles.loadTileImages(env),
        playerImages: Player.loadPlayerImages(Player.playerTypes, env),
        boardAngle: 0.0,
        gameState: gameState,
        lastAngleChange: 0.0
    };
};