open EggConstants;

type imageAsset = (string, Reprocessing_Types.Types.imageT);

type coords = {
  x: int,
  y: int,
  offsetX: int,
  offsetY: int
};

type tile = {
  id: int,
  title: string,
  filename: string,
  background: bool,
  frontLayer: bool,
  collectable: int,
  breakable: bool,
  action: string,
  dontAdd: bool,
  createPlayer: string,
  x: int,
  y: int
};

type board = list(list(tile));

type player = {
  coords,
  direction: coords,
  oldDirection: coords,
  currentFrame: int,
  id: int,
  frames: int,
  multiplier: int,
  falling: bool,
  playerType: string,
  moveSpeed: int,
  fallSpeed: int,
  value: int,
  filename: string,
  stop: bool,
  lastAction: string,
  title: string,
  moved: bool,
  flying: bool,
  movePattern: string
};

type programState = Loading | Playing;

type gameState = {
  players: list(player),
  board: board,
  score: int,
  rotations: int,
  rotateAngle: float,
  outcome: string
};

type gameStuff = {
  playerImages: list(imageAsset),
  tileImages: list(imageAsset),
  boardAngle: float,
  drawAngle: float,
  gameState: gameState,
  programState
};

