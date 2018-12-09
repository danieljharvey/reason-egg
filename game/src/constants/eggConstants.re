let screenSize = (640, 640);

let tileSize = 64;

type gameState =
  | Loading
  | Playing;

let gameSpeed: float = 60.0;

let rotateSpeed: float = 200.0;