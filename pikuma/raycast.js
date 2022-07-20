const TILE_SIZE = 64;
const MAP_NUM_ROWS = 11;
const MAP_NUM_COLS = 15;

const WINDOW_WIDTH = MAP_NUM_COLS * TILE_SIZE;
const WINDOW_HEIGHT = MAP_NUM_ROWS * TILE_SIZE;
const FOV_ANGLE = 60 * (Math.PI/180);
const RAY_STRIP_WIDTH = 1;
const RAY_NUMS = WINDOW_WIDTH / RAY_STRIP_WIDTH;

class Map {
	constructor() {
		this.grid = [
			[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
			[1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1],
			[1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1],
			[1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1],
			[1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1],
			[1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1],
			[1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
			[1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
			[1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1],
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
		return (this.grid[yIndex][xIndex] == 1);
	}
	render() {
		for (var i = 0; i < MAP_NUM_ROWS; i++) {
			for (var j = 0; j < MAP_NUM_COLS; j++) {
				var tileX = j * TILE_SIZE; 
				var tileY = i * TILE_SIZE;
				var tileColor = this.grid[i][j] == 1 ? "#222" : "#fff";
				stroke("#222"); // Its used to draw lines and borders around texts and shapes.
				fill(tileColor); // Its used to draw a color inside a shape.
				rect(tileX, tileY, TILE_SIZE, TILE_SIZE); // Creates a path for a rectangle at (x, y) position and (width, height) area.
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
		circle(this.x, this.y, this.radius);
		stroke("red");
		// line(
		// 	 this.x,
		// 	 this.y,
		// 	 this.x + Math.cos(this.rotationAngle) * 30,
		// 	 this.y + Math.sin(this.rotationAngle) * 30,
		// );
	}
}

class Ray {
	constructor(rayAngle) {
		this.rayAngle = normalizeAngle(rayAngle);
		this.wallHitX = 0;
		this.wallHitY = 0;
		this.distance = 0;
		this.wasHitVertical = false;

		this.isRayFacingDown = this.rayAngle > 0 && this.rayAngle < Math.PI;
		this.isRayFacingUp = !this.isRayFacingDown;

		this.isRayFacingRight = this.rayAngle < 0.5 * Math.PI || this.rayAngle > 1.5 * Math.PI;
		this.isRayFacingLeft = !this.isRayFacingRight;
	}
	cast(columnId) {
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
			else{
				nextHorzTouchX += xstep;
				nextHorzTouchY += ystep;
			}
		}

		var foundVertWallHit = false;
		var vertWallHitX = 0;
		var vertWallHitY = 0;

		xintercept = Math.floor(john.x / TILE_SIZE) * TILE_SIZE;
		xintercept += this.isRayFacingRight ? TILE_SIZE : 0;

		yintercept = john.y + (xintercept - john.x) * Math.tan(this.rayAngle);

		xstep = TILE_SIZE;
		xstep *= this.isRayFacingLeft ? -1 : 1;

		ystep = TILE_SIZE * Math.tan(this.rayAngle);
		ystep *= (this.isRayFacingUp && ystep > 0) ? -1 : 1;
		ystep *= (this.isRayFacingDown && ystep < 0) ? -1 : 1;

		var nextVertTouchX = xintercept;
		var nextVertTouchY = yintercept;

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
		var horzHitDistance = (foundHorzWallHit)
			? distanceBetweenPoints(john.x, john.y, horizontalHitX, horizontalHitY) : Number.MAX_VALUE;
		var vertHitDistance = (foundVertWallHit)
			? distanceBetweenPoints(john.x, john.y, vertWallHitX, vertWallHitY) : Number.MAX_VALUE;
		this.wallHitX = (horzHitDistance < vertHitDistance) ? horizontalHitX : vertWallHitX
		this.wallHitY = (horzHitDistance < vertHitDistance) ? horizontalHitY : vertWallHitY
		this.distance = (horzHitDistance < vertHitDistance) ? horzHitDistance : vertHitDistance;
		this.wasHitVertical = (vertHitDistance < horzHitDistance);
	}
	render() {
		stroke("red");
		 line(
			john.x,
			john.y,
			this.wallHitX,
			this.wallHitY,
		);
	}
}

var grid = new Map();
var john = new Player();
var rays = [];

function castAllRays() {
	var columnId = 0;
	var rayAngle = john.rotationAngle - (FOV_ANGLE / 2);
	var i = 0;
	rays = [];
	while (i < RAY_NUMS)
	{
		var ray = new Ray(rayAngle);
		ray.cast(columnId);
		rays.push(ray);
		rayAngle += FOV_ANGLE / RAY_NUMS;
		i++;
		columnId++;
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

function update() {
	john.update();
	castAllRays();
}

function draw() {
	update();

	grid.render();
	for (ray of rays)
	{
		ray.render();
	}
	john.render();
}
