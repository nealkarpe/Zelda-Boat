3D WORLD - BOAT GAME
====================

## Running Instructions
- mkdir build
- cd build
- cmake ..
- make
- ./game

## Controls
- A: Turn left
- D: Turn right
- W: Move front
- SPACE: Jump
- B: Turn on/off booster
- CURSOR: Move cannon around
- MOUSE LEFT-CLICK: Fire
- T: Toggle camera

## Objective
- Maximize your score by collecting as many coins as possible.
- Kill monsters and pick up goodies dropped by them.
- On killing 3 monsters, a boss will appear. On killing the boss, a booster is dropped.
- Pick up the booster to get boost points which enable you to speed up.

## The world
- Boat - You operate Link's ship. It also has a cannon to shoot fireballs.
- Rocks - Randomly laid out rocks. Collision with a rock incurs penalty.
- Monsters - Colored in green, red, blue. On killing a them, a goodie is dropped (either a coin or health points). Bumping into them incurs penalty.
- Boss - It appears after killing 3 monsters. Killing the boss allows you to pick up more 'boost'.
- Booster - Press B to use your 'boost'. When booster is on, you will move faster until your boost runs out.
- Barrels - There are barrels with coins hovering above them. Jump in the air over the barrel to collect the coin.
- Wind - At fixed intervals there is wind blowing at a random angle and it pushes the sail of your boat to align in the direction of the wind.

## Scores
- Gold coin: +4 points
- Purple coin: +2 points
- Pink coin: +1 points
- Medicine: +0.2 health
- Booster: +400 boost

## Camera Views - 'T' to toggle between these
- Helicopter-cam view: The camera can be controlled in an intuitive manner-
  - SCROLL: zoom-in/zoom-out
  - CURSOR: Aim cannon
  - Arrow Keys: Move the camera around

- Follow-cam view: A view of the ship and the region in front of it from a location behind
and above it.

- Boat view: We see what the ship sees, as if we were on the ship.

- Top View: A view that gives a clear picture of the path. It appears as if we were looking vertically downwards from a position in the sky.

- Tower view: The camera is sitting on a tower to the side of the plane of playing, observing it at an angle.

## Screenshot
![screenshot](https://user-images.githubusercontent.com/31779922/37220521-e528610a-23ec-11e8-807a-6d1134c1edab.png)
