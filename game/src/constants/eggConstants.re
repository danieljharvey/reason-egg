let screenSize = (640, 640);

let tileSize = 64;

type gameState =
  | Loading
  | Playing;

let gameSpeed: float = 40.0;

let rotateSpeed: float = 150.0;