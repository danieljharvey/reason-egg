open EggTypes;
open JsTypes;

let createPlayer = (x: int, y: int, playerType: playerType, id: int) : option(player) => {
    let coords = { ...Player.defaultCoords, x, y };
    let direction = {
        ...Player.defaultCoords,
        x: 1
    };
    Utils.optionMap(player => {
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

let loadGameState = (levelID: int): gameState => {
    let board = Board.getLevel(levelID);
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
        visualMode: Tint.getTintForLevelID(levelID),
        levelID
    };
};

let setupEnvironment = (gameState: gameState, env): gameStuff => 
{    
    {
        tileImages: DrawTile.loadTileImages(Tiles.tiles, env),
        playerImages: DrawPlayer.loadPlayerImages(Player.playerTypes, env),
        boardAngle: 0.0,
        gameState: gameState,
        lastAngleChange: 0.0
    };
};