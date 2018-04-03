open EggTypes;

let defaultCoords: coords = {x: 0, y: 0};

let createPlayer =
    (
      ~coords=defaultCoords,
      ~direction=defaultCoords,
      ~oldDirection=defaultCoords,
      ~currentFrame=0,
      ~id=0,
      ~frames=18,
      ~multiplier=1,
      ~falling=false,
      ~playerType="",
      ~moveSpeed=1,
      ~fallSpeed=1,
      ~value=1,
      ~filename="",
      ~stop=false,
      ~lastAction="",
      ~title="",
      ~moved=false,
      ~flying=false,
      ~movePattern="",
      ()
    )
    : player => {
  coords,
  direction,
  oldDirection,
  currentFrame,
  id,
  frames,
  multiplier,
  falling,
  playerType,
  moveSpeed,
  fallSpeed,
  value,
  filename,
  stop,
  lastAction,
  title,
  moved,
  flying,
  movePattern
};

let players: list(player) = [
  createPlayer(~filename="sprites/egg-rainbow.png", ~coords={x: 2, y: 2}, ()),
  createPlayer(~filename="sprites/egg-rainbow.png", ~coords={x: 4, y: 4}, ()),
  createPlayer(~filename="sprites/egg-rainbow.png", ~coords={x: 6, y: 6}, ())
];

let loadPlayerImages = (players: list(player), env) =>
  List.map(
    (player: player) => EggUtils.loadImage(env, player.filename),
    players
  );