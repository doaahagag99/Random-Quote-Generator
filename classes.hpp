/**
 * @file classes.hpp
 * @author Doaa Hagag (doaahagag128@gmail.com)
 * @brief  this file contains the declarations of the classes and their member functions.
 * @version 0.1
 * @date 2024-05-26
 */

#ifndef CLASSES_HPP
#define CLASSES_HPP
/********************************************************************************************
 *                             Include  Libraries
 ********************************************************************************************/
#include <iostream> // for input/output
#include <fstream>  // for file handling
#include <string>   // for string and container operations
#include <vector>   // for vector
#include <map>      // for map
#include <memory>   // for smart pointers
#include <cstdlib>  // for srand() and rand()
#include <ctime>    // for time()

/**********************************************************************************************
 * @brief This Class to store the current Quotes.
 * (Memento) Design Patern.
 * ********************************************************************************************/
class QuoteMemento
{
private:
    std::string quote;

public:
    QuoteMemento(std::string cp_quote);
    std::string getQuote();
};

/**********************************************************************************************
 * @brief This Class stores the current emotion.
 * (Memento) Design Patern.
 **********************************************************************************************/
class EmotionMemento
{
private:
    std::string emotion;

public:
    EmotionMemento(std::string cp_emotion);
    std::string getEmotion();
};

/** ********************************************************************************************
 * @brief This Class manages the saving and restoring mementos. (Memento) Design Pattern
 * This class manages the storage and retrieval of mementos, respectively
 * It provides methods to save and undo the state of quotes and emotions.
 * It stores mementos (states) of quotes and emotions in vectors.
 * ********************************************************************************************/
class QuoteCaretaker
{
private:
    std::vector<std::shared_ptr<QuoteMemento>> quoteHistory;
    std::vector<std::shared_ptr<EmotionMemento>> emotionHistory;

public:
    void saveQuote(std::shared_ptr<QuoteMemento> memento);
    std::shared_ptr<QuoteMemento> undoQuote();
    void saveEmotion(std::shared_ptr<EmotionMemento> memento);
    std::shared_ptr<EmotionMemento> undoEmotion();
    bool isQuoteHistoryEmpty();
    bool isEmotionHistoryEmpty();
};

/**********************************************************************************************
 * @brief class manages the quote system and user interaction (Mediator) Design Pattern
 *        it is the orginator for the memento Design pattern.
 * The QuoteMediator class handles:
 *     1) Loading quotes from files based on the user's emotion(user input).
 *     2) Displaying a random quote from the opposite emotion category.
 *     3) Saving and undoing quotes and emotions using the QuoteCaretaker.
 * The user interacts without needing to know the internal details of quote management.
 **********************************************************************************************/
class QuoteMediator
{
private:
    std::map<std::string, std::string> fileMapping;
    std::shared_ptr<QuoteCaretaker> caretaker;
    std::string currentEmotion;
    std::string currentQuote;
    bool autoSave;

    std::vector<std::string> loadQuotesFromFile(const std::string &filename);

public:
    QuoteMediator();
    void setAutoSave(bool value);
    void displayQuote(const std::string &emotion);
    void saveState();
    void undoState();
    std::string getOppositeEmotion(const std::string &emotion);
    void run();
    std::string getCurrentEmotion();
    std::string getCurrentQuote();
};

#endif // CLASSES_HPP
