/**
 * @file classes.cpp
 * @author Doaa Hagag (doaahagag128@gmail.com)
 * @brief  this file contains the definitions of the member functions.
 * @version 0.1
 * @date 2024-05-26
 */

#include "classes.hpp"


/***********************************************************************************/
/****************************  QuoteMemento definitions ****************************/
/***********************************************************************************/



QuoteMemento::QuoteMemento(std::string cp_quote) : quote(cp_quote) {}

std::string QuoteMemento::getQuote()
{
    return quote;
}



/***********************************************************************************/
/************************  EmotionMemento definitions  *****************************/
/***********************************************************************************/



EmotionMemento::EmotionMemento(std::string cp_emotion) : emotion(cp_emotion) {}

std::string EmotionMemento::getEmotion()
{
    return emotion;
}



/***********************************************************************************/
/*********************** QuoteCaretaker definitions*********************************/
/***********************************************************************************/




void QuoteCaretaker::saveQuote(std::shared_ptr<QuoteMemento> memento)
{
    quoteHistory.push_back(memento);
}

std::shared_ptr<QuoteMemento> QuoteCaretaker::undoQuote()
{
    if (quoteHistory.empty())
        return nullptr;
    quoteHistory.pop_back();
    if (quoteHistory.empty())
        return nullptr;
    return quoteHistory.back();
}

void QuoteCaretaker::saveEmotion(std::shared_ptr<EmotionMemento> memento)
{
    emotionHistory.push_back(memento);
}

std::shared_ptr<EmotionMemento> QuoteCaretaker::undoEmotion()
{
    if (emotionHistory.empty())
        return nullptr;
    emotionHistory.pop_back();
    if (emotionHistory.empty())
        return nullptr;
    return emotionHistory.back();
}

bool QuoteCaretaker::isQuoteHistoryEmpty()
{
    return quoteHistory.empty();
}

bool QuoteCaretaker::isEmotionHistoryEmpty()
{
    return emotionHistory.empty();
}



/***********************************************************************************/
/*********************** QuoteMediator definitions *********************************/
/***********************************************************************************/


QuoteMediator::QuoteMediator()
{
    caretaker = std::make_shared<QuoteCaretaker>();
    fileMapping = {
        {"happy", "happy.txt"},
        {"sad", "sad.txt"},
        {"angry", "angry.txt"},
        {"calm", "calm.txt"}};
}

void QuoteMediator::setAutoSave(bool value)
{
    autoSave = value;
}

void QuoteMediator::displayQuote(const std::string &emotion)
{
    if (fileMapping.find(emotion) == fileMapping.end())
    {
        std::cout << "Emotion not found!" << std::endl;
        std::cout << "-----------------------------------------------------------------------"<< std::endl;

        return;
    }
    auto quotes = loadQuotesFromFile(fileMapping[emotion]);
    if (quotes.empty())
    {
        std::cout << "No quotes available for this emotion!" << std::endl;
        std::cout << "-----------------------------------------------------------------------"<< std::endl;

        return;
    }
    srand(static_cast<unsigned>(time(0)));
    int randomIndex = rand() % quotes.size();
    std::string selectedQuote = quotes[randomIndex];
    std::cout << "Quote: " << selectedQuote << std::endl;
    std::cout << "-----------------------------------------------------------------------"<< std::endl;

    currentQuote = selectedQuote;

    if (autoSave)
    {
        caretaker->saveQuote(std::make_shared<QuoteMemento>(selectedQuote));
        caretaker->saveEmotion(std::make_shared<EmotionMemento>(currentEmotion));
    }
}

std::vector<std::string> QuoteMediator::loadQuotesFromFile(const std::string &filename)
{
    std::vector<std::string> quotes;
    std::ifstream file(filename);
    std::string line;
    while (getline(file, line))
    {
        quotes.push_back(line);
    }
    file.close();
    return quotes;
}

void QuoteMediator::saveState()
{
    caretaker->saveQuote(std::make_shared<QuoteMemento>(currentQuote));
    caretaker->saveEmotion(std::make_shared<EmotionMemento>(currentEmotion));
    std::cout << "State saved." << std::endl;
    std::cout << "-----------------------------------------------------------------------"<< std::endl;

}

void QuoteMediator::undoState()
{
    auto quoteMemento = caretaker->undoQuote();
    if (quoteMemento)
    {
        std::cout << "Current Quote: " << quoteMemento->getQuote() << std::endl;
        currentQuote = quoteMemento->getQuote();
    }
    else
    {
        std::cout << "No quote to undo!" << std::endl;
    }
    

    auto emotionMemento = caretaker->undoEmotion();
    if (emotionMemento)
    {
        std::cout << "Current Emotion: " << emotionMemento->getEmotion() << std::endl;
        currentEmotion = emotionMemento->getEmotion();
    }
    else
    {
        std::cout << "No emotion to undo!" << std::endl;
    }
    std::cout << "-----------------------------------------------------------------------"<< std::endl;
    
}

std::string QuoteMediator::getOppositeEmotion(const std::string &emotion)
{
    std::map<std::string, std::string> oppositeEmotions = {
        {"happy", "sad"},
        {"sad", "happy"},
        {"angry", "calm"},
        {"calm", "angry"}};
    return oppositeEmotions[emotion]; // it returns empty string if the key doesn't exist in the map
}

void QuoteMediator::run()
{
    std::string command;
    while (true)
    {
        std::cout << "Enter your choice" << std::endl;
        std::cout << "(feeling: happy, sad, angry, calm) \n(command: save, undo, exit)"<<std::endl;
        std::cout << "-----------------------------------------------------------------------"<< std::endl;
        std::cin >> command;
        if (command == "exit")
            break;
        if (command == "undo")
        {
            undoState();
            continue;
        }
        if (command == "save")
        {
            saveState();
            continue;
        }
        if (fileMapping.find(command) != fileMapping.end())
        {
            currentEmotion = command;
            std::string oppositeEmotion = getOppositeEmotion(command);
            if (!oppositeEmotion.empty())
            {
                displayQuote(oppositeEmotion);
            }
        }
        else
        {
            std::cout << "Invalid choice!" << std::endl;
            std::cout << "-----------------------------------------------------------------------"<< std::endl;
        }
    }
}

std::string QuoteMediator::getCurrentEmotion()
{
    if (caretaker->isEmotionHistoryEmpty())
        return "No emotions saved";
    return currentEmotion;
}

std::string QuoteMediator::getCurrentQuote()
{
    if (caretaker->isQuoteHistoryEmpty())
        return "No quotes saved";
    return currentQuote;
}
