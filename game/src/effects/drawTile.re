open EggTypes;
open JsTypes;

let loadTileImages = (tiles: list(tile), env) =>
  List.map((tile: tile) => RenderUtils.loadImage(env, tile.filename), tiles);

let getTileImageByID =
    (tileImages: list(imageAsset), filename: string)
    : option(imageAsset) =>
  Utils.find(
    tileImage =>
      switch tileImage {
      | (imgName, _) => imgName === filename
      },
    tileImages
  );
