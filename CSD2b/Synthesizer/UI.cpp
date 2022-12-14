

#include <iostream>
#include <algorithm>
#include <string>
#include <array>
#include <vector>

#include "UI.h"

std::string toLowerCase(std::string inputString) {//converts a whole string to lowerCase
    for (uint i = 0; i < inputString.length(); i++) {
        inputString[i] = tolower(inputString[i]);
    }
    return inputString;
}

bool validateSelection(std::string selection, std::vector<std::string> selectionOptions)
{
    
    for (int i = 0; i < int(selectionOptions.size()); i++) {
        if(toLowerCase(selection) == toLowerCase(selectionOptions[i])) {
            return true;
        }
    }
    // selection does not occur in options --> return false
    return false;
}

std::string askQuestion(std::string question, std::vector<std::string> options, bool allowEmpty, unsigned int max)

{

    std::cout << question << std::endl; //print question to console
    std::cout << "Options are:\n" << std::endl;

    for (auto i = options.begin(); i != options.end(); ++i) { //iterate through options
        std::cout << *i << std::endl; 
    }
    std::cout << std::endl;

    std::string result;
    std::getline(std::cin, result); //get user input

    bool isError = false; //initialize error to false

    if (!allowEmpty && result == "") {
        std::cout << "Value cannot be empty" << std::endl;
        isError = true;
    } else if (result.length() > max) {
        std::cout << "Value cannot be longer than " << max << " characters" << std::endl;
        isError = true;
    } 

    if (isError) {
        return askQuestion(question, options, allowEmpty, max); //ask question again if error
    } else {
        if (validateSelection(result, options)) { //if no error of above type then validate answer
            return result; //return answer if validated
        } else {
            std::cout << "Not a valid option" << std::endl;
            return askQuestion(question, options, allowEmpty, max); //ask question again
        }
    }
}

float askQuestion(std::string question, float min, float max)
{
    std::cout << question << std::endl; //print question to console

    std::string result;
    std::getline(std::cin, result); //get user input

    float value;
    
    bool isError = false;
    try {
        value = stof(result);
    
        if(value < min) {
            std::cout << "Value must be at least " << min << std::endl;
            isError = true;
        } else if (value > max) {
            std::cout << "Value must be lower than " << max << std::endl;
            isError = true;
        }
    } catch (const std::exception& e) {
        std::cout << "Value must be a number" << std::endl;
    }
    if (isError) {
        return askQuestion(question, min, max); //ask question again
    }

    return value;
}

bool askQuestion(std::string question)
{
    std::string trueOptions[8] = {"y", "Y", "yes", "ja",  "j", "true",  "True",  "TRUE"};

    std::string falseOptions[8] = {"n", "N", "no",  "nee", "n", "false", "False", "FALSE"};

    std::cout << question << std::endl; //print question to console

    std::string result;
    std::getline(std::cin, result); //get user input

    bool value;

    if (std::find(std::begin(trueOptions), std::end(trueOptions), result) != std::end(trueOptions))
    {
        value = true;
        return value;
    } else if (std::find(std::begin(falseOptions), std::end(falseOptions), result) != std::end(falseOptions)) {
        value = false;
        return value;
    } else {
        std::cout << "Invalid input" << std::endl;
        return askQuestion(question);
    }
}