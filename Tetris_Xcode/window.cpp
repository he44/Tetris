/*                                  
 *
 * window.cpp - source file contatining functions for all three states of the 
                game (before, in, and after).
 *
 * "Copyright (c) 2017 by Yuchen He."
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice and the following
 * two paragraphs appear in all copies of this software.
 * 
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, 
 * SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE USE OF THIS 
 * SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE AUTHOR HAS BEEN ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 * 
 * THE AUTHOR SPECIFICALLY DISCLAIM ANY WARRANTIES, INCLUDING, BUT NOT LIMITED 
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 * PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND THE 
 * AUTHOR HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, 
 * ENHANCEMENTS, OR MODIFICATIONS."
 *
 * Author:          Yuchen He
 * Version:         1
 * Creation Date:   2017-05-15
 * Filename:        window.cpp
 * History:
 * Notice:          
 */
 #include "window.h"

/*  startPage
    INPUT:  window -- pointer to the window of the game
    OUTPUT: 0 -- on success
            -1 -- something wrong happened(actually it shouldn't return -1)
    EFFECT: This function will print a Tetirs logo, author information and 
            a short notice in the window.
            This function should only return after user presses Enter. After 
            this, the main function will proceed to tetrisGame function.
*/
int startPage(sf::RenderWindow* window)
{
    // cout << "starting page should appear " << endl;
    
    /*  Tetris Logo and Author Note     */
    sf::Texture pre_logo_t, author_t;
    sf::Sprite pre_logo_s, author_s;
    if(! pre_logo_t.loadFromFile("./resource/big_logo.jpg")){
        cout << "Failed to load logo image for start page" << endl;
        return -1;
    }
    pre_logo_s.setTexture(pre_logo_t);
    pre_logo_s.setPosition(193, 50);


    if(! author_t.loadFromFile("./resource/author_note.png")){
        cout << "Failed to load author note image for start page " << endl;
        return -1;
    }
    author_s.setTexture(author_t);
    author_s.setPosition(225, 500);

    /*  Instructions (Press Enter to Start) */
    //  Loads the font into program to print out my name
    sf::Font font_consolas;
    if(! font_consolas.loadFromFile("./resource/Consolas.ttf")){
        cout << "Failed to load Consolas font" << endl;
        return -1;
    }

    //  Setting up the text to display with name and date
    sf::Text text_intro;
    text_intro.setFont(font_consolas);
    text_intro.setString("Press Enter to Start");
    text_intro.setCharacterSize(24);
    text_intro.setFillColor(sf::Color::Red);
    text_intro.setPosition(sf::Vector2f(350, 425));

    sf::Event event;

    while(window->isOpen()){
        while(window->pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    window->close();
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Return){
                        return 0;   //so it can go to tetrisGame in main()
                    }
                    break;
                default:
                    break;
            }
        }
        window->clear();
        window->draw(pre_logo_s);
        window->draw(author_s);
        window->draw(text_intro);
        window->display();
    }

    return -1;
}

