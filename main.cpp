/**
 * @file main.cpp
 * @author Doaa Hagag (doaahagag128@gmail.com)
 * @brief A program to print a random quote based on the user's emotions.
 *          The user is required to enter what he is feeling based on a selection list. 
 *          then a quote should be printed That can counter this emotion, so 
 *          if the user is feeling sad, a quote that can make him happy should be printed.
 *          if the user is feeling happy, a Quote that can make him sad should be printed :D and so on.
 *          -The Quotes are saved in simple database files.
 *          -the user can backup the states.
 *          -design patterns : Memento ,  Mediator
 * @version 1.0.0
 * @date 2024-05-26
 */

#include "classes.hpp"

void Welcome ();

/**
 * @brief The main function initializes the QuoteMediator 
 * and runs the interaction loop where the user can input emotions or undo actions.
 * @return int 
 */
int main()
{
    // make object of the orginator (QuoteMediator)
    QuoteMediator mediator;

    Welcome();

    std::string backupType;
    std::cout << "Select backup type \n1: save all States (Default). note : save command will duplicate the state. \n2: save States when needed)\nYOUR CHOICE >>  ";
    std::cin >> backupType;

    if (backupType == "1")
    {
        mediator.setAutoSave(true);
    }
    else if (backupType == "2")
    {
        mediator.setAutoSave(false);
    }
    else
    {
        std::cout << "Invalid selection." <<std::endl ;
        std::cout << "The default is >> to save all States." << std::endl;
        mediator.setAutoSave(true);
    }

    std::cout << "-----------------------------------------------------------------------"<< std::endl;

    mediator.run();

    std::cout << "-----------------------------------------------------------------------"<< std::endl;
    std::cout << "Last Emotion: " << mediator.getCurrentEmotion() << std::endl;
    std::cout << "Last Quote: " << mediator.getCurrentQuote() << std::endl;
    std::cout << "-----------------------------------------------------------------------"<< std::endl;
    return 0;
}

void Welcome ()
{
    std::cout <<"///////////////////////////////////////////////////////////////////////" << std::endl;
    std::cout <<"//////////////         Random Quote generator          ////////////////" << std::endl;
    std::cout <<"///////////////////////////////////////////////////////////////////////" << std::endl;
}