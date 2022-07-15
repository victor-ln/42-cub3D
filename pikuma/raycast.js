const TILE_SIZE = 32;
const MAP_NUM_ROWS = 11;
const MAP_NUM_COLS = 15;

const WINDOW_WIDTH = MAP_NUM_COLS * TILE_SIZE;
const WINDOW_HEIGHT = MAP_NUM_ROWS * TILE_SIZE;

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
		this.movementSpeed = 2;
		this.rotationSpeed = 2 * (Math.PI / 180);
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
        this.update();
        noStroke();
		fill("red");
		circle(this.x, this.y, this.radius);
        stroke("red");
        line(
            this.x,
            this.y,
            this.x + Math.cos(this.rotationAngle) * 30,
            this.y + Math.sin(this.rotationAngle) * 30,
        )
	}
}

var grid = new Map();
var jhon = new Player();

function setup() {
    createCanvas(WINDOW_WIDTH, WINDOW_HEIGHT);
}

function keyPressed() {
    if (keyCode == LEFT_ARROW)
        jhon.moveDirection = -1;
    else if (keyCode == RIGHT_ARROW)
        jhon.moveDirection = 1;
    else if (keyCode == UP_ARROW)
        jhon.walkDirection = 1;
    else if (keyCode == DOWN_ARROW)
        jhon.walkDirection = -1;
}

function keyReleased() {
    if (keyCode == LEFT_ARROW)
        jhon.moveDirection = 0;
    else if (keyCode == RIGHT_ARROW)
        jhon.moveDirection = 0;
    else if (keyCode == UP_ARROW)
        jhon.walkDirection = 0;
    else if (keyCode == DOWN_ARROW)
        jhon.walkDirection = 0;
}

function update() {
    // TODO: update all game objects before we render the next frame
}

function draw() {
    update();

    grid.render();
    jhon.render();
}
