#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;
using namespace sf;


int sessionHighScore = 0; // To track the highest score of the session

int main() {
    srand(time(NULL));

    RenderWindow window(VideoMode(1920, 974), "Space Shooter Game", Style::Close | Style::Resize);//this was for the window size, title, options like close, resize, etc.
    window.setFramerateLimit(60); // for the refresh rate of enemy and bullet movements

    // Background music setup
    Music backgroundMusic;
    backgroundMusic.openFromFile("cornfield_chase.mp3");
    backgroundMusic.setLoop(true);   // Loop the music as the audio was 30 second so to repeat it over and over
    backgroundMusic.setVolume(100);   // Set volume (0 to 100)
    backgroundMusic.play();          // Start playing the music

    bool isGameStarted = false; // Start menu is active initially
    bool isGameOver = false; // Tracks if the game is over
    //score and lives text:
    int score = 0;
    int lives = 3;
    int shootTimer = 0;
    int enemyTimer = 0;
    int hitCounter = 0; // Tracks the number of times the spaceship is hit
    int currentLevel = 1; // Start at Level 1
    float enemySpeed = 5.0; // Initial enemy speed
    int spawnRate = 50; // Initial enemy spawn rate (lower is faster)
    bool isGameWon = false; // Track if the game is won


    Font font;
    font.loadFromFile("Fonts/AnonymousPro-Regular.ttf");

    //Start menu text:
    Text startMenuText;
    startMenuText.setFont(font);
    startMenuText.setCharacterSize(40);
    //text.setColor(Color::Blue);
    startMenuText.setStyle(Text::Bold);
    startMenuText.setString("\t\t\t\t\t  Space Shooter Game \n\n\n \t\t\t\t\t\tINSTRUCTIONS: \n \n \t\t\t Use ( Arrow keys / A or D ) to move around \n\n \t\t\t Press space to fire bullets \n\n \t\t\t Press space key to Start Level 1 \n\n \t\t\t Press Esc key to Exit");
    startMenuText.setPosition(5.0, window.getSize().y / 6);


    // Text objects for score, level, lives

    Text levelText;
    levelText.setFont(font);
    levelText.setCharacterSize(36);
    levelText.setPosition(10.0, 10.0); // Top-left corner for level
    levelText.setFillColor(Color::Blue);

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setPosition(10.0, 60.0);
    scoreText.setFillColor(Color::Green);

    Text livesText;
    livesText.setFont(font);
    livesText.setCharacterSize(30);
    livesText.setPosition(10.0, 100.0);
    livesText.setFillColor(Color::Red);


    //Game over text:
    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setStyle(Text::Bold);
    gameOverText.setString("Game Over!\n\nPress SPACE to Restart from Levels 1\nPress ESC to Exit");
    gameOverText.setPosition(window.getSize().x / 2.0 - 500.0, window.getSize().y / 3.0); // Centered on the screen

    //Game won text
    Text winText;
    winText.setFont(font);
    winText.setCharacterSize(50);
    winText.setFillColor(Color::Green);
    winText.setStyle(Text::Bold);
    winText.setString("You Win, completed all 5 levels!\n\nPress SPACE to Restart from Level 1\nPress ESC to Exit the game");
    winText.setPosition(window.getSize().x / 2.0 - 500.f, window.getSize().y / 3.0);


    //textures for the images of the objects:
    Texture backgroundTexture;
    backgroundTexture.loadFromFile("Space_bg.jpg"); // Background image

    Texture spaceshipTexture;  //naming
    spaceshipTexture.loadFromFile("spaceship.png");  //accessing from the folder where cpp file is stored

    Texture bulletTexture;
    bulletTexture.loadFromFile("Bullet.png");

    Texture enemyTexture;
    enemyTexture.loadFromFile("Enemy.png");

    //OBJECTS:

    Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y);

    Sprite spaceshipSprite; //creation of Sprites which are used to display textures (2D images) on the screen 
    spaceshipSprite.setTexture(spaceshipTexture); //to associate it with textures
    spaceshipSprite.setScale(0.5, 0.5); //sizing of the texture
    spaceshipSprite.setPosition(window.getSize().x / 2 - spaceshipTexture.getSize().x / 4, window.getSize().y - spaceshipTexture.getSize().y / 2 - 10.0); // positioing

    Sprite bulletSprite;
    bulletSprite.setTexture(bulletTexture);
    bulletSprite.setScale(0.2, 0.2);

    Sprite enemySprite;
    enemySprite.setTexture(enemyTexture);
    enemySprite.setScale(0.1, 0.1);

    Vector2f spaceshipCenter;

    vector<Sprite> bullets; // sprite represents a drawable 2d object to display texture on the screen, each bullet individual sprite


    vector<Sprite> enemies;
    enemies.push_back(Sprite(enemySprite));
    //creates a new Sprite object based on an existing Sprite (enemySprite) and adds it to the enemies vector.
    //push_back Adds the newly created Sprite to the end of the bullets vector.
    //bulletSprite object is used as a template for the new bullet.

    while (window.isOpen()) { //checking if window is open, if not open then the loop will terminate and end the application

        Event evnt;
        while (window.pollEvent(evnt)) { //getting events from window and saving them in this evnt variable we are creating

            if (evnt.type == evnt.Closed) {
                // Log the session's highest score
                ofstream file("highscores.txt", ios::app); // Append mode
                if (file.is_open()) {
                    file << "Session High Score: " << sessionHighScore << '\n';
                    file.close();
                    cout << "done";
                }
                window.close(); // Close the game window
            }
            else if (evnt.type == evnt.Resized)
                cout << "New window width: " << evnt.size.width << " New Window height: " << evnt.size.height << endl;

            if (evnt.type == Event::KeyPressed) {
                if (evnt.key.code == Keyboard::Space) {
                    if (isGameOver || isGameWon) {
                        // Restart the game
                        isGameOver = false;
                        isGameWon = false;
                        score = 0;
                        lives = 3;
                        currentLevel = 1; // Restart from level 1
                        enemies.clear();
                        bullets.clear();
                        enemySpeed = 5.0; // Reset speed
                        spawnRate = 50;   // Reset spawn rate
                    }
                    // Here, it transitions to the game that is level 1 code
                    window.clear();
                    break;  // Exit the start menu loop and start the game
                }

                if (evnt.key.code == Keyboard::Escape) {
                    if (isGameStarted && !isGameOver && !isGameWon) {
                        // Restart the game from Level 1 during gameplay, this doesn't work for any other window as said in instructions
                        isGameStarted = true;
                        isGameOver = false;
                        isGameWon = false;
                        score = 0;
                        lives = 3;
                        currentLevel = 1;
                        enemies.clear();
                        bullets.clear();
                        enemySpeed = 5.0;
                        spawnRate = 50;
                        //resets all the variables and stuff for restart
                    }
                    else {
                        // Log the session's highest score
                        ofstream file("highscores.txt", ios::app); // Append mode
                        if (file.is_open()) {
                            file << "Session High Score: " << sessionHighScore << '\n';
                            file.close();
                            cout << "done";
                        }
                        window.close();// Exit the game in other states (start menu, game over, or game win)
                    }
                }
            }
        }

        // Update level based on score
        int levelScoreThresholds[] = { 10, 30, 60, 100, 150 }; // Threshold scores for each level
        if (currentLevel <= 5 && score > levelScoreThresholds[currentLevel - 1]) {
            currentLevel++;
            enemySpeed += 1.0; // Increase speed with each level
            spawnRate = max(10, spawnRate - 10); // Increase spawn rate (minimum 10)
            if (currentLevel > 5) {
                isGameWon = true; // Player wins the game after completing Level 5
            }
        }

        // Start Menu Logic
        if (!isGameStarted) {
            window.clear();
            window.draw(startMenuText); // Draw the start menu
            window.display();

            // Check if Space key is pressed to start the game
            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                isGameStarted = true; // Switch to game state
                window.clear(); // Clear the menu screen
                continue; // Restart the loop for game logic
            }
            continue; // Skip the rest of the loop (do not run game logic)
        }

        // Win logic
        if (isGameWon) {
            window.clear();
            window.draw(backgroundSprite); // Draw the background image
            window.draw(winText);          // Draw the "You Win" text
            window.display();
            continue; // Skip the rest of the game logic if won
        }

        //Game over logic
        if (isGameOver) {
            window.clear();
            window.draw(backgroundSprite); // Draw the background image
            window.draw(gameOverText);     // Draw the "Game Over" text
            window.display();
            continue; // Skip further drawing if game over
        }

        //UPDATE

        // for the centre position of spaceship:
        spaceshipCenter = Vector2f(
            spaceshipSprite.getPosition().x + spaceshipTexture.getSize().x * spaceshipSprite.getScale().x / 2,
            spaceshipSprite.getPosition().y);

        // Spaceship movement:
        float movementSpeed = 10.0; // Speed of spaceship movement

        if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) { //checks if the left arrow key or a
            // Move left but prevent moving out of bounds so that spaceship does not go beyond the left end of the window:
            if (spaceshipSprite.getPosition().x > 0) {
                spaceshipSprite.move(-movementSpeed, 0.0);
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
            if (spaceshipSprite.getPosition().x + spaceshipTexture.getSize().x * spaceshipSprite.getScale().x < window.getSize().x) {
                spaceshipSprite.move(movementSpeed, 0.0);
            }
        }

        //BULLETS
        if (shootTimer < 10)
            shootTimer++;

        if (Keyboard::isKeyPressed(Keyboard::Space) && shootTimer >= 10) { // for shooting bullets and shoottimer is for spacing between consecutive bullets
            bulletSprite.setPosition(spaceshipCenter.x - bulletTexture.getSize().x * 0.1, spaceshipCenter.y); // Adjust for texture center
            bullets.push_back(bulletSprite);
            shootTimer = 0;
        }

        for (long long i = 0; i < bullets.size(); i++) {
            bullets[i].move(0.0, -10.0);
            if (bullets[i].getPosition().y <= 0) {
                bullets.erase(bullets.begin() + i); // if outside screen, then we will remove it
            }
        }

        // ENEMIES
        if (enemyTimer < spawnRate) { // Use dynamic spawn rate
            enemyTimer++;
        }
        if (enemyTimer >= spawnRate) {
            enemySprite.setPosition((rand() % int(window.getSize().x - enemyTexture.getSize().x * 0.5)), 0.0);
            enemies.push_back(enemySprite);
            enemyTimer = 0;
        }
        for (long long i = 0; i < enemies.size(); i++) {
            enemies[i].move(0.0, enemySpeed); // Use dynamic enemy speed
            if (enemies[i].getPosition().y > window.getSize().y - 20) {
                enemies.erase(enemies.begin() + i);
            }
        }

        //Collosion:

        //Spaceship collision with enemies:
        for (long long i = 0; i < enemies.size(); i++) {
            if (enemies[i].getGlobalBounds().intersects(spaceshipSprite.getGlobalBounds())) {
                enemies.erase(enemies.begin() + i); // Remove the enemy after a collision
                hitCounter++; // Increment hit counter
                lives--; // Decrease lives
                if (lives <= 0) {
                    isGameOver = true; // Trigger game over state
                }
            }
        }

        //Aliens collision with bullets:
        if (!enemies.empty() && !bullets.empty()) {
            for (long long i = 0; i < bullets.size(); i++) {
                for (long long k = 0; k < enemies.size(); k++) {
                    if (bullets[i].getGlobalBounds().intersects(enemies[k].getGlobalBounds())) {
                        bullets.erase(bullets.begin() + i); // remove the projectile as soon as it hits
                        enemies.erase(enemies.begin() + k); // remove enemies as soon as attacked
                        score += 1; // Increase score
                        if (score > sessionHighScore) {
                            sessionHighScore = score; // Update if the current score exceeds the session high score
                        }
                        break;
                    }
                }
            }
        }

        // Update score and lives text
        scoreText.setString("Score: " + to_string(score));
        livesText.setString("Lives: " + to_string(lives));
        levelText.setString("Level: " + to_string(currentLevel));

        //DRAW

        window.clear();//clear old frames: used for the space shooter to move and not leave traces, default is black
        window.draw(backgroundSprite); //for the drawing of background image
        window.draw(spaceshipSprite);

        for (long long i = 0; i < enemies.size(); i++) {
            window.draw(enemies[i]);
        }
        for (long long i = 0; i < bullets.size(); i++) {
            window.draw(bullets[i]);
        }

        if (!isGameStarted) {
            window.draw(startMenuText); // Only draw when in start menu
        }

        //for displaying text:
        window.draw(levelText);
        window.draw(scoreText);
        window.draw(livesText);

        window.display();
    }
    return 0;
}