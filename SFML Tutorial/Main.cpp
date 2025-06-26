//#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/Audio.hpp>
//#include <SFML/Network.hpp>
//#include <iostream>
//using namespace std;
//using namespace sf;
//
//int main(){
//
//    RenderWindow window(VideoMode(800, 600), "Shooter Game", Style::Close | Style::Resize);
//    //this was for the window size, title, options like close, resize, etc.
//    Event evnt;
//
//    RectangleShape player(Vector2f(100.0f, 100.0f)); // for the size of the square
//    player.setFillColor(Color::White); // for the colour of the square
//    player.setOrigin(50.0f, 50.0f);
//    player.setPosition(206.0f, 206.0f);
//
// 
//    //texture:
//    Texture playerTexture; //created texture names player.
//    //we then load the texture from the file
//    playerTexture.loadFromFile("Shooter.png"); // for applying the path of texture and loading from files
//    player.setTexture(&playerTexture);
//
//    //loop for the game to begin
//    while (window.isOpen()) { //checking if window is open, if not open then the loop will terminate and end the application
//        
//        while (window.pollEvent(evnt)) { //getting events from window and saving them in this event variable we are creating
//
//
//            if (evnt.type == evnt.Closed) {
//                window.close();
//            }
//            else if (evnt.type == evnt.KeyPressed) {
//                if (evnt.key.code == sf::Keyboard::Escape) // closing window using escape key
//                    window.close();
//            }
//            else if (evnt.type == evnt.Resized) {
//                cout << "New window width: " << evnt.size.width << " New Window height: " << evnt.size.height << endl;
//            }
//            else if (evnt.type == evnt.TextEntered) {
//                if (evnt.text.unicode < 120)
//                    //cout << evnt.text.unicode; // printing unicode value for some reason
//                    cout << static_cast<char>(evnt.text.unicode); // same as: printf("%c", evnt.text.unicode);
//            }
//        }
//
//
//        if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
//            player.move(-0.1f, 0.0f); //left
//        }
//        if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
//            player.move(0.1f, 0.0f); //right
//        }
//        if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
//            player.move(0.0f, -0.1f); //up
//        }
//        if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
//            player.move(0.0f, 0.1f); //down
//        }
//        //co-ordinates are opposite for y-axis, negative on top and positive on bottom.
//
//
//        //Movement with mouse:
//        if (Mouse::isButtonPressed(Mouse::Left)) {
//            Vector2i mousePos = Mouse::getPosition(window);
//            player.setPosition((float)mousePos.x, (float)mousePos.y);
//        }
//
//        window.clear();//clear old frames: used for the space shooter to move and not leave traces, default is black 
//        window.draw(player);
//        window.display();
//    }
//
//    return 0;
//}