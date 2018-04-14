open EggTypes;

type combination = (int, int);

let chooseHigherLevelPlayer = (player1: player, player2: player): player => {
  if (player1.value > player2.value) {
    player1;
  } else if (player2.value > player1.value) {
    player2;
  } else {
    player1;
  };
};

let fetchPlayerByID = (players: list(player), id: int): option(player) => {
  Utils.find((player: player) => player.id === id, players);
};

let combinePlayers = (player1: player, player2: player): list(player) => {
  let newValue = player1.value + player2.value;
  let higherPlayer = chooseHigherLevelPlayer(player1, player2);
  let maybePlayerType = Player.getPlayerTypeByValue(newValue);
  switch (maybePlayerType) {
    | Some(newPlayerType) => {
      let newPlayer = {
        ...newPlayerType,
        id: player1.id,
        coords: higherPlayer.coords,
        direction: higherPlayer.direction
      };
      [newPlayer];
    }
    | _ => [player1, player2];
  };
};

let createNewPlayers = (collided: list(combination), players: list(player)): list(player) => {
  List.fold_right((collidedIDs: combination, newPlayers: list(player)) => {
    let player1 = fetchPlayerByID(players, fst(collidedIDs));
    let player2 = fetchPlayerByID(players, snd(collidedIDs));
    switch (player1) {
      | Some (one) => switch (player2) {
        | Some (two) => {
          List.concat([newPlayers, combinePlayers(one, two)]);
        }
        | _ => newPlayers
      }
      | _ => newPlayers
    };
  }, collided, []);
};

let playerIsInList = (list: list(int), player: player): bool => {
  let match = Utils.find(id => player.id === id, list);
  Utils.isNone(match);
};

let removeCollidedPlayers = (
  collided: list(combination),
  players: list(player)
): list(player) => {
  let collidedIDs = List.flatten(
    List.map(Utils.tupleToList, collided)
  );
  let uniqueIDs = Utils.removeDuplicates(collidedIDs);
  List.filter(playerIsInList(collidedIDs), players);
};

let isSamePlayer = (player1: player, player2: player): bool => (player1.id === player2.id);

let isNotEgg = (player1: player, player2: player): bool => (player1.value === 0 || player2.value === 0);

let hasJustSplit = (player1: player, player2: player): bool => (player1.lastAction === "split" || player2.lastAction === "split");

let isDifferentRow = (player1: player, player2: player): bool => (player1.coords.y !== player2.coords.y);

let calcDistance = (player1: player, player2: player): int => {
  let position1 = Board.getActualPosition(player1.coords);
  let position2 = Board.getActualPosition(player2.coords); 
  let distance = position1.x - position2.x;
  (distance < 0) ? distance * -1 : distance;
};

let isCloseEnough = (player1: player, player2: player): bool => {
  (calcDistance(player1, player2) <= 20);
};

/* only deal with horizontal collisions for now */
let checkCollision = (player1: player, player2: player): bool => {
  if (
    isSamePlayer(player1, player2) ||
    isNotEgg(player1, player2) ||
    hasJustSplit(player1, player2) || 
    isDifferentRow(player1, player2)
    ) {
    false;
  } else {
    isCloseEnough(player1, player2);
  };
};

let optCheckCollision = (player1: option(player), player2: option(player)): bool => {
  switch (player1) {
  | Some (one) => switch (player2) {
    | Some (two) => checkCollision(one, two)
    | _ => false
  }
  | _ => false
  };
};

/* send an array of pairs of player ids, returns all that collide */
let findCollisions = (
  combinations: list(combination),
  players: list(player)
): list(combination) => {
  List.filter(comb => {
    let player1 = fetchPlayerByID(players, fst(comb));
    let player2 = fetchPlayerByID(players, snd(comb));
    optCheckCollision(player1, player2);
  }, combinations);
};

let isOtherPlayer = (player: player, otherPlayer: player) : bool => player.id < otherPlayer.id;

let playerCombineFold = (players: list(player), player: player, total: list(combination)) => {
  let otherPlayers = List.filter(isOtherPlayer(player), players);
  let combos = List.map(otherPlayer => {
    (player.id, otherPlayer.id);
  }, otherPlayers);
  List.append(total, combos);
};

let getAllPlayerCombinations = (players: list(player)): list(combination) => {
  List.fold_right(playerCombineFold(players), players, []);
};

let checkAllCollisions = (players: list(player)): list(player) => {
  let combinations = getAllPlayerCombinations(players);
  
  let collided = findCollisions(combinations, players);

  let oldPlayers = removeCollidedPlayers(collided, players);

  let newPlayers = createNewPlayers(collided, players);

  List.concat([oldPlayers, newPlayers]);
};

let checkAll = (gameState: gameState): gameState => {
  ...gameState,
  players: checkAllCollisions(gameState.players)
};