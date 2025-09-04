import GameModule from "./${PROJECT}.js";

GameModule({
  canvas: (function () {
    const canvas = document.querySelector("canvas");
    // Do some canvas setup

    return canvas;
  })(),
})
.then(Module => {
  // Do something with the Module
});
