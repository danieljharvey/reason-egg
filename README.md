# Reason Egg

### Port of hopeless game It Is The Egg to Reprocessing.

Play the original game here: http://itistheegg.com/

### Installation

```
cd game
git clone https://github.com/danieljharvey/reason-egg
cd reason-egg
yarn install
```

### Run in browser

```
cd game
yarn build:web:watch
```

Then open `index.html` in browser.

### Run in OCaml bytecode

```
cd game
yarn build
yarn start
```

### Compile to native code

```
cd game
yarn build:native
yarn start:native
```
