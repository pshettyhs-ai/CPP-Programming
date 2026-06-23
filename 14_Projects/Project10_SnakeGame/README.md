# 🐍 Project 10 — Console Snake Game

**Author:** Pavan Shetty H S  
**Concepts Used:** `deque`, 2D grid, real-time input, game loop, levels

---

## ✨ Features

- Classic snake gameplay in terminal
- Real-time keyboard input (WASD)
- Score system (×level multiplier)
- Level progression (speed increases, walls added)
- High score tracking
- Pause functionality
- Game over screen with replay option

## 🎮 Controls

| Key | Action |
|-----|--------|
| W / ↑ | Move Up |
| S / ↓ | Move Down |
| A / ← | Move Left |
| D / → | Move Right |
| P | Pause / Resume |
| Q | Quit |

## 🖥️ Sample Screen

```
╔══════════════════════════════╗
║ SNAKE GAME    Score:   50 Hi:   50 Lv:2 ║
╠══════════════════════════════╣
║██████████████████████████████║
║█                            █║
║█    ooo@                    █║
║█       *                    █║
║█                            █║
║██████████████████████████████║
╠══════════════════════════════╣
║ W/↑:Up  S/↓:Down  A/←:Left  D/→:Right  P:Pause  Q:Quit ║
╚══════════════════════════════╝
```

## ▶️ Compile & Run

```bash
# Linux/Mac
g++ -std=c++17 SnakeGame.cpp -o snake && ./snake

# Windows (MinGW)
g++ -std=c++17 SnakeGame.cpp -o snake.exe && snake.exe
```

## 📚 Key Design Decisions

- **`deque<Point>`** for snake body — O(1) push_front (new head) and pop_back (tail removal)
- **Game loop**: input → update → draw, with `sleepMs()` controlling speed
- **Non-blocking input**: `kbhit()` checks if key pressed without blocking the game loop
- **Level system**: speed decreases and wall obstacles added at each level

## 🐛 Challenges Faced

1. Cross-platform terminal clearing (`cls` vs `clear`)
2. Non-blocking keyboard input — very different on Linux vs Windows
3. Flicker-free rendering — minimized with full frame redraws
4. Self-collision detection — had to exclude the tail segment that's about to move

## 🚀 Future Ideas

- [ ] GUI version using SDL2
- [ ] Two-player mode
- [ ] Power-ups (speed boost, invincibility)
- [ ] Save/load high scores to file
