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

  test("Recognse if player is on a tile", () => {
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

});

/*













test("Recognise if player isn't on a tile", () => {
  const player1 = new Player({
    coords: new Coords({
      x: 1,
      y: 1
    })
  });

  const tile = new Tile({
    action: "split-eggs",
    x: 1,
    y: 2
  });

  const actual = BoardCollisions.isPlayerOnTile(player1)(tile);

  expect(actual).toEqual(false);
});

test("Do nothing when player is of minimum value", () => {
  const player1 = new Player({
    coords: new Coords({
      x: 1,
      y: 1
    }),
    value: 1
  });

  const actual = BoardCollisions.checkBoardCollisions(board, [
    player1
  ]);

  expect(actual).toEqual([player1]);
});

test("Split a 2-value egg", () => {
  const actual = BoardCollisions.newValues(2);

  expect(actual).toEqual([1, 1]);
});

test("Split a 3-value egg", () => {
  const actual = BoardCollisions.newValues(3);

  expect(actual).toEqual([2, 1]);
});

test("Split a 4-value egg", () => {
  const actual = BoardCollisions.newValues(4);

  expect(actual).toEqual([2, 2]);
});

test("Split a 2-value egg", () => {
  const player = new Player({
    value: 2
  });

  const expected = [
    player.modify({
      direction: new Coords({
        x: -1
      }),
      value: 1,
      img: "egg-sprite.png",
      title: "It is of course the egg",
      lastAction: "split",
      frames: 18
    }),
    player.modify({
      direction: new Coords({
        x: 1
      }),
      value: 1,
      img: "egg-sprite.png",
      title: "It is of course the egg",
      lastAction: "split",
      frames: 18
    })
  ];

  const actual = BoardCollisions.splitPlayer(player);

  expect(actual).toEqual(expected);
});

test("Get values and directions", () => {
  const value = 2;

  const expected = [{ value: 1, direction: -1 }, { value: 1, direction: 1 }];

  const actual = BoardCollisions.getValuesAndDirections(value);

  expect(actual).toEqual(expected);
});

test("Split a 3-value egg when the time is right", () => {
  const player1 = new Player({
    coords: new Coords({
      x: 1,
      y: 1
    }),
    value: 3
  });

  const expected = [
    player1.modify({
      direction: new Coords({
        x: -1
      }),
      value: 2,
      img: "egg-sprite-red.png",
      title: "It is of course the red egg",
      type: 'red-egg',
      id: 0,
      frames :18,
      multiplier: 2,
      lastAction: "split"
    }),
    player1.modify({
      direction: new Coords({
        x: 1
      }),
      img: 'egg-sprite.png',
      title: "It is of course the egg",
      value: 1,
      id: 1,
      frames: 18,
      lastAction: "split"
    })
  ];

  const actual = BoardCollisions.checkBoardCollisions(board, [
    player1
  ]);

  expect(actual).toEqual(expected);
});

*/