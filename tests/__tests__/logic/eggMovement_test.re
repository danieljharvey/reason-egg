open EggTypes;

open Jest;

describe("Egg movements", () => {
  test("Stay still when not moving", () => {
    open Expect;
    let player = Player.defaultPlayer;
    let response = EggMovement.incrementPlayerFrame(player);
    expect(response.currentFrame) |> toEqual(player.currentFrame);
  });
  test("Wipe old direction when stopped", () => {
    open Expect;
    let player = {
      ...Player.defaultPlayer,
      oldDirection: {
        ...Player.defaultCoords,
        x: 1,
        y: 0
      }
    };
    let expected = Player.defaultCoords;
    let response = EggMovement.incrementPlayerFrame(player);
    expect(response.oldDirection) |> toEqual(expected);
  });
  test("Move left", () => {
    open Expect;
    let player = {
      ...Player.defaultPlayer,
      direction: {
        ...Player.defaultCoords,
        x: (-1)
      },
      coords: {
        ...Player.defaultCoords,
        x: 2,
        y: 2
      }
    };
    let timePassed = 10.0;
    let moveAmount = EggMovement.calcMoveAmount(player.moveSpeed, timePassed);
    let expected = {
      ...player,
      coords: {
        ...player.coords,
        offsetX: - moveAmount
      }
    };
    let response = EggMovement.incrementPlayerDirection(timePassed, player);
    expect(response) |> toEqual(expected);
  });
  test("Move right", () => {
    open Expect;
    let player = {
      ...Player.defaultPlayer,
      direction: {
        ...Player.defaultCoords,
        x: 1
      },
      coords: {
        ...Player.defaultCoords,
        x: 2,
        y: 2
      }
    };
    let timePassed = 10.0;
    let moveAmount = EggMovement.calcMoveAmount(player.moveSpeed, timePassed);
    let expected = {
      ...player,
      coords: {
        ...player.coords,
        offsetX: moveAmount
      }
    };
    let response = EggMovement.incrementPlayerDirection(timePassed, player);
    expect(response) |> toEqual(expected);
  });
  test("Move up", () => {
    open Expect;
    let player = {
      ...Player.defaultPlayer,
      direction: {
        ...Player.defaultCoords,
        y: (-1)
      },
      coords: {
        ...Player.defaultCoords,
        x: 2,
        y: 2
      }
    };
    let timePassed = 10.0;
    let moveAmount = EggMovement.calcMoveAmount(player.moveSpeed, timePassed);
    let expected = {
      ...player,
      coords: {
        ...player.coords,
        offsetY: - moveAmount
      }
    };
    let response = EggMovement.incrementPlayerDirection(timePassed, player);
    expect(response) |> toEqual(expected);
  });
  test("Move down", () => {
    open Expect;
    let player = {
      ...Player.defaultPlayer,
      direction: {
        ...Player.defaultCoords,
        y: 1
      },
      coords: {
        ...Player.defaultCoords,
        x: 2,
        y: 2
      }
    };
    let timePassed = 10.0;
    let moveAmount = EggMovement.calcMoveAmount(player.moveSpeed, timePassed);
    let expected = {
      ...player,
      coords: {
        ...player.coords,
        offsetY: moveAmount
      }
    };
    let response = EggMovement.incrementPlayerDirection(timePassed, player);
    expect(response) |> toEqual(expected);
  });
  test("change frame left", () => {
    open Expect;
    let player: player = {
      ...Player.defaultPlayer,
      currentFrame: 3,
      direction: {
        ...Player.defaultCoords,
        x: (-1),
        y: 0
      }
    };
    let response = EggMovement.incrementPlayerFrame(player);
    expect(response.currentFrame) |> toEqual(2);
  });
  test("change frame right", () => {
    open Expect;
    let player: player = {
      ...Player.defaultPlayer,
      currentFrame: 10,
      frames: 11,
      oldDirection: {
        ...Player.defaultCoords,
        x: 1,
        y: 0
      }
    };
    let response = EggMovement.incrementPlayerFrame(player);
    expect(response.currentFrame) |> toEqual(0);
  });
  test("change going up", () => {
    open Expect;
    let player: player = {
      ...Player.defaultPlayer,
      currentFrame: 3,
      direction: {
        ...Player.defaultCoords,
        x: 0,
        y: (-1)
      }
    };
    let response = EggMovement.incrementPlayerFrame(player);
    expect(response.currentFrame) |> toEqual(2);
  });
  test("change going down", () => {
    open Expect;
    let player: player = {
      ...Player.defaultPlayer,
      currentFrame: 10,
      frames: 11,
      oldDirection: {
        ...Player.defaultCoords,
        x: 0,
        y: 1
      }
    };
    let response = EggMovement.incrementPlayerFrame(player);
    expect(response.currentFrame) |> toEqual(0);
  });
  test("Calculate move amount 1", () => {
    open Expect;
    let player = Player.defaultPlayer;
    expect(EggMovement.calcMoveAmount(10, 10.0)) |> toEqual(4000);
  });
  test("Calculate move amount 2", () => {
    open Expect;
    let player = Player.defaultPlayer;
    expect(EggMovement.calcMoveAmount(10, 20.0)) |> toEqual(8000);
  });
  test("Egg with no speed stays still", () => {
    open Expect;
    let player = {...Player.defaultPlayer, moveSpeed: 0};
    let movedPlayer = EggMovement.incrementPlayerDirection(1.0, player);
    expect(player.coords) |> toEqual(movedPlayer.coords);
  });
  test("No change in overflow", () => {
    open Expect;
    let coords: coords = {x: 1, y: 0, offsetX: 63, offsetY: 0};
    let fixedCoords = EggMovement.correctTileOverflow(coords);
    expect(fixedCoords) |> toEqual(coords);
  });
  test("Overflow to right updates x", () => {
    open Expect;
    let coords: coords = {x: 0, y: 0, offsetX: 100, offsetY: 0};
    let fixedCoords = EggMovement.correctTileOverflow(coords);
    expect(fixedCoords.x) |> toEqual(1);
  });
  test("Overflow to right updates offsetX", () => {
    open Expect;
    let coords: coords = {x: 0, y: 0, offsetX: 100, offsetY: 0};
    let fixedCoords = EggMovement.correctTileOverflow(coords);
    expect(fixedCoords.offsetX) |> toEqual(0);
  });
  test("Overflow to left updates x", () => {
    open Expect;
    let coords: coords = {x: 3, y: 0, offsetX: (-100), offsetY: 0};
    let fixedCoords = EggMovement.correctTileOverflow(coords);
    expect(fixedCoords.x) |> toEqual(2);
  });
  test("Overflow to left updates offsetX", () => {
    open Expect;
    let coords: coords = {x: 3, y: 0, offsetX: (-100), offsetY: 0};
    let fixedCoords = EggMovement.correctTileOverflow(coords);
    expect(fixedCoords.offsetX) |> toEqual(0);
  });
});
/*

 test("No overflow above", () => {
   const coords = new Coords({ x: 0, y: 4, offsetX: 0, offsetY: -100 });

   const fixedCoords = Movement.correctTileOverflow(coords);

   expect(fixedCoords.y).toEqual(3);
   expect(fixedCoords.offsetY).toEqual(0);
 });

 test("No overflow below", () => {
   const coords = new Coords({ x: 0, y: 4, offsetX: 0, offsetY: 100 });

   const fixedCoords = Movement.correctTileOverflow(coords);

   expect(fixedCoords.y).toEqual(5);
   expect(fixedCoords.offsetY).toEqual(0);
 });

 test("Fall through breakable block", () => {
   const boardArray = [
     [
       new Tile({ background: true, breakable: false }),
       new Tile({ background: false, breakable: true })
     ]
   ];

   const board = new Board(boardArray);

   const player = new Player({
     coords: new Coords({
       x: 0,
       y: 0
     }),
     falling: true
   });

   const result = Movement.checkFloorBelowPlayer(board, 10)(player);

   expect(result.equals(player)).toEqual(true);
   expect(result.falling).toEqual(true);
 });

 test("Don't fall through floor", () => {
   const boardArray = [
     [
       new Tile({ background: true, breakable: false }),
       new Tile({ background: false, breakable: false })
     ]
   ];

   const board = new Board(boardArray);

   const player = new Player({
     coords: new Coords({
       x: 0,
       y: 0
     }),
     falling: true
   });

   const expected = player.modify({
     falling: false
   });

   const result = Movement.checkFloorBelowPlayer(board, 10)(player);

   expect(result.equals(expected)).toEqual(true);
   expect(result.falling).toEqual(false);
 });

 test("Non-flying players fall downwards", () => {
   const boardArray = [
     [new Tile({ background: true }), new Tile({ background: true })]
   ];

   const board = new Board(boardArray);

   const player = new Player({
     coords: new Coords({
       x: 0,
       y: 0
     }),
     falling: false
   });

   const expected = player.modify({
     falling: true
   });

   const result = Movement.checkFloorBelowPlayer(board, 10)(player);

   expect(result.equals(expected)).toEqual(true);
   expect(result.falling).toEqual(true);
 });

 test("Flying players don't fall through floor", () => {
   const boardArray = [
     [
       new Tile({ background: true, breakable: false }),
       new Tile({ background: true, breakable: false })
     ]
   ];

   const board = new Board(boardArray);

   const player = new Player({
     coords: new Coords({
       x: 0,
       y: 0
     }),
     flying: true,
     falling: true
   });

   const expected = player.modify({
     falling: false // flying players are never falling
   });

   const result = Movement.checkFloorBelowPlayer(board, 10)(player);

   expect(result.equals(expected)).toEqual(true);
   expect(result.falling).toEqual(false);
 });

 test("Check player has not moved", () => {
   const oldPlayer = new Player({
     coords: new Coords({ x: 0, y: 0 })
   });

   const newPlayer = oldPlayer.modify({ id: 3 });

   const moved = Movement.playerHasMoved(oldPlayer, newPlayer);

   expect(moved).toEqual(false);
 });

 test("Check player has moved", () => {
   const oldPlayer = new Player({
     coords: new Coords({ x: 0, y: 0, offsetX: 3 })
   });

   const newPlayer = oldPlayer.modify({
     coords: oldPlayer.coords.modify({ offsetX: 0 })
   });

   const moved = Movement.playerHasMoved(oldPlayer, newPlayer);

   expect(moved).toEqual(true);
 });

 test("Don't bounce off anything", () => {
   const boardArray = [
     [new Tile({ background: true })],
     [new Tile({ background: true })],
     [new Tile({ background: true })]
   ];

   const board = new Board(boardArray);

   const player = new Player({
     coords: new Coords({
       x: 1,
       y: 0
     }),
     direction: new Coords({
       x: -1
     })
   });

   const result = Movement.checkPlayerDirection(board)(player);

   expect(result.equals(player)).toEqual(true);
 });

 test("Bounce off a wall to the left", () => {
   const boardArray = [
     [new Tile({ background: false })],
     [new Tile({ background: true })],
     [new Tile({ background: true })]
   ];

   const board = new Board(boardArray);

   const player = new Player({
     coords: new Coords({
       x: 1,
       y: 0
     }),
     direction: new Coords({
       x: -1
     })
   });

   const expected = player.modify({
     direction: new Coords({
       x: 1
     })
   });

   const result = Movement.checkPlayerDirection(board)(player);

   expect(result.equals(expected)).toEqual(true);
 });

 test("Bounce off a wall to the right", () => {
   const boardArray = [
     [new Tile({ background: true, breakable: false })],
     [new Tile({ background: true, breakable: false })],
     [new Tile({ background: false, breakable: false })]
   ];

   const board = new Board(boardArray);

   const player = new Player({
     coords: new Coords({
       x: 1,
       y: 0
     }),
     direction: new Coords({
       x: 1
     })
   });

   const expected = player.modify({
     direction: new Coords({
       x: -1
     })
   });

   const result = Movement.checkPlayerDirection(board)(player);

   expect(result.equals(expected)).toEqual(true);
 });

 test("Flying player bounce off wall above", () => {
   const boardArray = [
     [
       new Tile({ background: false, breakable: false }),
       new Tile({ background: true, breakable: false }),
       new Tile({ background: true, breakable: false })
     ]
   ];

   const board = new Board(boardArray);

   const player = new Player({
     coords: new Coords({
       x: 0,
       y: 1
     }),
     direction: new Coords({
       y: -1
     }),
     flying: true
   });

   const expected = player.modify({
     direction: new Coords({
       x: 1,
       y: 0
     })
   });

   const result = Movement.checkPlayerDirection(board)(player);

   expect(result.equals(expected)).toEqual(true);
 });

 test("Flying player bounce off right", () => {
   const boardArray = [
     [new Tile({ background: true, breakable: false })],
     [new Tile({ background: true, breakable: false })],
     [new Tile({ background: false, breakable: false })]
   ];

   const board = new Board(boardArray);

   const player = new Player({
     coords: new Coords({
       x: 1,
       y: 0
     }),
     direction: new Coords({
       x: 1
     }),
     flying: true
   });

   const expected = player.modify({
     direction: new Coords({
       x: 0,
       y: 1
     })
   });

   const result = Movement.checkPlayerDirection(board)(player);

   expect(result.equals(expected)).toEqual(true);
 });

 test("Flying player bounce off wall below", () => {
   const boardArray = [
     [
       new Tile({ background: true, breakable: false }),
       new Tile({ background: true, breakable: false }),
       new Tile({ background: false, breakable: false })
     ]
   ];

   const board = new Board(boardArray);

   const player = new Player({
     coords: new Coords({
       x: 0,
       y: 1
     }),
     direction: new Coords({
       y: 1
     }),
     flying: true
   });

   const expected = player.modify({
     direction: new Coords({
       x: -1,
       y: 0
     })
   });

   const result = Movement.checkPlayerDirection(board)(player);

   expect(result.equals(expected)).toEqual(true);
 });

 test("Flying player bounce off left", () => {
   const boardArray = [
     [new Tile({ background: false })],
     [new Tile({ background: true })],
     [new Tile({ background: true })]
   ];

   const board = new Board(boardArray);

   const player = new Player({
     coords: new Coords({
       x: 1,
       y: 0
     }),
     direction: new Coords({
       x: -1
     }),
     flying: true
   });

   const expected = player.modify({
     direction: new Coords({
       x: 0,
       y: -1
     })
   });

   const result = Movement.checkPlayerDirection(board)(player);

   expect(result.equals(expected)).toEqual(true);
 });

 */