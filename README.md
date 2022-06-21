Interactive console games in C.

The following are some games such as Snake, Renju, Tic Tac Toe and Zuma.
They follow the same conventional rules and more ore less same controls.

Zuma controls:
*Before the game starts
- To start a game - press ENTER
- Change the dimension of the table - press T
- Change the end-score (when does the game end) – press W
- Change the speed of the balls (difficulty) – press S

*After the game starts
- You can move your character using the keys: W - up, A - left, S - down, D – right, but you can’t leave the central area.
- You can change the orientation your character shoots to using the keys J - left, L – right, I – up, K – down.
- You can shoot a ball using SPACE.
- You can exit pe game using ESCAPE.

Zuma Rules:
From the bottom right side of the screen letters emerge and move on the screen around your character.
The letters are noted with the same color they have.
If the letters reach "0", you lose.
When you shoot, another letter moves from your turret in the orientation it currently has.
If it hits the line with letters, it is added to it, if it hits the border of the screen, it flies into cosmos forever.
If there are 3 or 4 letters of the same color alongside each other they get destroyed and the line backtracks until it is connected again.
If you destroy all the letters and reach the score goal, you win!

Technicalities:
The coloring was done using the <windows.h> library while reading the keyboard was done using <conio.h>
Because of the limitations of the console, I decided to abandon the idea of mouse tracking and introduced the 4 directional pointing.
Then to make aiming easier it was decided to also add a moving option.
The colors of the ball are created randomly.
The rules regarding striking a score remained faithful to the original.
You gain score after destroying 3 or 4 letters (4 letters give more points). 
This was done by creating a separatecase for when 3 identical letters are near each other and when 4 letters are.
To provide a more enjoyable game experience, I also incorporated a shooting animation, instead of the letter immediately being added to the line.
The backtracking is also performed step by step to bring a sense of continuity.
To signal to the player that they hit 3 or 4 balls in a row, I also change them for a split second into white "X".
To provide a diverse playing experience it is also possible to change the field size, winning score and speed of the letters before starting the game.