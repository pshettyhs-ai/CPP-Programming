/*
 * Project  : Console-Based Snake Game
 * Author   : Pavan Shetty H S
 * Date     : Week 17 — Most fun project so far!
 *
 * This was genuinely challenging to build. The hardest parts were:
 * 1. Real-time non-blocking keyboard input (platform-specific)
 * 2. Keeping the snake body rendering smooth
 * 3. Collision detection with self
 *
 * Uses: deque for snake body, 2D array for grid, raw terminal I/O
 *
 * Compile:
 *   Linux/Mac: g++ -std=c++17 SnakeGame.cpp -o snake
 *   Windows  : g++ -std=c++17 SnakeGame.cpp -o snake (MinGW)
 *
 * Note: Uses platform-specific terminal control.
 *       Works best on Linux/Mac terminal.
 */

#include <iostream>
#include <deque>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <thread>
#include <string>

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
    #define CLEAR "cls"
    bool kbhit_() { return _kbhit(); }
    char getch_() { return _getch(); }
    void sleepMs(int ms) { Sleep(ms); }
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
    #define CLEAR "clear"
    bool kbhit_() {
        struct termios oldt, newt;
        int ch, oldf;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);
        if (ch != EOF) { ungetc(ch, stdin); return true; }
        return false;
    }
    char getch_() { return getchar(); }
    void sleepMs(int ms) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }
#endif

using namespace std;

const int WIDTH  = 30;
const int HEIGHT = 20;

enum Direction { UP, DOWN, LEFT, RIGHT };

struct Point {
    int x, y;
    bool operator==(const Point& o) const { return x == o.x && y == o.y; }
};

class SnakeGame {
    deque<Point> snake;
    Point        food;
    Direction    dir;
    bool         gameOver;
    bool         paused;
    int          score;
    int          highScore;
    int          level;
    int          speed;      // ms delay between frames
    vector<Point> walls;     // extra obstacles at higher levels

    void spawnFood() {
        do {
            food.x = rand() % (WIDTH  - 2) + 1;
            food.y = rand() % (HEIGHT - 2) + 1;
        } while (isSnakeAt(food) || isWallAt(food));
    }

    bool isSnakeAt(Point p) const {
        for (auto& seg : snake) if (seg == p) return true;
        return false;
    }
    bool isWallAt(Point p) const {
        for (auto& w : walls) if (w == p) return true;
        return false;
    }

    void addLevelWalls() {
        walls.clear();
        if (level >= 2) {
            for (int x = 5; x <= 10; x++) walls.push_back({x, HEIGHT/2});
        }
        if (level >= 3) {
            for (int x = 18; x <= 24; x++) walls.push_back({x, HEIGHT/2});
            for (int y = 5;  y <= 10; y++)  walls.push_back({WIDTH/2, y});
        }
    }

    void draw() const {
        system(CLEAR);

        // Header
        cout << "╔";
        for (int x = 0; x < WIDTH; x++) cout << "═";
        cout << "╗\n";

        cout << "║" << " SNAKE GAME"
             << string(WIDTH - 28, ' ')
             << "Score:" << setw(5) << score
             << " Hi:" << setw(5) << highScore
             << " Lv:" << level << " ║\n";

        cout << "╠";
        for (int x = 0; x < WIDTH; x++) cout << "═";
        cout << "╣\n";

        // Grid
        for (int y = 0; y < HEIGHT; y++) {
            cout << "║";
            for (int x = 0; x < WIDTH; x++) {
                Point p{x, y};

                // Border
                if (x == 0 || x == WIDTH-1 || y == 0 || y == HEIGHT-1) {
                    cout << "█";
                }
                // Snake head
                else if (p == snake.front()) {
                    cout << "@";
                }
                // Snake body
                else if (isSnakeAt(p)) {
                    cout << "o";
                }
                // Food
                else if (p == food) {
                    cout << "*";
                }
                // Wall
                else if (isWallAt(p)) {
                    cout << "#";
                }
                else {
                    cout << " ";
                }
            }
            cout << "║\n";
        }

        cout << "╠";
        for (int x = 0; x < WIDTH; x++) cout << "═";
        cout << "╣\n";
        cout << "║ W/↑:Up  S/↓:Down  A/←:Left  D/→:Right  P:Pause  Q:Quit"
             << string(WIDTH - 55, ' ') << " ║\n";
        cout << "╚";
        for (int x = 0; x < WIDTH; x++) cout << "═";
        cout << "╝\n";

        if (paused) cout << "\n  *** PAUSED — Press P to resume ***\n";
    }

