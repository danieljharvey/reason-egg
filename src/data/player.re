open EggTypes;

let defaultCoords: coords = {x: 0, y: 0, offsetX: 0, offsetY: 0};

let defaultPlayer: player = {
  coords: defaultCoords,
  direction: defaultCoords,
  oldDirection: defaultCoords,
  currentFrame: 0,
  id: 0,
  frames: 18,
  multiplier: 1,
  falling: false,
  playerType: Nope,
  moveSpeed: 10,
  fallSpeed: 10,
  value: 1,
  filename: "",
  stop: false,
  lastAction: "",
  title: "",
  moved: false,
  flying: false,
  movePattern: Normal
};

let loadPlayerImages = (players: list(player), env) =>
  List.map(
    (player: player) => EggUtils.loadImage(env, player.filename),
    players
  );

let playerTypes: list(player) = [
  {
    ...defaultPlayer,
    frames: 18,
    filename: "sprites/egg-sprite-blue.png",
    multiplier: 5,
    title: "It is of course the blue egg",
    playerType: BlueEgg,
    value: 3
  },
  {
    ...defaultPlayer,
    frames: 18,
    filename: "sprites/egg-sprite.png",
    multiplier: 1,
    title: "It is of course the egg",
    playerType: Egg,
    value: 1
  },
  {
    ...defaultPlayer,
    frames: 18,
    filename: "sprites/egg-sprite-red.png",
    multiplier: 2,
    title: "It is of course the red egg",
    playerType: RedEgg,
    value: 2
  },
  {
    ...defaultPlayer,
    fallSpeed: 20,
    frames: 1,
    filename: "sprites/silver-egg.png",
    moveSpeed: 0,
    multiplier: 10,
    title: "It is of course the silver egg",
    playerType: SilverEgg,
    value: 0
  },
  {
    ...defaultPlayer,
    frames: 18,
    filename: "sprites/egg-sprite-yellow.png",
    multiplier: 10,
    title: "It is of course the yellow egg",
    playerType: YellowEgg,
    value: 4
  },
  {
    ...defaultPlayer,
    frames: 18,
    filename: "sprites/egg-rainbow.png",
    multiplier: 1,
    title: "It goes without saying that this is the rainbow egg",
    playerType: RainbowEgg,
    value: 1
  },
  {
    ...defaultPlayer,
    frames: 18,
    filename: "sprites/blade-sprite.png",
    title: "It is the mean spirited blade",
    playerType: Blade,
    value: 0,
    flying: true
  },
  {
    ...defaultPlayer,
    frames: 18,
    filename: "sprites/find-blade-sprite.png",
    title: "It is the mean spirited blade",
    playerType: FindBlade,
    value: 0,
    movePattern: SeekEgg,
    flying: true
  }
];

let getPlayerByType = (playerType: playerType) => EggUtils.find((player: player) => player.playerType === playerType, playerTypes);