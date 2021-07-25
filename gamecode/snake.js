//type that represents location
function Vector2(x,y) {
    this.x = x;
    this.y = y;
    this.set = function (vector) {
        this.x = vector.x;
        this.y = vector.y;
    };
    this.equal = function (vector) {
        return this.x == vector.x && this.y == vector.y;
    };
}

Vector2.prototype = Object.create(null,
    {

    });

let SnakeBlockType =
{
    Head : 0,
    Body: 1,
    Tail :2
}

//representation of the snake body
function SnakeBlock() {
    this.location = new Vector2(0, 0);
    this.previousLocation = new Vector2(0,0);
    //this value
    this.type = SnakeBlockType.Body
}

function FoodBlock()
{
    this.location = new Vector2(0, 0);
}

FoodBlock.prototype = Object.create(null,{});

SnakeBlock.prototype = Object.create(null,{

});

//get canvas for future use
let canvas;
let context;

//default variables
let shapeSize = 50;
let deltaTime = 1;

//parts of the snake that need update
let snakeParts = [];
let food = [];

//set of objects that kill player on touch
let obstacles = [];

let inputKeyIsHeld = false;

let fieldSize = 0;

//0 - up, 1- right,2 - down,3 - down
let lastDirection = 1;
let turnBased = false;

function drawSnakePart(snakeBlock) {
    switch (snakeBlock.type) {
        case SnakeBlockType.Body:
            //draw a square
            context.fillStyle = 'rgb(255,0,0)';
            break;
        case SnakeBlockType.Head:
            context.fillStyle = 'rgb(0,0,255)';
            break;
        case SnakeBlockType.Tail:
            context.fillStyle = 'rgb(0,255,0)';
            break;
        default:
            break;
    }
    context.fillRect(snakeBlock.location.x*shapeSize, snakeBlock.location.y*shapeSize, shapeSize, shapeSize);
}


function draw() {
    //clear the canvas
    context.fillStyle = "white";
    context.fillRect(0, 0, canvas.width, canvas.height);

    //draw snake parts
    for (let i = 0; i < snakeParts.length; i++) {
        if (snakeParts[i] != null) {
            drawSnakePart(snakeParts[i]);
        } else {
            alert("Invalid snake data has been passed!");
        }
    }

    for (let i = 0; i < food.length; i++) {
        context.fillStyle = 'yellow';
        context.fillRect(shapeSize * 0.25 + shapeSize * food[i].location.x, shapeSize * 0.25 + shapeSize * food[i].location.y, shapeSize * 0.75, shapeSize * 0.75);
    }

    for (let i = 0; i < obstacles.length; i++) {
        context.fillStyle = 'black';
        context.fillRect(shapeSize*obstacles[i].x,shapeSize*obstacles[i].y,shapeSize,shapeSize);
    }
}

function die()
{
    alert("you dead");
}

