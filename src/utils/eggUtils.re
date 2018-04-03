open Reprocessing;

let optionMap = (f, option: option('a)) =>
  switch option {
  | Some(x) => Some(f(x))
  | _ => None
  };

let find = (f, list) => {
  let found = List.filter(f, list);
  List.length(found) === 0 ? None : Some(List.hd(found));
};

let degreesToRadians = (degrees: float) : float =>
  degrees /. 360.0 *. Constants.two_pi;

let loadImage = (env, filename: string) : EggTypes.imageAsset => (
  filename,
  Draw.loadImage(~filename="assets/" ++ filename, ~isPixel=true, env)
);

let isNone = (item: option('a)): bool => 
  switch (item) {
    | None => true
    | _ => false
    };

/* need an id function even though it won't get used */
let sequence = (id: 'a, list: list(option('a))): option(list('a)) => {
  let nothings = List.filter(isNone, list);
  if (List.length(nothings) > 0) {
    None;
  } else {
    Some(
      List.map(item => switch item {
      | Some(thing) => thing
      | _ => id
      }, list)
    );
  };
};


