open EggTypes;

let cycleFrame = (currentFrame: int, tile: tile): tile => {
    (currentFrame mod tile.cycleSpeed === 0) ?
    {
        ...tile,
        currentFrame: (tile.currentFrame >= tile.frames - 1) ? 0 : tile.currentFrame + 1
    }: tile;
};

let boardFold = (currentFrame: int, tile: tile, board: board): board => 
    Board.changeTile(board, cycleFrame(currentFrame, tile));

let cycleAllTileFrames = (currentFrame: int, board: board): board => 
    List.fold_right(boardFold(currentFrame), Board.getDrawTiles(board), board);

let incrementGameFrame = (currentFrame: int): int => 
    (currentFrame < max_int) ? currentFrame + 1 : 0;


let cycleAll = (gameState: gameState): gameState => {
    {
        ...gameState,
        currentFrame: incrementGameFrame(gameState.currentFrame),
        board: cycleAllTileFrames(gameState.currentFrame, gameState.board)
    };
};