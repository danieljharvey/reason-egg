open Reprocessing;

let loadImage = (env, filename: string) : JsTypes.imageAsset => (
  filename,
  Draw.loadImage(~filename="assets/" ++ filename, ~isPixel=true, env)
);