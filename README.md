Snake Game
A classic Snake game built in C with a cool terminal interface using the ncurses library. Guide your snake to eat food, grow longer, and chase high scores—without crashing into walls or yourself!
Features

Smooth Gameplay: Move the snake around to grab food and watch it grow.
Score Tracking: Earn points for every bite and aim to beat your high score (stored in recorde.txt).
Pause Anytime: Hit Esc to pause and resume whenever you want.
Game Over Options: After losing, restart with any key or exit with e or Esc.

How to Play

Compile the Game:make


Run It:./snakegame



Controls

Move: Use w (up), a (left), s (down), d (right) or arrow keys.
Pause: Press Esc to pause/resume.
Exit: Press e to quit anytime.

Requirements

ncurses: Needed for the terminal graphics (install it if you don’t have it—e.g., sudo apt-get install libncurses5-dev on Ubuntu).
make: To build the project easily.

Project Breakdown
Here’s what’s inside:

main.c: The heart of the game—runs the main loop and ties everything together.
snakegame.c: Handles the game logic, like drawing the board, moving the snake, and spawning food.
lista.c: A doubly-linked list to keep track of the snake’s body.
recorde.c: Manages reading and saving the high score.
makefile: Makes compiling a breeze.

Contributing
Got ideas or fixes? Feel free to fork the repo, tweak it, and send a pull request. I’d love to see what you come up with!
License
This project is under the MIT License—check out the LICENSE file for details.

Happy gaming! 

