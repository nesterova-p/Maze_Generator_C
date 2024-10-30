## Project Goal

The goal of this project is to create a maze generator based on user-defined dimensions (from 2x2 to 10x10) and to generate a directed graph traversing through the maze.

## Compilation

To compile the program, execute the following command in the terminal:

```bash
gcc main.c stos.c labir.c graficz.c graf.c -lncurses -lm
```

## Requirements

For graphical representation of the maze, the `ncurses` library is required, which can be installed in the terminal using:

```bash
sudo apt-get install libncurses5-dev libncursesw5-dev
```

## Example Execution

After compilation, the user will see a graphical visualization of the maze along with the graph traversing through its structure.

![Image 2](https://github.com/user-attachments/assets/0ce0d001-6520-438b-a569-2c8d060817c5)

---

![Image 1](https://github.com/user-attachments/assets/614a24f4-7d7c-4d54-9d40-ccf5f21a8421)