    void update() {
        if (paused || gameOver) return;

        Point newHead = snake.front();
        switch(dir) {
            case UP:    newHead.y--; break;
            case DOWN:  newHead.y++; break;
            case LEFT:  newHead.x--; break;
            case RIGHT: newHead.x++; break;
        }

        // Wall collision (border)
        if (newHead.x <= 0 || newHead.x >= WIDTH-1 ||
            newHead.y <= 0 || newHead.y >= HEIGHT-1) {
            gameOver = true; return;
        }

        // Extra wall collision
        if (isWallAt(newHead)) { gameOver = true; return; }

        // Self collision (skip tail — it's about to move)
        for (size_t i = 0; i < snake.size()-1; i++) {
            if (snake[i] == newHead) { gameOver = true; return; }
        }

        snake.push_front(newHead);

        // Ate food?
        if (newHead == food) {
            score += 10 * level;
            if (score > highScore) highScore = score;
            spawnFood();

            // Level up every 5 food items
            if (score % (50 * level) == 0) {
                level++;
                speed = max(50, speed - 20);
                addLevelWalls();
                cout << "\n  *** LEVEL UP! Now Level " << level << " ***\n";
                sleepMs(1000);
            }
        } else {
            snake.pop_back();
        }
    }

    void handleInput() {
        if (!kbhit_()) return;
        char c = getch_();
        c = tolower(c);
        switch(c) {
            case 'w': if (dir != DOWN)  dir = UP;    break;
            case 's': if (dir != UP)    dir = DOWN;  break;
            case 'a': if (dir != RIGHT) dir = LEFT;  break;
            case 'd': if (dir != LEFT)  dir = RIGHT; break;
            case 'p': paused = !paused;               break;
            case 'q': gameOver = true;                break;
        }
    }

public:
    SnakeGame() : dir(RIGHT), gameOver(false), paused(false),
                  score(0), highScore(0), level(1), speed(200) {
        srand(time(nullptr));

        // Initial snake — 3 segments
        snake.push_back({WIDTH/2,     HEIGHT/2});
        snake.push_back({WIDTH/2 - 1, HEIGHT/2});
        snake.push_back({WIDTH/2 - 2, HEIGHT/2});

        spawnFood();
    }

    void run() {
        cout << "\n╔══════════════════════════════╗\n";
        cout << "║      SNAKE GAME              ║\n";
        cout << "╠══════════════════════════════╣\n";
        cout << "║  Controls:                   ║\n";
        cout << "║  W/A/S/D  — Move             ║\n";
        cout << "║  P        — Pause            ║\n";
        cout << "║  Q        — Quit             ║\n";
        cout << "╠══════════════════════════════╣\n";
        cout << "║  Eat * to grow and score.    ║\n";
        cout << "║  Avoid walls and yourself.   ║\n";
        cout << "║  Level up every 5 foods!     ║\n";
        cout << "╚══════════════════════════════╝\n";
        cout << "\n  Press ENTER to start...";
        cin.get();

        while (!gameOver) {
            handleInput();
            update();
            draw();
            sleepMs(speed);
        }

        system(CLEAR);
        cout << "\n╔══════════════════════════════╗\n";
        cout << "║         GAME OVER!           ║\n";
        cout << "╠══════════════════════════════╣\n";
        cout << "║  Score     : " << left << setw(15) << score     << " ║\n";
        cout << "║  High Score: " << left << setw(15) << highScore << " ║\n";
        cout << "║  Level     : " << left << setw(15) << level     << " ║\n";
        cout << "║  Length    : " << left << setw(15) << snake.size() << " ║\n";
        cout << "╚══════════════════════════════╝\n\n";

        cout << "  Play again? (y/n): ";
        char c; cin >> c;
        if (c == 'y' || c == 'Y') {
            SnakeGame newGame;
            newGame.run();
        }
    }
};

int main() {
    SnakeGame game;
    game.run();
    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread SnakeGame.cpp -o prog
 ================================================================

 NOTE: This program terminates abnormally (uncaught std::length_error,
 SIGABRT, exit code 134) on the very first frame draw, regardless of
 any key pressed. The cause: in draw(), the line
   string(WIDTH - 55, ' ')
 evaluates WIDTH - 55 = 30 - 55 = -25 (int), which is then implicitly
 converted to a huge size_t when passed to the std::string(count, ch)
 constructor, exceeding string::max_size() and throwing. This is a
 genuine bug in the code above (WIDTH=30 is shorter than the 55-char
 control-legend string), reproduced exactly as it happens -- not a
 build or environment problem. Since this is a real-time, raw-terminal
 game (kbhit()/getch() via termios), the captured output below is the
 actual console session up to the crash, run with stdin = an ENTER
 keypress followed by 'n'.


 ╔══════════════════════════════╗
 ║      SNAKE GAME              ║
 ╠══════════════════════════════╣
 ║  Controls:                   ║
 ║  W/A/S/D  — Move             ║
 ║  P        — Pause            ║
 ║  Q        — Quit             ║
 ╠══════════════════════════════╣
 ║  Eat * to grow and score.    ║
 ║  Avoid walls and yourself.   ║
 ║  Level up every 5 foods!     ║
 ╚══════════════════════════════╝

   Press ENTER to start...terminate called after throwing an instance of 'std::length_error'
   what():  basic_string::_M_create

 [Process exited with status 134]

 ================================================================
*/

