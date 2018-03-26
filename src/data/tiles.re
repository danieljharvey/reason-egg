open EggTypes;

let createTile =
    (
      ~action="",
      ~background=false,
      ~breakable=false,
      ~collectable=0,
      ~createPlayer="",
      ~dontAdd=false,
      ~frontLayer=false,
      ~id=0,
      ~filename="",
      ~title="",
      ~x=0,
      ~y=0,
      ()
    ): EggTypes.tile => {
  id,
  title,
  filename,
  background,
  frontLayer,
  collectable,
  breakable,
  action,
  dontAdd,
  createPlayer,
  x,
  y
};

let tiles: list(EggTypes.tile) = [
  createTile(~background=true, ~id=1, ~filename="tiles/sky.png", ~title="Sky", ()),
  createTile(
    ~background=false,
    ~id=2,
    ~filename="tiles/fabric.png",
    ~title="Fabric",
    ()
  ),
  createTile(
    ~background=true,
    ~collectable=1,
    ~frontLayer=true,
    ~id=3,
    ~filename="tiles/cacti.png",
    ~title="Cacti",
    ()
  ),
  createTile(
    ~background=true,
    ~collectable=10,
    ~frontLayer=true,
    ~id=4,
    ~filename="tiles/plant.png",
    ~title="Plant",
    ()
  ),
  createTile(
    ~background=false,
    ~breakable=true,
    ~id=5,
    ~filename="tiles/crate.png",
    ~title="Crate",
    ()
  ),
  createTile(
    ~background=false,
    ~id=8,
    ~filename="tiles/work-surface-2.png",
    ~title="Work surface 2",
    ()
  ),
  createTile(
    ~background=false,
    ~id=9,
    ~filename="tiles/work-surface-3.png",
    ~title="Work surface 3",
    ()
  ),
  createTile(
    ~background=false,
    ~id=10,
    ~filename="tiles/work-surface-4.png",
    ~title="Work surface 4",
    ()
  ),
  createTile(
    ~background=false,
    ~id=11,
    ~filename="tiles/tile.png",
    ~title="Tiles",
    ()
  ),
  createTile(
    ~action="completeLevel",
    ~background=true,
    ~createPlayer="egg",
    ~frontLayer=true,
    ~id=12,
    ~filename="tiles/egg-cup.png",
    ~title="Egg Cup",
    ()
  )
];

let getTileByID = id => EggUtils.find(tile => tile.id === id, tiles);

let loadTileImages = env =>
  List.map(tile => EggUtils.loadImage(env, tile.filename), tiles);

let getTileImageByID =
    (tileImages: list(imageAsset), filename: string)
    : option(imageAsset) =>
  EggUtils.find(
    tileImage =>
      switch tileImage {
      | (imgName, _) => imgName === filename
      | (_, _) => false
      },
    tileImages
  );
/*


   {
     action: "completeLevel",
     background: true,
     createPlayer: "egg",
     frontLayer: true,
     id: 12,
     img: "egg-cup.png",
     title: "Egg Cup"
   },
   {
     background: true,
     collectable: 100,
     dontAdd: true,
     frontLayer: true,
     id: 13,
     img: "toast.png",
     title: "Toast"
   },
   {
     action: "teleport",
     background: true,
     frontLayer: true,
     id: 14,
     img: "door.png",
     title: "Door"
   },
   {
     background: true,
     frontLayer: true,
     id: 15,
     img: "pink-door-open.png",
     title: "Pink door open"
   },
   {background: false, id: 16, img: "pink-door.png", title: "Pink door closed"},
   {
     action: "pink-switch",
     background: true,
     frontLayer: true,
     id: 17,
     img: "pink-switch.png",
     title: "Pink door switch"
   },
   {
     background: true,
     frontLayer: true,
     id: 18,
     img: "green-door-open.png",
     title: "Green door open"
   },
   {
     background: false,
     id: 19,
     img: "green-door.png",
     title: "Green door closed"
   },
   {
     action: "green-switch",
     background: true,
     frontLayer: true,
     id: 20,
     img: "green-switch.png",
     title: "Green door switch"
   },
   {
     background: true,
     createPlayer: "silver-egg",
     frontLayer: true,
     id: 21,
     img: "silver-egg-cup.png",
     title: "Silver Egg Cup"
   },
   {
     background: true,
     createPlayer: "blade",
     frontLayer: true,
     id: 22,
     img: "blade-egg-cup.png",
     title: "Blade egg cup"
   },
   {
     background: true,
     createPlayer: "find-blade",
     frontLayer: true,
     id: 23,
     img: "find-blade-egg-cup.png",
     title: "Find-blade egg cup"
   },
   {
     background: true,
     id: 24,
     action: "split-eggs",
     frontLayer: true,
     img: "egg-splitter.png",
     title: "It is the egg splitter"
   }
 ];
 */
