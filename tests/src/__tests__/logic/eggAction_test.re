open EggTypes;
open Jest;

describe("Expect", () => {
  open Expect;

  test("toBe", () =>
    expect(1 + 2) |> toBe(3))
});

describe("Expect.Operators", () => {
    open Expect;
    open! Expect.Operators;

    test("==", () =>
      expect(1 + 2) === 3)
  }
);

let makeSimpleBoard = (): board => {
  let tile = {
    ...Tiles.blankTile,
    x: 0,
    y: 0,
    action: Collectable(100)
  };

  [[tile]];
};

describe("Egg Actions", () => {
  test("Do nothing if player not centered on board in X axis", () => 
  {
    open Expect;

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
  
    expect(output.board) |> toEqual(board);
  
});

test("Do nothing if player not centered on board in Y axis", () => {
  open Expect;

    let board = makeSimpleBoard();
  
    let player = {
      ...Player.defaultPlayer,
      coords: {
          ...Player.defaultCoords,
          x: 0,
          y: 0,
          offsetY: -10
      }
    };

    let output = EggAction.checkPlayerTileAction(player, board, 0, "");
  
    expect(output.board) |> toEqual(board);
});

test("Do nothing if player has not moved", () => {
  open Expect;

    let board = makeSimpleBoard();
  
    let player = {
      ...Player.defaultPlayer,
      coords: Player.defaultCoords,
      moved: false
    };

    let output = EggAction.checkPlayerTileAction(player, board, 0, "");
  
    expect(output.board) |> toEqual(board);
});

test("Change board if player has moved", () => {
  open Expect;

  let board = makeSimpleBoard();
  
  let player = {
    ...Player.defaultPlayer,
    coords: Player.defaultCoords,
    moved: true
  };

  let output = EggAction.checkPlayerTileAction(player, board, 0, "");
  
  expect(output.board) |> Expect.not_ |> toEqual(board);

  expect(output.score) |> toEqual(100);
});

})

/*




test("Change board if player has moved", () => {
  const board = makeSimpleBoard();

  const player = new Player({
    coords: new Coords({
      x: 0,
      y: 0
    }),
    moved: true
  });

  const action = new Action();

  const output = action.checkPlayerTileAction(player, board, 0, "");

  expect(is(output.board, board)).toEqual(false);
  expect(output.score).toEqual(100); // tile was collected
});
*/