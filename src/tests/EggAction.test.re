open EggTypes;
open Reunit;

let makeSimpleBoard = (): board => {
  let tile = {
    ...Tiles.blankTile,
    x: 0,
    y: 0,
    action: Collectable(100)
  };

  [[tile]];
};

test("Do nothing if player not centered on board in X axis", true, () => {
  let board = makeSimpleBoard();

  let player = {
    ...Player.defaultPlayer,
    coords: {
        ...Player.defaultCoords,
        x: 0,
        y: 0,
        offsetX: 1
    }
  };

  let output = EggAction.checkPlayerTileAction(player, board, 0, "");

  output.board == board;
});