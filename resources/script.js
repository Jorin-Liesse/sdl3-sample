import GameModule from "./SGE.js";

GameModule({
  canvas: (function () {
    const canvas = document.querySelector("canvas");
    resizeCanvas(canvas);

    window.addEventListener("resize", () => {
      resizeCanvas(canvas);
    });

    // document.addEventListener("visibilitychange", () => {
    //   if (document.visibilityState === "visible") {
    //     window.pageVisibility = true;
    //   } else {
    //     window.pageVisibility = false;
    //     window.wasHidden = true;
    //   }
    // });
    // window.addEventListener("focus", () => {
    //   window.pageFocus = false;
    //   window.wasHidden = true;
    // });

    // window.addEventListener("blur", () => {
    //   window.pageFocus = false;
    //   window.wasHidden = true;
    // });
    return canvas;
  })(),
});
// .then(Module => {});

function resizeCanvas(canvas) {
  canvas.width = window.innerWidth;
  canvas.height = window.innerHeight;
}
