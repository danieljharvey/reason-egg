open Respect.Dsl;

open EggTypes;

let makeSimpleBoard = (): board => {
  let tile = {
    ...Tiles.blankTile,
    x: 0,
    y: 0,
    action: Collectable(100)
  };

  [[tile]];
};

describe "Egg Actions" [
  it "does nothing if player not centered on board in X axis" ((_) => {(
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
  )})
] |> register