#include "window.h"
#include "game.h"
#include "piece.h"

int main()
{
    /*  Constructs the game object with pre-defined dimensions.
        The game board will be of 10 in width and 20 in height
    */
	Game main_game(BOARD_WIDTH, BOARD_HEIGHT);

    /*  Constructs the active piece
    */
    // Piece act_piece(0);
    srand(time(NULL));
    Piece act_piece(rand()%PIECE_TYPE);

    /*  Constructs the window for the game with pre-defined dimensions.
        The window will be of 1000 in width and 800 in height
    */
    sf::RenderWindow window;
    window.create(sf::VideoMode(WINDOW_WIDTH_X, WINDOW_HEIGHT_Y), 
    			  "Tetris by Yuchen He");
    
    /*  
        Loads the logo sprite/texture from resource directory.
        The size is 300*200 and it starts at location (700,0), right corner
    */
    sf::Texture logo_t;
    sf::Sprite  logo_s;
    if(! logo_t.loadFromFile("./resource/logo.png")){
        cout << "Failed to load logo image" << endl;
    }
    logo_s.setTexture(logo_t);
    logo_s.setPosition(sf::Vector2f(700, 0));

    /*  Loads the font into program to print out my name
    */
    sf::Font font_consolas;
    if(! font_consolas.loadFromFile("./resource/Consolas.ttf")){
        cout << "Failed to load Consolas font" << endl;
    }

    /*  Setting up the text to display with name and date
    */
    sf::Text text_intro;
    text_intro.setFont(font_consolas);
    text_intro.setString("Developed by Yuchen He\n       2017-06");
    text_intro.setCharacterSize(24);
    text_intro.setFillColor(sf::Color::Red);
    text_intro.setPosition(sf::Vector2f(700, 250));
    
    /*  Setting up the variables for time   */
    sf::Clock clock;

    int flag = 0;
    /*  
        Main Loop / Game Loop
        a loop that ensures the app will be refersed until
        window is closed
    */
    while (window.isOpen()){
        /*  checking timing condition here  */
        // the following code is able to provide an "almost 1-second" periodic 
        // interrupt
        if (clock.getElapsedTime().asSeconds() >= (float)1){
            //cout << "1 second passed " << clock.getElapsedTime().asSeconds() << endl;
            
            if(act_piece.is_LockDown(&main_game)){
                /*  lock down active piece  */
                act_piece.lockDown(&main_game);
                /*  Check possibility of line clear */
                main_game.clearLine();
                // flag++;
                // if(flag >= 7){flag = 0;}
                // act_piece = Piece(flag);
                // srand(time(NULL));
                act_piece = Piece(rand()%PIECE_TYPE);
            } else {
                act_piece.soft_drop();
                if(act_piece.is_LockDown(&main_game)){
                    act_piece.lockDown(&main_game);
                }
            }

            //act_piece.soft_drop(&main_game);

            clock.restart();
        }

        /*  
            Checking Any Event  
            pollEvent returns true if any event occurs
            Note: this function must be called in the same thread
            where window is creaed
        */
        sf::Event event;
        while (window.pollEvent(event)){
            /*  close the window if close event is detected 
                Window will get closed, program terminated
            */
            //if (event.type == sf::Event::Closed){window.close();}
            switch (event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                // case sf::Event::TextEntered:
                    // if (event.text.unicode< 128){
                    //     cout << "key pressed is " << 
                    //     (char)(event.text.unicode) << endl;
                    // }
                    // break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Left){
                        //cout << "left key press detected " << endl;
                        act_piece.moveLeft();
                    } else if (event.key.code == sf::Keyboard::Right){
                        //cout << "right key press detected " << endl;
                        act_piece.moveRight();
                    } else if (event.key.code == sf::Keyboard::Space){
                        act_piece.hard_drop(&main_game);
                    }
                    break;
                default:
                    break;
            }
        }
        /*  Drawing sectoin: logo, text, game board and active piece  */
        window.clear(); //clear the buffer
        window.draw(logo_s);
        window.draw(text_intro);
        main_game.draw_board(&window);
        act_piece.draw_piece(&window);
        window.display();   //copy the buffer to video mem
        
    }

	return 0;
}