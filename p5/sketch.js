let vid;
let pg;

let materialOffset = 0;
let speed = -1;

// tramo donde el cuerpo se deforma
let x1 = 1000;
let x2 = 3700;

// intensidad de deformación fija
let stretchAmount = 1;

function setup() {
  createCanvas(4000, 500);

  pg = createGraphics(2000, 1000);

  vid = createVideo("convey-me-nude-mask-white-background.mp4", videoLoaded);
  vid.hide();

  vid.volume(0);
  vid.elt.muted = true;
  vid.elt.playsInline = true;
}

function videoLoaded() {
  console.log("VIDEO LOADED");
  vid.loop();
}

function draw() {
  background(255);

  if (!vid || vid.width === 0 || vid.height === 0) {
    fill(0);
    textSize(24);
    text("loading video...", 30, 40);
    return;
  }

  pg.background(255);
  pg.image(vid, 0, 0, pg.width, pg.height);

  materialOffset += speed;

  drawElasticBelt();
}

function getStretchFactor() {
  return 1 + pow(stretchAmount, 2) * 20;
}

function drawElasticBelt() {
  let span = x2 - x1;
  let stretchFactor = getStretchFactor();
  let realSpan = span / stretchFactor;
  let extra = span - realSpan;

  for (let x = 0; x < width; x++) {
    let u;

    if (x < x1) {
      u = x + extra;
    } else if (x <= x2) {
      let local = x2 - x;
      let t = local / span;
      u = x2 - t * realSpan;
    } else {
      u = x;
    }

    u = floor(u);

    let texX = floor((u - materialOffset) % pg.width);
    if (texX < 0) texX += pg.width;

    copy(pg, texX, 0, 1, pg.height, x, 0, 1, height);
  }
}

function mousePressed() {
  vid.loop();
}