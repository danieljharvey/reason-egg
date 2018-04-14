open EggTypes;

let correctForOverflow = (
    coords: coords,
    boardSize: int
  ): coords => {
    
  let newX = if (coords.x < 0) {
    boardSize - 1;
  } else if (coords.x >= boardSize) {
    0;
  } else {
    coords.x;
  };

  let newY = if (coords.y < 0) {
    boardSize - 1;
  } else if (coords.y >= boardSize) {
    0;
  } else {
    coords.y;
  };
  { ...coords, x: newX, y: newY };
};

let tupleToList = (tuple: ('a, 'a)) : list('a) => {
  [fst(tuple), snd(tuple)];
};

let removeElt = (e, l) => {
  let rec go = (l, acc) =>
    switch l {
    | [] => List.rev(acc)
    | [x, ...xs] when e == x => go(xs, acc)
    | [x, ...xs] => go(xs, [x, ...acc])
    };
  go(l, []);
};

let removeDuplicates = (l) => {
  let rec go = (l, acc) =>
    switch l {
    | [] => List.rev(acc)
    | [x, ...xs] => go(removeElt(x, xs), [x, ...acc])
    };
  go(l, []);
};

let optionMap = (f, option: option('a)) =>
  switch option {
  | Some(x) => Some(f(x))
  | _ => None
  };

let find = (f, list) => {
  let found = List.filter(f, list);
  List.length(found) === 0 ? None : Some(List.hd(found));
};

let randomFromList = (list: list('a)) : 'a => 
  List.nth(list, Random.int(List.length(list)));

let degreesToRadians = (degrees: float) : float =>
  degrees /. 360.0 *. (pi *. 2.0);

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




/* 
export class Utils {
  public static getRandomObjectKey(object: object) {
    const keys = Object.keys(object);
    return this.returnRandomKey(keys);
  }

  public static getRandomArrayKey(array: object[]) {
    const keys = _.keys(array);
    return this.returnRandomKey(keys);
  }

  public static returnRandomKey(keys: any[]) {
    if (keys.length === 0) {
      return false;
    }
    return keys[(keys.length * Math.random()) << 0];
  }

  public static getControlStyle(id: string, property: string) {
    const controlHeader = document.getElementById(id);
    if (!controlHeader) {
      return 0;
    }
    const style = window.getComputedStyle(controlHeader);
    const value = style[property];
    if (isNaN(value)) {
      return parseInt(value, 10);
    }
    return value;
  }

  public static getControlProperty(id: string, property: string) {
    const controlHeader = document.getElementById(id);
    if (!controlHeader) {
      return 0;
    }
    const value = controlHeader[property];
    if (isNaN(value)) {
      return parseInt(value, 10);
    }
    return value;
  }

  public static removeParams(params: object, removeList: string[]) {
    const goodParams = {};
    for (const i in params) {
      if (removeList.indexOf(i) === -1) {
        goodParams[i] = params[i];
      }
    }
    return goodParams;
  }

  

 

  

  // todo : a Maybe?
  public static getPlayerByValue(playerTypes, value: number) {
    for (const i in playerTypes) {
      if (playerTypes[i].value === value) {
        return playerTypes[i];
      }
    }
    return false;
  }

  public static getPlayerByType(playerTypes: Player[], type: string): (Player | undefined) {
    return playerTypes.find(playerType =>
      (playerType.type === type)
    )
  }



  public static getTileImagePath(img: string): string {
    return imagesFolder + img
  }

  public static moveSpeed (playerMoveSpeed: number): number {
    return (playerMoveSpeed === undefined || playerMoveSpeed === 1) ? defaultMoveSpeed : playerMoveSpeed
  }

  public static fallSpeed  (playerFallSpeed: number): number {
    return (playerFallSpeed === undefined || playerFallSpeed === 1) ? defaultMoveSpeed * 1.5 : playerFallSpeed
  }
    
  public static getPlayerType = (type: string): Maybe<IPlayerType> => {
    return maybe(allPlayerTypes.find(playerType => 
      playerType.type === type
    ))
  }

}*/
