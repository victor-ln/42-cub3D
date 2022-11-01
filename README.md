# __Cub3D__

![cub3dm](https://user-images.githubusercontent.com/81260589/193924497-8023cfb2-59fe-4447-adcc-3271828a182a.png)

## __Introduction__

This project is inspired by the world-famous Wolfenstein 3D game, which
was the first FPS ever. It enable us to explore ray-casting. Our goal was to
make a dynamic view inside a maze, in which we had to find your way.

## __Demonstration__

Demo gameplay showing menus.

![Mídia1](https://user-images.githubusercontent.com/63206471/196565968-0f375a13-efb8-4d3c-8aa5-bc9c982938c1.gif)

Demo gamplay showing weapons, crosshair, enemies and doors.

![Mídia2](https://user-images.githubusercontent.com/63206471/196566020-639a7e20-4002-444d-858b-f84def43266d.gif)

## __Skills that we have improved__

- Math applied to computer science
- Computer graphics
- Game events management
- Algorithms
- Trigonometry
- Bitwise operation
- Project management

## __How to run it ?__

- Clone the repository
````
git clone --recurse-submodules git@github.com:victor-ln/42-so_long.git
````
- Run `make` to compile _common part_ and `make bonus` to _bonus part_
- To clean objects files execute: `make clean`
- To clean executable file and objects: `make fclean`
- Recompile: `make re`
- Run `./cub3D` or `./cub3D_bonus` followed by map path e.g. `./maps/map_0.ber`

![Mídia1](https://user-images.githubusercontent.com/63206471/196570728-1f16241c-5569-44e3-88d9-acc6a17e749e.gif)

## __File configuration__

To run the game, you must pass as first argument a scene description file with the .cub
extension.

### __Identifiers__

The file must have 6 element identifiers:

- `'NO'`, `'SO'`, `'WE'` and `'EA'` : Represents the wall texture path on each direction.

- `'C'`, `'F'` : Represents the RGB color scale of the floor and celling respectively.

For example:

````
NO ./assets/xpm/walls/blue_wall_01.xpm
SO ./assets/xpm/walls/blue_wall_02.xpm
WE ./assets/xpm/walls/blue_wall_02.xpm
EA ./assets/xpm/walls/blue_wall_01.xpm

F 220,100,0
C 225,30,0
````

### __Map configuration__

The map construction is composed by the following characters:

#### _Common Part_

Walls: `'1'`

Empty spaces inside: `'0'`

Empty spaces outside: `' '`

Initial player direction: `'N'`, `'S'`, `'W'` or `'E'`

#### _Bonus Part_

Doors: `'D'`

Enemies: `'e'`

### __Map Rules__

- It must be completely surrounded by walls
- It must have a player

Map example:

````
111111111111111111111
100001000000000000001
101000000000000000001
100S00100100100100101
100000000000000000001
100000100000000000001
111111111111111111111
````

## __How to play__ ?

#### _Common part_

- The `'→'` and `'←'`  keys of the keyboard allow you to look left and
right in the maze.
- The `'W'`, `'A'`, `'S'`, and `'D'` keys allow you to move the point of view through
the maze.
- You can run holding `'Shift'` key.
- `'Esc'` key exits the game.

#### _Bonus part_

- Move the mouse to look left and right in the maze.
- The player shoots on left mouse click or `'Ctrl'` key. 
- The player opens the doors with `'E'` key.
- The `'M'` key pauses the game and displays a menu.
- Using `'→'`, `'←'`, `'↓'` and `'↑'` arrows allows you to navigate through the menu.
- Press `'Enter'` key to select an option in the menu.
