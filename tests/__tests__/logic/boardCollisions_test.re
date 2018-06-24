open EggTypes;
open Jest;

let blankTile = Tiles.blankTile;

let splitterTile: tile = {
  ...Tiles.idTile,
  background: true,
  action: SplitEggs,
  x: 1,
  y: 1
};

let blankBoard: board = [[blankTile, blankTile], [blankTile, blankTile]];

let board: board = [
  [blankTile, blankTile, blankTile],
  [blankTile, splitterTile, blankTile],
  [blankTile, blankTile, blankTile]
];

describe("Board Collisions", () => {
  test("Ignores when not on whole tile", () => {
    open Expect;

    let player1 = {
      ...Player.defaultPlayer,
      coords: { ...Player.defaultCoords, offsetX: 10 }
    };
  
    expect(BoardCollisions.checkBoardCollisions(board, [player1])) |> toEqual([player1]);
  });

  test("Get splitter tiles", () => {
    open Expect;

    let tiles = BoardCollisions.getSplitterTiles(board);
  
    expect(List.length(tiles)) |> toEqual(1);
  });

  test("Do nothing when no splitter tiles", () => {
    open Expect;

    let player1: player = {
      ...Player.defaultPlayer,
      coords: { ...Player.defaultCoords, offsetX: 10 }
    };
  
    expect(BoardCollisions.checkBoardCollisions(blankBoard, [player1])) |> toEqual([player1]);
  });

  test("Do nothing when player is not on tile", () => {
    open Expect;

    let player1: player = {
      ...Player.defaultPlayer,
      coords: { ...Player.defaultCoords, x: 2, y: 2 }
    };
  
    expect(BoardCollisions.checkBoardCollisions(board, [player1])) |> toEqual([player1]);
  });

  test("Recognise if player is on a tile", () => {
    open Expect;

    let player1: player = {
      ...Player.defaultPlayer,
      coords: {
        ...Player.defaultCoords,
        x: 1,
        y: 1
      }
    };
  
    let tile: tile = {
      ...Tiles.idTile,
      action: SplitEggs,
      x: 1,
      y: 1
    };
  
    expect(BoardCollisions.isPlayerOnTile(player1)(tile)) |> toEqual(true);
  });

  test("Recognise if player isn't on a tile", () => {
    open Expect;

    let player1: player = {
      ...Player.defaultPlayer,
      coords: {
        ...Player.defaultCoords,
        x: 1,
        y: 1
      }
    };
  
    let tile: tile = {
      ...Tiles.idTile,
      action: SplitEggs,
      x: 1,
      y: 2
    };
  
    expect(BoardCollisions.isPlayerOnTile(player1)(tile)) |> toEqual(false);
  });

  test("Do nothing when player is of minimum value", () => {
    open Expect;

    let player1: player = {
      ...Player.defaultPlayer,
      value: 1,
      coords: {
        ...Player.defaultCoords,
        x: 1,
        y: 1
      }
    };

    expect(BoardCollisions.checkBoardCollisions(board, [
      player1
    ])) |> toEqual([player1]);
  });
  
  test("Split a 2-value egg", () => {
    open Expect;
    
    let actual = BoardCollisions.getValuesAndDirections(2);
    
    expect(List.length(actual)) |> toEqual(2);
  });

  test("Split a 3-value egg", () => {
    open Expect;
    
    let actual = BoardCollisions.getValuesAndDirections(3);
    
    expect(List.length(actual)) |> toEqual(2);
  });

  test("Split a 4-value egg", () => {
    open Expect;
    
    let actual = BoardCollisions.getValuesAndDirections(4);
    
    expect(List.length(actual)) |> toEqual(2);
  });

  test("Split a 2-value egg", () => {
    open Expect;

    let player = {
      ...Player.defaultPlayer,
      value: 2,
      playerType: RedEgg
    };
  
    let expected = [
      {
        ...player,
        direction: {
          ...Player.defaultCoords,
          x: -1
        },
        value: 1,
        playerType: Egg,
        filename: "sprites/egg-sprite.png",
        title: "It is of course the egg",
        lastAction: "split",
        frames: 18
      },
      {
        ...player,
        direction: {
          ...Player.defaultCoords,
          x: 1
        },
        value: 1,
        playerType: Egg,
        filename: "sprites/egg-sprite.png",
        title: "It is of course the egg",
        lastAction: "split",
        frames: 18
      }
    ];
  
    expect(BoardCollisions.splitPlayer(player)) |> toEqual(Some(expected));
  });

  test("Get values and directions", () => {
    open Expect;

    let value = 2;
    
    let left: coords = { ...Player.defaultCoords, x: -1 };
    let right: coords = { ...Player.defaultCoords, x: 1 };

    let expected: list(BoardCollisions.splitItem) = [{ value: 1, direction: left }, { value: 1, direction: right }];
  
    expect(BoardCollisions.getValuesAndDirections(value)) |> toEqual(expected);
  });

  test("Split a 3-value egg when the time is right", () => {
    open Expect;

    let player1: player = {
      ...Player.defaultPlayer,
      coords: {
        ...Player.defaultCoords,
        x: 1,
        y: 1
      },
      value: 3,
      playerType: BlueEgg
    };
  
    let expected = [
      {
        ...player1,
        direction: {
          ...Player.defaultCoords,
          x: -1
        },
        value: 2,
        filename: "sprites/egg-sprite-red.png",
        title: "It is of course the red egg",
        playerType: RedEgg,
        id: 0,
        frames :18,
        multiplier: 2,
        lastAction: "split"
      },
      {
        ...player1,
        direction: {
          ...Player.defaultCoords,
          x: 1
        },
        filename: "sprites/egg-sprite.png",
        title: "It is of course the egg",
        value: 1,
        playerType: Egg,
        id: 1,
        frames: 18,
        lastAction: "split"
      }
    ];
  
    expect(BoardCollisions.checkBoardCollisions(board, [
      player1
    ])) |> toEqual(expected);
  });

});
