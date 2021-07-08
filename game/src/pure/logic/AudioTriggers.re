open EggTypes;

type audioTrigger = {
  name: string,
  pan: float
};

type compare('a) = {
  oldValue: 'a,
  newValue: 'a
};

type compareTiles = {
  oldTile: tile,
  newTile: tile
};

type comparePlayers = {
  oldPlayer: player,
  newPlayer: player
};

type sample = Bounce | Bell | CrateSmash | Pop | PowerUp | SoftBell | Switch | Thud | Warp | Woo;

type audioSample = {
  filename: string,
  sample
};

let audioSamples = [
  {
    sample: Bounce,
    filename: "audio/bounce.wav"
  },
  {
    sample: Bell, 
    filename: "audio/bright-bell.wav"
  },
  {
    sample: CrateSmash,
    filename: "audio/crate-smash.wav"
  },
  {
    sample: Pop,
    filename: "audio/pop.wav"
  },
  {
    sample: PowerUp,
    filename: "audio/power-up.wav"
  },
  {
    sample: SoftBell,
    filename: "audio/soft-bell.wav"
  },
  {
    sample: Switch,
    filename: "audio/switch.wav"
  },
  {
    sample: Thud,
    filename: "audio/thud.wav"
  },
  {
    sample: Warp,
    filename: "audio/warp.wav"
  },
  {
    sample: Woo,
    filename: "audio/woo.wav"
  }
];

let filename = (audioSample: audioSample): string => audioSample.filename;

let getFilenameForSample = (sample: sample): option(string) => 
  Utils.find(
    audioSample => audioSample.sample === sample,
    audioSamples
  ) |> Utils.optionMap(filename);

let triggerSounds = (oldState: gameState, newState: gameState): list(audioTrigger) => {
  /*const nearlyDoneSounds = [nearlyDone(oldState)(newState)];
  const eatenSounds = getEatenSounds(oldState)(newState);
  const playerSounds = getPlayerSounds(oldState)(newState);
  return [...nearlyDoneSounds, ...eatenSounds, ...playerSounds].filter(
    isItNothing
  );*/
  [];
};

