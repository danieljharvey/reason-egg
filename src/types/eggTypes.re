open EggConstants;

type imageAsset = (string, Reprocessing_Types.Types.imageT);

type coords = {
  x: int,
  y: int,
  offsetX: int,
  offsetY: int
};

type tileAction = NoAction | Teleport | CompleteLevel | PinkSwitch | GreenSwitch | SplitEggs | Collectable(int);

type playerType = Nope | Egg | RedEgg | BlueEgg | YellowEgg | SilverEgg | RainbowEgg | Blade | FindBlade;

type gameAction = Playing | Paused | TurnLeft | TurnRight | RotatingLeft(float) | RotatingRight(float);

type tile = {
  id: int,
  title: string,
  filename: string,
  background: bool,
  breakable: bool,
  action: tileAction,
  createPlayer: playerType,
  render: bool,
  x: int,
  y: int
};

type board = list(list(tile));

type movePattern = Normal | SeekEgg;

type player = {
  coords,
  direction: coords,
  oldDirection: coords,
  currentFrame: int,
  id: int,
  frames: int,
  multiplier: int,
  falling: bool,
  playerType,
  moveSpeed: int,
  fallSpeed: int,
  value: int,
  filename: string,
  stop: bool,
  lastAction: string,
  title: string,
  moved: bool,
  flying: bool,
  movePattern
};

type gameState = {
  players: list(player),
  board: board,
  score: int,
  rotations: (int,int),
  drawAngle: float,
  outcome: string,
  boardAngle: float,
  gameAction
};

type gameStuff = {
  playerImages: list(imageAsset),
  tileImages: list(imageAsset),
  boardAngle: float,
  lastAngleChange: float,
  gameState: gameState,
};

