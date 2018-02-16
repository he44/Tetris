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


int main()
{
    /*  Enables "random" number generation  */
    srand(time(NULL));
    /*  flag for restarting the game    */
    int restart = 1;   
    /*  Constructs the window for the game with pre-defined dimensions.
        The window will be of 1000 in width and 800 in height
    */
    sf::RenderWindow* window = new sf::RenderWindow;
    window->create(sf::VideoMode(WINDOW_WIDTH_X, WINDOW_HEIGHT_Y), 
                  "Tetris by Yuchen He");

    /* Display the starting page with logo, author information  */
    if (startPage(window) == -1){
        cout << "Something went wrong, please check error message above" << endl;
        return -1;
    }
    //when enter pressed in startPage, the function returns
    //then we get into game page

    while (restart){
        tetrisGame(window); //the game process, returns when the game ends
        restart = endPage(window);  //then we get into end page
                                    //endPage() returns either when use wants to
                                    //quit(restart = 0) or restart(restart = 1) 
                                    //the game
                                    //"restart" simply means calling tetrisGame
                                    //one more time
    }

    // if the code gets here, means user want to quit
    window->close();
	return 0;
}