/*
const isItNothing = (maybe: Maybe<any>): boolean => {
  return maybe.caseOf({
    just: () => true,
    nothing: () => false
  });
};

const hasRotated = (oldGame: GameState, newGame: GameState): boolean =>
  oldGame.rotateAngle === newGame.rotateAngle;

const getEatenSounds = (oldState: GameState) => (
  newState: GameState
): Array<Maybe<IAudioTrigger>> => {
  if (hasRotated(oldState, newState)) {
    return findEatenThings(oldState.board)(newState.board);
  } else {
    return [rotateSound()];
  }
};

const rotateSound = (): Maybe<IAudioTrigger> => {
  return Maybe.just({
    name: "warp",
    pan: 0
  });
};

// diffs board changes and outputs list of sounds to play
export const findEatenThings = (oldBoard: Board) => (
  board: Board
): Array<Maybe<IAudioTrigger>> => {
  const boardSize = board.getLength();

  const oldTiles = oldBoard.getAllTiles();
  const newTiles = board.getAllTiles();

  const tiles: ICompareTiles[] = getListDiff(oldTiles)(newTiles).filter(
    filterUnchanged
  );
  const coinSounds = tiles.map(gotCoins(boardSize));
  const crateSounds = tiles.map(crateSmash(boardSize));
  const doorSounds = justOne(tiles.map(doorChange(boardSize)));
  return [...coinSounds, ...crateSounds, ...doorSounds];
};

const justOne = (arr: any[]): any[] => {
  const first = _.find(item => item !== undefined, arr);
  if (first) {
    return [first];
  }
  return [];
};

const filterUnchanged = (tiles: ICompare) =>
  _.not(megaEquals(tiles.new, tiles.old));

const megaEquals = (x, y): boolean => {
  if (typeof x.equals !== "undefined") {
    return x.equals(y);
  }
  return x === y;
};

const getListDiff = (oldList: List<any>) => (newList: List<any>): any[] =>
  oldList
    .zipWith((oldItem: any, newItem: any) => {
      return {
        old: oldItem,
        new: newItem
      };
    }, newList)
    .toJS();

const getArrayDiff = (oldArray: any[]) => (newArray: any[]): any[] =>
  _.zipWith(
    (oldItem: any, newItem: any) => {
      return {
        old: oldItem,
        new: newItem
      };
    },
    oldArray,
    newArray
  );

const filterGotCoins = (tiles: ICompareTiles): boolean => {
  return tiles.old.collectable > tiles.new.collectable;
};

export const gotCoins = (boardSize: number) => (
  tiles: ICompareTiles
): Maybe<IAudioTrigger> => {
  return filterGotCoins(tiles)
    ? Maybe.just({
        name: "pop",
        pan: calcPan(boardSize)(tiles.new.x)
      })
    : Maybe.nothing();
};

const filterCrateSmash = (tiles: ICompareTiles): boolean => {
  return tiles.old.breakable === true && tiles.new.breakable === false;
};

export const crateSmash = (boardSize: number) => (
  tiles: ICompareTiles
): Maybe<IAudioTrigger> => {
  return filterCrateSmash(tiles)
    ? Maybe.just({
        name: "crate-smash",
        pan: calcPan(boardSize)(tiles.new.x)
      })
    : Maybe.nothing();
};

const filterDoorChange = (tiles: ICompareTiles): boolean => {
  return (
    (tiles.old.background === true &&
      tiles.old.frontLayer === true &&
      tiles.new.background === false) ||
    (tiles.new.background === true &&
      tiles.new.frontLayer === true &&
      tiles.old.background === false)
  );
};

export const doorChange = (boardSize: number) => (
  tiles: ICompareTiles
): Maybe<IAudioTrigger> => {
  return filterDoorChange(tiles)
    ? Maybe.just({
        name: "switch",
        pan: calcPan(boardSize)(tiles.new.x)
      })
    : Maybe.nothing();
};

export const getPlayerSounds = (oldState: GameState) => (
  newState: GameState
) => {
  const boardSize = newState.board.getLength();

  const combine = [playersCombine(oldState.players)(newState.players)];

  const players: IComparePlayers[] = getArrayDiff(oldState.players)(
    newState.players
  ).filter(filterUnchanged);
  const thuds = players.map(playerHitsFloor(boardSize));
  const teleports = players.map(playerTeleported(boardSize));
  const bounces = players.map(playerHitsWall(boardSize));
  return [...combine, ...thuds, ...teleports, ...bounces];
};

const filterPlayerHitsFloor = (players: IComparePlayers): boolean => {
  return players.old.falling === true && players.new.falling === false;
};

export const playerHitsFloor = (boardSize: number) => (
  players: IComparePlayers
): Maybe<IAudioTrigger> => {
  return filterPlayerHitsFloor(players)
    ? Maybe.just({
        name: "thud",
        pan: calcPan(boardSize)(players.new.coords.x)
      })
    : Maybe.nothing();
};

const filterPlayerHitsWall = (players: IComparePlayers): boolean => {
  return (
    players.old.falling === false &&
    players.new.falling === false &&
    players.new.flying === false &&
    players.old.direction.x !== players.new.direction.x
  );
};

export const playerHitsWall = (boardSize: number) => (
  players: IComparePlayers
): Maybe<IAudioTrigger> => {
  return filterPlayerHitsWall(players)
    ? Maybe.just({
        name: "bounce",
        pan: calcPan(boardSize)(players.new.coords.x)
      })
    : Maybe.nothing();
};

const filterTeleported = (players: IComparePlayers): boolean => {
  return players.old.lastAction === "" && players.new.lastAction === "teleport";
};

export const playerTeleported = (boardSize: number) => (
  players: IComparePlayers
): Maybe<IAudioTrigger> => {
  return filterTeleported(players)
    ? Maybe.just({
        name: "soft-bell",
        pan: calcPan(boardSize)(players.new.coords.x)
      })
    : Maybe.nothing();
};

const filterPlayersCombine = (oldPlayers: Player[]) => (
  newPlayers: Player[]
): boolean => {
  return oldPlayers.length > newPlayers.length;
};

const playersCombine = (oldPlayers: Player[]) => (
  newPlayers: Player[]
): Maybe<IAudioTrigger> => {
  return filterPlayersCombine(oldPlayers)(newPlayers)
    ? Maybe.just({
        name: "power-up",
        pan: 0
      })
    : Maybe.nothing();
};

// super basic for now
const calcPan = (boardSize: number) => (x: number): number => {
  if (boardSize < 2) {
    return 0;
  }
  const ratio = x / (boardSize - 1);
  const ans = ratio * 2 - 1;
  return ans;
};

const filterNearlyDone = (oldState: GameState) => (
  newState: GameState
): boolean => {
  return (
    Utils.checkLevelIsCompleted(oldState) === false &&
    Utils.checkLevelIsCompleted(newState) === true
  );
};

const nearlyDone = (oldState: GameState) => (
  newState: GameState
): Maybe<IAudioTrigger> => {
  return filterNearlyDone(oldState)(newState)
    ? Maybe.just({
        name: "woo",
        pan: 0
      })
    : Maybe.nothing();
};

*/