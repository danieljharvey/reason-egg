open EggTypes;
open Jest;

describe("Collisions", () => {
  test("Ignores same player collision test", () => {
    open Expect;

    let player1 = Player.defaultPlayer;

    expect(EggCollisions.checkCollision(player1, player1)) |> toEqual(false);
  });

  test("Vertical collision works", () => {
    open Expect;

    let player1: player = {
      ...Player.defaultPlayer,
      coords: { x: 1, y: 1, offsetX: 0, offsetY: 0 },
      falling: true,
      id: 1,
      playerType: Egg
    };
  
    let player2: player = {
      ...Player.defaultPlayer,
      coords: { x: 1, y: 1, offsetX: 0, offsetY: 0 },
      falling: false,
      id: 2,
      playerType: Egg
    };
  
    expect(EggCollisions.checkCollision(player1, player2)) |> toEqual(true);
  });

  test("Too far for horizontal collision", () => {
    open Expect;

    let player1: player = {
      ...Player.defaultPlayer,
      coords: { x: 5, y: 5, offsetX: 1, offsetY: 0 },
      falling: false,
      id: 1,
      playerType: RedEgg
    };
  
    let player2: player = {
      ...Player.defaultPlayer,
      coords: { x: 6, y: 5, offsetX: -32, offsetY: 0 },
      falling: false,
      id: 2,
      playerType: RedEgg
    };
  
    /* difference of 31 */
  
    expect(EggCollisions.checkCollision(player1, player2)) |> toEqual(false);
  });

  test("Close enough for RHS horizontal collision", () => {

    open Expect;

    let player1: player = {
      ...Player.defaultPlayer,
      coords: { x: 5, y: 5, offsetX: 24, offsetY: 0 },
      falling: false,
      id: 1,
      playerType: RedEgg
    };
  
    let player2: player = {
      ...Player.defaultPlayer,
      coords: { x: 6, y: 5, offsetX: -24, offsetY: 0 },
      falling: false,
      id: 2,
      playerType: RedEgg
    };

  
    /* difference of 20 */
  
    expect(EggCollisions.checkCollision(player1, player2)) |> toEqual(true);
  });


  test("Close enough for LHS horizontal collision", () => {
    open Expect;

    let player1: player = {
      ...Player.defaultPlayer,
      coords: { x: 6, y: 5, offsetX: -80, offsetY: 0 },
      falling: false,
      id: 1,
      playerType: RedEgg
    };
  
    let player2: player = {
      ...Player.defaultPlayer,
      coords: { x: 5, y: 5, offsetX: 0, offsetY: 0 },
      falling: false,
      id: 2,
      playerType: RedEgg
    };
  
    /* difference of 19 */
  
    expect(EggCollisions.checkCollision(player1, player2)) |> toEqual(true);
  });

  test("Ignores collision with zero-value player", () => {
    open Expect;

    let player1: player = {
      ...Player.defaultPlayer,
      coords: { x: 1, y: 1, offsetX: 0, offsetY: 0}
    };
  
    let zeroValuePlayer: player = {
      ...player1,
      value: 0,
      id: 100
    };

    expect(EggCollisions.checkCollision(player1, zeroValuePlayer)) |> toEqual(false);
  });

  test("Ignores collision with just-split player", () => {
    open Expect;

    let player1: player = {
      ...Player.defaultPlayer,
      coords: { x: 1, y: 1, offsetX: 0, offsetY: 0},
      lastAction: "split"
    };

    let splitPlayer: player = {
      ...player1,
      id: 100
    };
  
    expect(EggCollisions.checkCollision(player1, splitPlayer)) |> toEqual(false);
  });

  test("Removes correct players", () => {
    open Expect;

    let player1: player = {
      ...Player.defaultPlayer,
      id: 1
    };

    let player2: player = {
      ...Player.defaultPlayer,
      id: 2
    };

    let players = [player1, player2];
  
    let expected = [player1];

    let collided = [(2, 3), (4, 5)];
  
    expect(EggCollisions.removeCollidedPlayers(collided, players)) |> toEqual(expected);
  });

  test("Create new players", () => {
    open Expect;

    let player1: player = {
      ...Player.defaultPlayer,
      id: 1,
      value: 1,
      coords: {x: 100, y: 100, offsetX: 0, offsetY: 0}
    };
  
    let player2: player = {
      ...Player.defaultPlayer,
      id: 2,
      value: 1,
      coords: {x: 6, y: 6, offsetX: 0, offsetY: 0}
    };

    let expected = [
      {
        ...Player.defaultPlayer,
        filename: "sprites/egg-sprite-red.png",
        multiplier: 2,
        title: "It is of course the red egg",
        playerType: RedEgg,
        value: 2,
        id: 1,
        frames: 18,
        coords: {
          x: 100,
          y: 100,
          offsetX: 0,
          offsetY: 0
        }
      }
    ];
  
    expect(EggCollisions.combinePlayers(player1, player2)) |> toEqual(expected);
  });

  test("Create no new players as no type found", () => {

    open Expect;
    
    let player1: player = {
      ...Player.defaultPlayer,
      id: 1,
      value: 10,
      coords: { x: 100, y: 100, offsetX: 0, offsetY: 0}
    };

    let player2: player = {
      ...Player.defaultPlayer,
      id: 2,
      value: 5,
      coords: { x: 6, y: 6, offsetX: 0, offsetY: 0}
    };
  
    let expected = [player1, player2];
  
    expect(EggCollisions.combinePlayers(player1, player2)) |> toEqual(expected);
  });

  test("Find collisions", () => {
    open Expect;

    let players = [
      { ...Player.defaultPlayer, id: 1, coords: { x: 1, y: 1, offsetX: 0, offsetY: 0} },
      { ...Player.defaultPlayer, id: 2, coords: { x: 1, y: 1, offsetX: 0, offsetY: 0} },
      { ...Player.defaultPlayer, id: 3, coords: { x: 10, y: 10, offsetX: 0, offsetY: 0} }
    ];
  
    let combinations = [(1, 2), (1, 3), (2, 3)];
  
    let expected = [(1, 2)];
  
    expect(EggCollisions.findCollisions(combinations, players)) |> toEqual(expected);
  });

  test("Fetch player by ID", () => {
    open Expect;

    let players = [
      { ...Player.defaultPlayer, id: 1 },
      { ...Player.defaultPlayer, id: 2 },
      { ...Player.defaultPlayer, id: 3 }
    ];
  
    let expected = Some({ ...Player.defaultPlayer, id: 2 });
  
    expect(EggCollisions.fetchPlayerByID(players, 2)) |> toEqual(expected);
  });

  test("Get all player combinations", () => {
    open Expect;

    let players = [
      { ...Player.defaultPlayer, id: 1 },
      { ...Player.defaultPlayer, id: 4 },
      { ...Player.defaultPlayer, id: 2 }
    ];
  
    let expected = [(2, 4), (1, 4), (1, 2)];
  
    expect(EggCollisions.getAllPlayerCombinations(players)) |> toEqual(expected);
  });

  test("Create new players actually works", () => {
    open Expect;

    let player1: player = {
      ...Player.defaultPlayer,
      id: 1,
      value: 1,
      coords: { x: 100, y: 100, offsetX: 0, offsetY: 0}
    };
    
    let player2: player = {
      ...Player.defaultPlayer,
      id: 2,
      value: 1,
      coords: { x: 6, y: 6, offsetX: 0, offsetY: 0}
    };

    let player3: player = {
      ...Player.defaultPlayer,
      id: 3,
      value: 2,
      coords: { x: 100, y: 100, offsetX: 0, offsetY: 0}
    };

    let expected = [
      {
        ...Player.defaultPlayer,
        id: 1,
        filename: "sprites/egg-sprite-red.png",
        multiplier: 2,
        title: "It is of course the red egg",
        playerType: RedEgg,
        value: 2,
        frames: 18,
        coords: { x: 100, y: 100, offsetX: 0, offsetY: 0}
      }
    ];
  
    let players = [player1, player2, player3];
  
    let collided = [(1, 2), (4, 6)];
  
    expect(EggCollisions.createNewPlayers(collided, players)) |> toEqual(expected);
  });
});

/*

















test("Combine player lists", () => {
  const player1 = new Player({
    id: 1,
    value: 10,
    coords: new Coords({
      x: 100,
      y: 100
    })
  });

  const player2 = new Player({
    id: 2,
    value: 5,
    coords: new Coords({
      x: 6,
      y: 6
    })
  });

  const player3 = new Player({
    id: 3,
    value: 5,
    coords: new Coords({
      x: 100,
      y: 100
    })
  });

  const list1 = [player1, player2];

  const list2 = fromJS([player3]);

  const expected = fromJS([player1, player2, player3]);

  const collisions = new Collisions();

  const actual = collisions.combinePlayerLists(list1, list2);

  expect(actual).toEqual(expected);
});

*/