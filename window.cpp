//#include <SFML/Graphics.hpp>
#include "window.h"

static int flag = 0;
static sf::Color color[3] = {sf::Color::Red, sf::Color::Green, sf::Color::Blue};
/*  window_trial
    INPUT:  NONE
    OUTPUT: NONE
    EFFECT: This function creates a 600*800 window with the name "SFML works"
            This window will have a circle filled with blue color drawn
            The code is copied from SFML websites. This function serves merely  
            as a rough idea on how SFML works
*/
int window_trial()
{
    sf::RenderWindow window(sf::VideoMode(600, 800), "SFML works!");
    sf::CircleShape shape(300.f);
    shape.setFillColor(sf::Color::Blue);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}

/*  open_window
    INPUT:  NONE
    OUTPUT: NONE
    EFFECT: This function serves as the playground of interfacing SFML features.
            Especially the key/input feature of SFML since I wanted to build 
            Tetris and I need to make use of keyboard input from user-side
*/
int open_window()
{
    /*  Window module is not in charge of drawing contents  */
    sf::RenderWindow window;
    window.create(sf::VideoMode(800, 600), "My Window");

    sf::CircleShape shape(300.f);
    shape.setFillColor(sf::Color::Blue);
    /*  
        Main Loop / Game Loop
        a loop that ensures the app will be refersed until
        window is closed
    */
    while (window.isOpen()){
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
                case sf::Event::TextEntered:
                    if (event.text.unicode< 128){
                        cout << "key pressed is " << 
                        (char)(event.text.unicode) << endl;
                        if (event.text.unicode == 119 ||
                            event.text.unicode == 87){
                            cout << "yes " << endl;
                            shape.setFillColor(color[flag]);
                            flag ++;
                            if(flag >= 3){flag = 0;}
                            window.draw(shape);
                            window.display();
                        }
                        else{
                            cout << "no " << endl;
                            window.clear();
                        }
                    }
                    break;
                //case sf::Event:KeyPressed:

                default:
                    break;
            }

        }
    }
    return 0;
}