open Reprocessing;
open EggTypes;

let convertColor = (tint: color) : JsTypes.fillColour => {
  {
    r: tint.r,
    g: tint.g,
    b: tint.b,
    a: tint.a
  };
};

let loadImage = (env, filename: string) : JsTypes.imageAsset => (
  filename,
  Draw.loadImage(~filename="assets/" ++ filename, ~isPixel=true, env)
);