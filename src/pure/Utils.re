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

/*import * as _ from "ramda";
import { Board } from "../objects/Board";
import { BoardSize } from "../objects/BoardSize";
import { Coords } from "../objects/Coords";
import { GameState } from "../objects/GameState";
import { Player } from "../objects/Player";
import { Tile } from '../objects/Tile'

import { IPlayerType, playerTypes as allPlayerTypes } from "../data/PlayerTypes"

import { maybe, Maybe } from 'tsmonad'

// wee lad full of reusable functions

const imagesFolder: string = "img/";
const defaultMoveSpeed = 10

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

  // check leftovers on board and whether player is over finish tile
  public static checkLevelIsCompleted(gameState: GameState): boolean {
    const collectable = Utils.countCollectable(gameState.board);
    const playerCount: number = Utils.countPlayers(gameState.players);
    return collectable < 1 && playerCount < 2;
  }

  public static countPlayers(players: Player[]): number {
    const validPlayers = players.filter(player => {
      return player && player.value > 0;
    });
    return validPlayers.length;
  }

  // get total outstanding points left to grab on board
  public static countCollectable(board: Board): number {
    const tiles = board.getAllTiles();
    return tiles.reduce((collectable, tile) => {
      const score = tile.collectable;
      if (score > 0) {
        return collectable + score;
      }
      return collectable;
    }, 0);
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
