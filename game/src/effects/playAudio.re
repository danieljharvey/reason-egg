open Reprocessing_Env;

open JsTypes;

let audio = [
    "audio/bounce.wav",
    "audio/bright-bell.wav",
    "audio/crate-smash.wav",
    "audio/pop.wav",
    "audio/power-up.wav",
    "audio/soft-bell.wav",
    "audio/switch.wav",
    "audio/thud.wav",
    "audio/warp.wav",
    "audio/woo.wav"
];

let loadAudioFile = (env, filename: string): audioAsset => {
    (filename, loadSound("assets/" ++ filename, env));
};

let playAudioFile = (env, audioAsset: audioAsset) => {
    let audio = snd(audioAsset);
    playSound(audio, env);
};

let loadAudioFiles = (filenames: list(string), env): list(audioAsset) => List.map(loadAudioFile(env), filenames);

let getAudioAssetByID =
    (audioAssets: list(audioAsset), filename: string)
    : option(audioAsset) =>
  Utils.find(
    audioAsset =>
      switch audioAsset {
      | (audioFilename, _) => audioFilename === filename
      },
    audioAssets
  );

let playAudioAssetByID = (env, audioAssets: list(audioAsset), filename: string) => {
    switch (getAudioAssetByID(audioAssets, filename)) {
    | Some(audioAsset) => playAudioFile(env, audioAsset)
    | _ => ()
    };
};
