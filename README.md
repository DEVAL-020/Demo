# 🎮 Tetris Game in C++

A simple **console-based Tetris game built using C++**. The game features randomly generated Tetris pieces, piece rotation, collision detection, automatic falling, line clearing, and score tracking.

## 📌 Features

- **Seven Classic Tetris Shapes:** I, O, T, S, Z, J, and L.
- **Real-Time Controls:** Move and rotate pieces while playing.
- **Automatic Falling:** Pieces move downward automatically.
- **Collision Detection:** Prevents pieces from moving through walls or locked blocks.
- **Line Clearing:** Completed rows are removed from the board.
- **Score System:** Earn 100 points for each completed row.
- **Game Over Detection:** The game ends when a new piece cannot be placed.
- **Cross-Platform Support:** Includes separate input and console-handling code for Windows and Unix-like systems.

## 🛠️ Technologies Used

- **Language:** C++
- **Libraries:** `iostream`, `cstdlib`, `ctime`
- **Platform-Specific Libraries:**
  - Windows: `conio.h`, `windows.h`
  - Linux/macOS: `termios.h`, `unistd.h`, `sys/select.h`

## 🎮 Controls

| Key | Action |
|---|---|
| `A` | Move piece left |
| `D` | Move piece right |
| `W` | Rotate piece |
| `S` | Move piece down faster |
| `Esc` | Quit the game |

## ⚙️ Requirements

- A C++ compiler supporting modern C++.
- A terminal or command-line interface.
- Windows, Linux, or macOS with the appropriate terminal support.

## 🚀 How to Run

### 1. Clone the Repository

```bash
git clone <your-repository-url>
cd <your-project-folder>
```

Replace the placeholders with your actual repository URL and project folder name.

### 2. Compile the Code

**Using g++ on Windows:**

```bash
g++ tetris.cpp -o tetris
```

**Using g++ on Linux/macOS:**

```bash
g++ tetris.cpp -o tetris
```

### 3. Run the Game

**Windows:**

```bash
tetris.exe
```

**Linux/macOS:**

```bash
./tetris
```

## 🕹️ How to Play

1. Start the game from your terminal.
2. Use `A` and `D` to move the falling piece left or right.
3. Press `W` to rotate the piece.
4. Press `S` to move the piece downward faster.
5. Complete horizontal rows to clear them and earn points.
6. Keep clearing rows to increase your score.
7. Avoid stacking pieces to the top of the board, or the game will end.
8. Press `Esc` to quit.

## 📐 Game Details

- **Board Size:** 10 columns × 20 rows.
- **Piece Types:** 7 classic Tetris shapes.
- **Scoring:** 100 points per cleared row.
- **Game Loop:** Updates the display, processes keyboard input, and moves pieces downward at regular intervals.

## 📂 Project Structure

```text
Tetris/
├── tetris.cpp
└── README.md
```

## 🔮 Future Improvements

- Add a next-piece preview.
- Introduce increasing difficulty as the score grows.
- Add a hard-drop feature.
- Improve the scoring system for clearing multiple rows.
- Add colors to distinguish different pieces.
- Implement a pause and restart option.
- Improve keyboard input handling on Linux/macOS.

## 👨‍💻 Author

**Your Name**

## 📄 License

This project is available for educational and personal use. Add a specific open-source license if you intend to distribute it publicly.
