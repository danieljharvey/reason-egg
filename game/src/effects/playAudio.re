open Reprocessing_Env;

open JsTypes;
open AudioTriggers;

let loadAudioFile = (env, filename: string): audioAsset => {
    (filename, loadSound("assets/" ++ filename, env));
};

let playAudioFile = (env, audioAsset: audioAsset) => {
    let audio = snd(audioAsset);
    playSound(audio, ~loop=false, ~volume=1.0, env);
};

let loadAudioFiles = (audioSamples: list(audioSample), env): list(audioAsset) => 
    List.map(filename, audioSamples)
    |> List.map(loadAudioFile(env));

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
