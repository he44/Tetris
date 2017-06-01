/*                                  
 *
 * main.cpp - main source file for the Tetris game
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
 * Creation Date:   2017-05-16
 * Filename:        main.cpp
 * History:
 * Notice:          
 */

#include "window.h"
#include "game.h"
#include "piece.h"

int main()
{
    /*  Enables "random" number generation  */
    srand(time(NULL));

    /*  Constructs the game object with pre-defined dimensions.
        The game board will be of 10 in width and 20 in height
    */
	Game main_game(BOARD_WIDTH, BOARD_HEIGHT);

    /*  Constructs the active piece */
    Piece act_piece(rand()%PIECE_TYPE);

    /*  Constructs the window for the game with pre-defined dimensions.
        The window will be of 1000 in width and 800 in height
    */
    sf::RenderWindow* window = new sf::RenderWindow;
    window->create(sf::VideoMode(WINDOW_WIDTH_X, WINDOW_HEIGHT_Y), 
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
                act_piece = Piece(rand()%PIECE_TYPE);
                /*  Check possibility of ending a game */
                if(act_piece.isOccupied(&main_game)){
                    // might do something else when game ends
                    window->close();
                    cout << "Game over" << endl;
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

	return 0;
}