/*  tetrisGame
    INPUT:  window -- pointer to the window of the game
    OUTPUT: 0 -- if the game ends naturally
            -1 -- something wrong happened(actually it shouldn't return -1)
    EFFECT: This function correspond to the game process. It enables soft_drop 
            of the active piece, hard_drop on each press of SPACE, rotation of 
            active piece on each press of UP, moveLeft/moveRight on press of 
            LEFT or RIGHT.
            This function returns when the game ends.
*/
int tetrisGame(sf::RenderWindow* window)
{
    /*  Constructs the game object with pre-defined dimensions.
        The game board will be of 10 in width and 20 in height
    */
    Game main_game(BOARD_WIDTH, BOARD_HEIGHT);

    /*  Constructs the active piece */
    Piece act_piece(rand()%PIECE_TYPE);

    
    /*  
        Loads the logo sprite/texture from resource directory.
        The size is 300*200 and it starts at location (700,0), right corner
    */
    sf::Texture logo_t;
    sf::Sprite  logo_s;
    if(! logo_t.loadFromFile("./resource/logo.png")){
        cout << "Failed to load logo image for gaming" << endl;
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

    /*  
        Main Loop / Game Loop
        a loop that ensures the app will be refersed until
        window is closed
    */
    while (window->isOpen()){
        /*  checking timing condition here  */
        // the following code is able to provide an "almost 1-second" periodic 
        // interrupt(it's actually very close, we can print out the time 
        // elpsed to see)
        if (clock.getElapsedTime().asSeconds() >= (float)1){
            //cout << "1 second passed " << clock.getElapsedTime().asSeconds() << endl;

            /*  if current piece is in locking_down position, lock it 
                (although i believe that piece is actually already locked by the 
                else branch here)
                then we should check for clearline and actually clear them
            */
            if(act_piece.is_LockDown(&main_game)){
                /*  lock down active piece  */
                act_piece.lockDown(&main_game);
                /*  Check possibility of line clear */
                main_game.clearLine();
                /*  Generating a new active piece   */
                act_piece = Piece(rand()%PIECE_TYPE);
                /*  Check possibility of ending a game */
                if(act_piece.isOccupied(&main_game)){
                    return 0;//return to get into endPage in main.cpp
                }
            } 
            /*  if current piece is not in locking_down position, drop it by one
                cell.
                If it is in locking_down position after dropping, we lock it. 
                (This makes sure user cannot move the piece when they see it
                in place)
            */
            else {
                act_piece.soft_drop();
            }

            clock.restart();    //restart the clock for next 1-second
        }

        /*  
            Checking Any Event  
            pollEvent returns true if any event occurs
            Note: this function must be called in the same thread
            where window is creaed
        */
        sf::Event event;
        while (window->pollEvent(event)){
            /*  close the window if close event is detected 
                Window will get closed, program terminated
            */
            //if (event.type == sf::Event::Closed){window.close();}
            switch (event.type){
                case sf::Event::Closed:
                    window->close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Left){
                        //cout << "left key press detected " << endl;
                        act_piece.moveLeft(&main_game);
                    } else if (event.key.code == sf::Keyboard::Right){
                        //cout << "right key press detected " << endl;
                        act_piece.moveRight(&main_game);
                    } else if (event.key.code == sf::Keyboard::Space){
                        act_piece.hard_drop(&main_game);
                    } else if (event.key.code == sf::Keyboard::Up){
                        act_piece.rotate(&main_game);
                    }
                    break;
                default:
                    break;
            }
        }
        /*  Drawing sectoin: logo, text, game board and active piece  */
        window->clear(); //clear the buffer
        window->draw(logo_s);
        window->draw(text_intro);
        main_game.draw_board(window);
        act_piece.draw_piece(window);
        window->display();   //copy the buffer to video mem
        
    }
    return -1;
}


/*  endPage
    INPUT:  window -- pointer to the window of the game
    OUTPUT: 0 -- the user wants to restart the game
            1 -- the user wants to quit the game
            -1 -- something wrong happened(actually it shouldn't return -1)
    EFFECT: This function will print three lines of words. Telling the player 
            the game is over and he/she can either restart the game or merely 
            quit.
*/
int endPage(sf::RenderWindow* window)
{
    // cout << "end page should appear " << endl;
    
    /*  Instructions (Press Enter to Start) */
    //  Loads the font into program to print out my name
    sf::Font font_consolas;
    if(! font_consolas.loadFromFile("./resource/Consolas.ttf")){
        cout << "Failed to load Consolas font" << endl;
    }

    //  Setting up the text to display with name and date
    sf::Text text_intro;
    text_intro.setFont(font_consolas);
    text_intro.setString("GAME OVER:(\n\n\n\nPress Enter to Restart\n\nPress ESC to Quit");
    text_intro.setCharacterSize(24);
    text_intro.setFillColor(sf::Color(135, 206, 235));
    text_intro.setPosition(sf::Vector2f(350, 300));

    sf::Event event;
    while(window->isOpen()){
        while(window->pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    window->close();
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Return){
                        return 1;   //so it can go to tetrisGame in main()
                    } else if (event.key.code == sf::Keyboard::Escape){
                        return 0;
                    }
                    break;
                default:
                    break;
            }
        }
        window->clear();
        window->draw(text_intro);
        window->display();
    }

    return -1;
}


