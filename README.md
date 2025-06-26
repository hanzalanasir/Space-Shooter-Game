# 🚀 Space Shooter Game

A classic arcade-style 2D space shooter game built in **C++ using SFML (Simple and Fast Multimedia Library)**. Take control of a spaceship, shoot down enemies, level up, and try to survive through all 5 levels!

## 🎮 Gameplay Features

- Smooth spaceship movement using Arrow keys or A/D
- Bullet firing with spacebar
- Progressive difficulty across 5 levels
- Enemy spawn rate and speed increases with level
- Lives and score tracking
- Game Over and Victory screen handling
- Background music and sound integration
- Session high scores saved to file

## 🛠️ Built With

- **Language:** C++
- **Library:** [SFML](https://www.sfml-dev.org/) (Graphics, Audio, Window, System, Network)
- **External Assets:**
  - Background image (`Space_bg.jpg`)
  - Spaceship texture (`spaceship.png`)
  - Bullet texture (`Bullet.png`)
  - Enemy texture (`Enemy.png`)
  - Background music (`cornfield_chase.mp3`)
  - Font (`Fonts/AnonymousPro-Regular.ttf`)

## 📂 Project Structure

```

Space-Shooter-Game/

│

├── Shooter.cpp # Main game source code

├── Assets/

│├── spaceship.png

│├── Enemy.png

│├── Bullet.png

│├── Space_bg.jpg

│└── cornfield_chase.mp3

├── Fonts/

│└── AnonymousPro-Regular.ttf


├── ExternalLibraries/ # Any third-party SFML/static dependencies

├── highscores.txt # Stores session high scores

└── README.md

````

> Note: All required SFML libraries and external dependencies are included in the repository to ease compilation and debugging.

## 🧪 How to Run

1. **Install SFML** if not already:
   - You can use your local setup or link dynamically to the provided `ExternalLibraries` if using this repo as-is.
2. **Compile the Code** (using g++ or any compatible C++ compiler):

```bash
g++ Shooter.cpp -o SpaceShooter -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
````

3. **Run the Executable**:

```bash
./SpaceShooter
```

## 🎮 Controls

| Action          | Key      |
| --------------- | -------- |
| Move Left       | ← or `A` |
| Move Right      | → or `D` |
| Shoot           | `Space`  |
| Start / Restart | `Space`  |
| Exit Game       | `Esc`    |

## 🧠 Developer Notes

* The game uses `sprites`, `textures`, and `text` objects to manage rendering.
* Game state is controlled with booleans like `isGameStarted`, `isGameOver`, and `isGameWon`.
* A `sessionHighScore` is tracked and stored in `highscores.txt` on game exit.
* Logic for enemy spawning, bullet firing, collision detection, and game win/loss is all handled in the main game loop.

## 📈 Future Enhancements

* Add enemy bullet shooting mechanics
* Introduce power-ups and new spaceship types
* Create a main menu and level selection
* Integrate sound effects on shooting and collisions
* Add scoreboards and persistent high scores

---


Made with 💻 and 🎮 by **Hanzala Nasir**

```
