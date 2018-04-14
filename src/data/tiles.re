open EggTypes;

let idTile: tile = {
  action: NoAction,
  background: false,
  breakable: false,
  createPlayer: Nope,
  render: true,
  id: 0,
  filename: "",
  title: "",
  x:0,
  y:0,
  frames: 1,
  currentFrame: 0,
  cycleSpeed: 1
};

let tiles: list(EggTypes.tile) = [
  {
    ...idTile,
    background: true,
    id: 1,
    filename: "tiles/sky.png",
    render: false,
    title: "Sky"
  },
  {
    ...idTile,
    background: false,
    id: 2,
    filename: "tiles/fabric.png",
    title: "Fabric"
  },
  {
    ...idTile,
    background: true,
    action: Collectable(1),
    id: 3,
    filename: "tiles/cacti.png",
    title: "Cacti"
  },
  {
    ...idTile,
    background: true,
    action: Collectable(10),
    id: 4,
    filename: "tiles/plant.png",
    title: "Plant"
  },
  {
    ...idTile,
    background: false,
    breakable: true,
    id: 5,
    filename: "tiles/crate.png",
    title: "Crate"
  },
  {
    ...idTile,
    background: false,
    id: 8,
    filename: "tiles/work-surface-2.png",
    title: "Work surface 2"
  },
  {
    ...idTile,
    background: false,
    id: 9,
    filename: "tiles/work-surface-3.png",
    title: "Work surface 3"
  },
  {
    ...idTile,
    background: false,
    id: 10,
    filename: "tiles/work-surface-4.png",
    title: "Work surface 4"
  },
  {
    ...idTile,
    background: false,
    id: 11,
    filename: "tiles/tile.png",
    title: "Tiles"
  },
  {
    ...idTile,
    render: false,
    background: true,
    createPlayer: Egg,
    id: 12,
    filename: "tiles/egg-cup.png",
    title: "Egg Cup"
  },
  {
    ...idTile,
    background: true,
    action: Collectable(100),
    id: 13,
    filename: "tiles/toast.png",
    title: "Toast"
  },
  {
    ...idTile,
    action: Teleport,
    background: true,
    id: 14,
    filename: "tiles/teleport.png",
    title: "Door"
  },
  {
    ...idTile,
    background: true,
    id: 15,
    filename: "tiles/pink-door-open.png",
    title: "Pink door open"
  },
  {
    ...idTile,
    background: false,
    id: 16,
    filename: "tiles/pink-door.png",
    title: "Pink door closed"
  },
  {
    ...idTile,
    action: PinkSwitch,
    background: true,
    id: 17,
    filename: "tiles/pink-switch.png",
    title: "Pink door switch"
  },
  {
    ...idTile,
    background: true,
    id: 18,
    filename: "tiles/green-door-open.png",
    title: "Green door open"
  },
  {
    ...idTile,
    background: false,
    id: 19,
    filename: "tiles/green-door.png",
    title: "Green door closed"
  },
  {
    ...idTile,
    action: GreenSwitch,
    background: true,
    id: 20,
    filename: "tiles/green-switch.png",
    title: "Green door switch"
  },
  {
    ...idTile,
    background: true,
    createPlayer: SilverEgg,
    id: 21,
    filename: "tiles/silver-egg-cup.png",
    title: "Silver Egg Cup"
  },
  {
    ...idTile,
    background: true,
    createPlayer: Blade,
    id: 22,
    filename: "tiles/blade-egg-cup.png",
    title: "Blade egg cup"
  },
  {
    ...idTile,
    background: true,
    createPlayer: FindBlade,
    id: 23,
    filename: "tiles/find-blade-egg-cup.png",
    title: "Find-blade egg cup"
  },
  {
    ...idTile,
    background: true,
    id: 24,
    action: SplitEggs,
    filename: "tiles/egg-splitter.png",
    title: "It is the egg splitter"
  },
  {
    ...idTile,
    action: ClosedDoor,
    background: true,
    id: 25,
    filename: "tiles/door-closed.png",
    title: "Closed Door"
  },
  {
    ...idTile,
    action: CompleteLevel,
    background: true,
    id: 26,
    filename: "tiles/door-open.png",
    title: "Open Door",
    frames: 18,
    cycleSpeed: 10
  },
];

let blankTile = List.hd(tiles);

let getTileByID = (id: int) => EggUtils.find((tile: tile) => tile.id === id, tiles);

let loadTileImages = env =>
  List.map((tile: tile) => EggUtils.loadImage(env, tile.filename), tiles);

let getTileImageByID =
    (tileImages: list(imageAsset), filename: string)
    : option(imageAsset) =>
  EggUtils.find(
    tileImage =>
      switch tileImage {
      | (imgName, _) => imgName === filename
      },
    tileImages
  );
