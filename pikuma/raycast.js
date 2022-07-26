const TILE_SIZE = 64;
const MAP_NUM_ROWS = 11;
const MAP_NUM_COLS = 15;

const WINDOW_WIDTH = MAP_NUM_COLS * TILE_SIZE;
const WINDOW_HEIGHT = MAP_NUM_ROWS * TILE_SIZE;
const FOV_ANGLE = 60 * (Math.PI/180);
const WALL_STRIP_WIDTH = 1;
const RAY_NUMS = WINDOW_WIDTH / WALL_STRIP_WIDTH;

const RED = 1;
const GREEN = 2;
const BLUE = 3;

const MINIMAP_SCALE_FACTOR = 0.2;

class Map {
	constructor() {
		this.grid = [
			[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
			[1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1],
			[1, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 2, 0, 1],
			[1, 3, 3, 3, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 1],
			[1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 1],
			[1, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 1],
			[1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
			[1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
			[1, 3, 3, 3, 3, 3, 0, 0, 0, 2, 2, 2, 2, 0, 1],
			[1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
			[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
		];
	}
	hasWallsAt(x, y) {
		if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT) {
			return true;
		}
		var xIndex = Math.floor(x / TILE_SIZE);
		var yIndex = Math.floor(y / TILE_SIZE);
		return (this.grid[yIndex][xIndex] != 0);
	}
	render() {
		for (var i = 0; i < MAP_NUM_ROWS; i++) {
			for (var j = 0; j < MAP_NUM_COLS; j++) {
				var tileX = j * TILE_SIZE; 
				var tileY = i * TILE_SIZE;
				var tileColor = this.grid[i][j] != 0 ? "#222" : "#fff";
				stroke("#222"); // Its used to draw lines and borders around texts and shapes.
				fill(tileColor); // Its used to draw a color inside a shape.
				rect(
					MINIMAP_SCALE_FACTOR * tileX, 
					MINIMAP_SCALE_FACTOR * tileY, 
					MINIMAP_SCALE_FACTOR * TILE_SIZE, 
					MINIMAP_SCALE_FACTOR * TILE_SIZE); // Creates a path for a rectangle at (x, y) position and (width, height) area.
			}
		}
	}
}

class Player {
	constructor() {
		this.x = WINDOW_WIDTH / 2;
		this.y = WINDOW_HEIGHT / 2;
		this.radius = 3;
		this.moveDirection = 0;
		this.walkDirection = 0;
		this.rotationAngle = Math.PI / 2;
		this.movementSpeed = 4;
		this.rotationSpeed = 4 * (Math.PI / 180);
	}
	update() {
		this.rotationAngle += this.moveDirection * this.rotationSpeed;

		var moveStep = this.walkDirection * this.movementSpeed;
		var to_x = this.x + Math.cos(this.rotationAngle) * moveStep;
		var to_y = this.y + Math.sin(this.rotationAngle) * moveStep;

		if (!grid.hasWallsAt(to_x, to_y)) {
			this.x = to_x;
			this.y = to_y;
		}
	}
	render() {
		noStroke();
		fill("red");
		circle(
			MINIMAP_SCALE_FACTOR * this.x, 
			MINIMAP_SCALE_FACTOR * this.y, 
			MINIMAP_SCALE_FACTOR * this.radius);
		stroke("red");
	}
}

class Ray {
	constructor(rayAngle) {
		this.rayAngle = normalizeAngle(rayAngle);
		this.wallHitX = 0;
		this.wallHitY = 0;
		this.distance = 0;
		this.wasHitVertical = false;
		this.wallPaper;

		this.isRayFacingDown = this.rayAngle > 0 && this.rayAngle < Math.PI;
		this.isRayFacingUp = !this.isRayFacingDown;

		this.isRayFacingRight = this.rayAngle < 0.5 * Math.PI || this.rayAngle > 1.5 * Math.PI;
		this.isRayFacingLeft = !this.isRayFacingRight;
	}
	cast () {
		var xintercept, yintercept;
		var xstep, ystep;

		var foundHorzWallHit = false;
		var horizontalHitX = 0;
		var horizontalHitY = 0;

		yintercept = Math.floor(john.y / TILE_SIZE) * TILE_SIZE;
		yintercept += this.isRayFacingDown ? TILE_SIZE : 0;

		xintercept = john.x + (yintercept - john.y) / Math.tan(this.rayAngle);

		ystep = TILE_SIZE;
		ystep *= this.isRayFacingUp ? -1 : 1;

		xstep = TILE_SIZE / Math.tan(this.rayAngle);
		xstep *= (this.isRayFacingLeft && xstep > 0) ? -1 : 1;
		xstep *= (this.isRayFacingRight && xstep < 0) ? -1 : 1;

		var nextHorzTouchX = xintercept;
		var nextHorzTouchY = yintercept;

		while (nextHorzTouchX >= 0 && nextHorzTouchX <= WINDOW_WIDTH && nextHorzTouchY >= 0 && nextHorzTouchY <= WINDOW_HEIGHT) {
			if (grid.hasWallsAt(nextHorzTouchX, nextHorzTouchY - this.isRayFacingUp)) {
				foundHorzWallHit = true;
				horizontalHitX = nextHorzTouchX;
				horizontalHitY = nextHorzTouchY;
				break ;
			}
			else {
				nextHorzTouchX += xstep;
				nextHorzTouchY += ystep;
			}
		}

		let foundVertWallHit = false;
		let vertWallHitX = 0;
		let vertWallHitY = 0;

		xintercept = Math.floor(john.x / TILE_SIZE) * TILE_SIZE;
		xintercept += this.isRayFacingRight ? TILE_SIZE : 0;

		yintercept = john.y + (xintercept - john.x) * Math.tan(this.rayAngle);

		xstep = TILE_SIZE;
		xstep *= this.isRayFacingLeft ? -1 : 1;

		ystep = TILE_SIZE * Math.tan(this.rayAngle);
		ystep *= (this.isRayFacingUp && ystep > 0) ? -1 : 1;
		ystep *= (this.isRayFacingDown && ystep < 0) ? -1 : 1;

		let nextVertTouchX = xintercept;
		let nextVertTouchY = yintercept;

		while (nextVertTouchX >= 0 && nextVertTouchX <= WINDOW_WIDTH && nextVertTouchY >= 0 && nextVertTouchY <= WINDOW_HEIGHT) {
			if (grid.hasWallsAt(nextVertTouchX - this.isRayFacingLeft, nextVertTouchY)) {
				foundVertWallHit = true;
				vertWallHitX = nextVertTouchX;
				vertWallHitY = nextVertTouchY;
				break ;
			} else{
				nextVertTouchX += xstep;
				nextVertTouchY += ystep;
			}
		}
		let horzHitDistance = (foundHorzWallHit)
			? distanceBetweenPoints(john.x, john.y, horizontalHitX, horizontalHitY) : Number.MAX_VALUE;
		let vertHitDistance = (foundVertWallHit)
			? distanceBetweenPoints(john.x, john.y, vertWallHitX, vertWallHitY) : Number.MAX_VALUE;
		this.wallHitX = (horzHitDistance < vertHitDistance) ? horizontalHitX : vertWallHitX
		this.wallHitY = (horzHitDistance < vertHitDistance) ? horizontalHitY : vertWallHitY
		this.distance = (horzHitDistance < vertHitDistance) ? horzHitDistance : vertHitDistance;
		this.wasHitVertical = (vertHitDistance < horzHitDistance);
		let xCoord;
		let yCoord;
		if (this.wasHitVertical) {
			xCoord = Math.floor((this.wallHitX - this.isRayFacingLeft) / TILE_SIZE);
			yCoord = Math.floor(this.wallHitY / TILE_SIZE);
		}
		else {
			xCoord = Math.floor(this.wallHitX / TILE_SIZE);
			yCoord = Math.floor((this.wallHitY - this.isRayFacingUp) / TILE_SIZE);
		}
		this.wallPaper = grid.grid[yCoord][xCoord];
	}
	render() {
		stroke("red");
		 line(
			MINIMAP_SCALE_FACTOR * john.x,
			MINIMAP_SCALE_FACTOR * john.y,
			MINIMAP_SCALE_FACTOR * this.wallHitX,
			MINIMAP_SCALE_FACTOR * this.wallHitY,
		);
	}
}

var grid = new Map();
var john = new Player();
var rays = [];

function castAllRays() {
	let rayAngle = john.rotationAngle - (FOV_ANGLE / 2);
	let col = 0;

	rays = [];
	while (col < RAY_NUMS)
	{
		var ray = new Ray(rayAngle);
		ray.cast();
		rays.push(ray);
		rayAngle += FOV_ANGLE / RAY_NUMS;
		col++;
	}
}

function normalizeAngle(angle) {
	angle = angle % (2 * Math.PI);
	if (angle < 0) {
		angle = (2 * Math.PI) + angle;
	}
	return angle;
}

function distanceBetweenPoints(x1, y1, x2, y2) {
	return (Math.sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

function setup() {
	createCanvas(WINDOW_WIDTH, WINDOW_HEIGHT);
}

function keyPressed() {
	if (keyCode == LEFT_ARROW)
	john.moveDirection = -1;
	else if (keyCode == RIGHT_ARROW)
		john.moveDirection = 1;
	else if (keyCode == UP_ARROW)
	john.walkDirection = 1;
	else if (keyCode == DOWN_ARROW)
		john.walkDirection = -1;
}

function keyReleased() {
	if (keyCode == LEFT_ARROW)
		john.moveDirection = 0;
	else if (keyCode == RIGHT_ARROW)
		john.moveDirection = 0;
	else if (keyCode == UP_ARROW)
		john.walkDirection = 0;
	else if (keyCode == DOWN_ARROW)
		john.walkDirection = 0;
}

function draw3DProjectedWalls() {
	let column;
	let projectedWallDistance;
	let projectedWallHeight;
	let	rayDistance;
	let transparency;
	let rgb = [];

	column = 0;
	background(0, 0, 0);
	for (ray of rays) {
		rayDistance = ray.distance * Math.cos(ray.rayAngle - john.rotationAngle);
		projectedWallDistance = (WINDOW_WIDTH / 2) / Math.tan(FOV_ANGLE / 2);
		projectedWallHeight = (TILE_SIZE / rayDistance) * projectedWallDistance;
		transparency = (100 / rayDistance);
		rgb[RED] = ray.wallPaper == RED ? 255 : 0;
		rgb[GREEN] = ray.wallPaper == GREEN ? 255 : 0;
		rgb[BLUE] = ray.wallPaper == BLUE ? 255 : 0;
		fill("rgba(" + rgb[RED] + "," + rgb[GREEN] + "," + rgb[BLUE] + "," + transparency + ")");
		noStroke();
		rect(
			column * WALL_STRIP_WIDTH,
			(WINDOW_HEIGHT - projectedWallHeight) / 2,
			WALL_STRIP_WIDTH,
			projectedWallHeight
		);
		column++;
	}
}

function update() {
	john.update();
	castAllRays();
}

function draw() {
	update();

	draw3DProjectedWalls();
	grid.render();
	for (ray of rays) {
		ray.render();
	}
	john.render();
}
