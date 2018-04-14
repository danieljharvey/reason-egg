type imageAsset = (string, Reprocessing_Types.Types.imageT);

type fillColour = Reprocessing_Types.Types.colorT;

type coords = {
  x: int,
  y: int,
  offsetX: int,
  offsetY: int
};

type tileAction = NoAction | Teleport | ClosedDoor | CompleteLevel | PinkSwitch | GreenSwitch | SplitEggs | Collectable(int);

type playerType = Nope | Egg | RedEgg | BlueEgg | YellowEgg | SilverEgg | RainbowEgg | Blade | FindBlade;

type gameAction = Playing | Paused | TurnLeft | TurnRight | RotatingLeft(float) | RotatingRight(float);

type visualMode = Standard | MegaVibes;

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
  y: int,
  frames: int,
  currentFrame: int,
  cycleSpeed: int
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
  movePattern,
  size: float
};

type gameState = {
  players: list(player),
  board: board,
  score: int,
  rotations: (int,int),
  drawAngle: float,
  outcome: string,
  boardAngle: float,
  currentFrame: int,
  gameAction,
  visualMode
};

type gameStuff = {
  playerImages: list(imageAsset),
  tileImages: list(imageAsset),
  boardAngle: float,
  lastAngleChange: float,
  gameState: gameState,
};