function update() {
    if(!turnBased) {
        //in normal language
        //snakeParts[0].previousLocation =  snakeParts[0].location
        //would work, but it's javascript and it tries to assign reference to the value not value of the value
        snakeParts[0].previousLocation.x = snakeParts[0].location.x;
        snakeParts[0].previousLocation.y = snakeParts[0].location.y;
        switch (lastDirection) {
            case 0/*"ArrowUp"*/:
                snakeParts[0].location.y -= 1;
                break;
            case 2/*"ArrowDown"*/:
                snakeParts[0].location.y += 1;
                break;
            case 3/*"ArrowLeft"*/:
                snakeParts[0].location.x -= 1;
                break;
            case 1/*"ArrowRight"*/:
                snakeParts[0].location.x += 1;
                break;
            default:
                break;
        }
    }

    if ((snakeParts[0].location.x > fieldSize || snakeParts[0].location.x < 0) || (snakeParts[0].location.y > fieldSize || snakeParts[0].location.y < 0)) {
        die();
    }
    //update location
    for (let i = 1; i < snakeParts.length; i++) {
        if (snakeParts[i] != null) {
            snakeParts[i].previousLocation.x = snakeParts[i].location.x;
            snakeParts[i].previousLocation.y = snakeParts[i].location.y;

            snakeParts[i].location.x = snakeParts[i - 1].previousLocation.x;
            snakeParts[i].location.y = snakeParts[i - 1].previousLocation.y;

            snakeParts[i].type = SnakeBlockType.Body;

            if (snakeParts[0].location.x == snakeParts[i].location.x && snakeParts[0].location.y == snakeParts[i].location.y) {
                die();
            }
        }
    }

    for (let i = 0; i < food.length; i++) {
        if (snakeParts[0].location.x == food[i].location.x && snakeParts[0].location.y == food[i].location.y) {
            let id = snakeParts.length;
            snakeParts[id] = new SnakeBlock();
            snakeParts[id].location.x = snakeParts[id - 1].previousLocation.x;
            snakeParts[id].location.y = snakeParts[id - 1].previousLocation.y;

            food[0].location.x = Math.floor(Math.random() * fieldSize);
            food[0].location.y = Math.floor(Math.random() * fieldSize);
            break;
        }
    }

    for (let i = 0; i < obstacles.length; i++) {
        if (obstacles[i] != null && obstacles[i].equal(snakeParts[0].location)) {
            die();
        }
    }

    snakeParts[snakeParts.length - 1].type = SnakeBlockType.Tail;
    snakeParts[0].type = SnakeBlockType.Head;

    draw();
}

function updateMovement(keyThing) {
    switch (keyThing) {
        case "ArrowUp":
            if (turnBased) {
                snakeParts[0].location.y -= 1;
            } else {
                lastDirection = 0;
            }
            break;
        case "ArrowDown":
            if (turnBased) {
                snakeParts[0].location.y += 1;
            } else {
                lastDirection = 2;
            }
            break;
        case "ArrowLeft":
            if (turnBased) {
                snakeParts[0].location.x -= 1;
            } else {
                lastDirection = 3;
            }
            break;
        case "ArrowRight":
            if (turnBased) {
                snakeParts[0].location.x += 1;
            } else {
                lastDirection = 1;
            }
            break
            break;
        default:
            break;
    }
}

//generate world
function load() {
    canvas = document.getElementById("gamefield");
    context = canvas.getContext('2d');

    fieldSize = document.getElementById("fieldSize").value;

    canvas.height = fieldSize * shapeSize;
    canvas.width = fieldSize * shapeSize;

    snakeParts = [];
    snakeParts[0] = new SnakeBlock();
    snakeParts[0].location = new Vector2(1, 0);
    snakeParts[0].type = SnakeBlockType.Head;

    food[0] = new FoodBlock();
    food[0].location.x = Math.floor(Math.floor(Math.random() * fieldSize));
    food[0].location.y = Math.floor(Math.floor(Math.random() * fieldSize));

    for (let i = 0; i < document.getElementById("obstacleCount").value; i++) {
        obstacles[i] = new Vector2(Math.floor(Math.random() * fieldSize), Math.floor(Math.random() * fieldSize));
    }

    turnBased = document.getElementById("turnBased").checked;
    if (!turnBased) {
        setInterval(update, document.getElementById("inverval").value*100)
    }
    else { //input handling
        window.addEventListener('keydown', function (e) {
            if (!inputKeyIsHeld) {
                //no spam here
                inputKeyIsHeld = true;

                //in normal language
                //snakeParts[0].previousLocation =  snakeParts[0].location
                //would work, but it's javascript and it tries to assign reference to the value not value of the value
                snakeParts[0].previousLocation.x = snakeParts[0].location.x;
                snakeParts[0].previousLocation.y = snakeParts[0].location.y;

                updateMovement(e.key);
            }
            update();
        });

        window.addEventListener('keyup', function (e) {
            inputKeyIsHeld = false;
        });
    }

    draw();
}

