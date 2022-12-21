

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

//Checks if user input is one of the available options and returns option index
int validateSelection(std::string selection, std::vector<std::string> selectionOptions)
{
    
    for (int i = 0; i < int(selectionOptions.size()); i++) {
        if(toLowerCase(selection) == toLowerCase(selectionOptions[i])) {
            return i;
        }
    }
    // selection does not occur in options --> return false
    return -1;
}

int askQuestion(std::string question, std::vector<std::string> options, bool allowEmpty, unsigned int max)

{

    std::cout << question << std::endl; //print question to console
    std::cout << "Options are:\n" << std::endl;

    for (auto i = options.begin(); i != options.end(); ++i) { //iterate through options
        std::cout << *i << std::endl; //print options to console
    }
    std::cout << std::endl;

    std::string result;
    bool isError = true; //initialize error to true to stay in while loop

    while (isError) {
        std::getline(std::cin, result); //get user input

        if (!allowEmpty && result == "") {
            std::cout << "Value cannot be empty" << "\n" << std::endl;
        } else if (result.length() > max) {
            std::cout << "Value cannot be longer than " << max << " characters" << "\n" << std::endl;
        } 
            if (validateSelection(result, options) != -1) { //if no error of above type then validate answer
                return validateSelection(result, options); //return answer if validated
            } else {
                std::cout << "Not a valid option\n" << std::endl;
            }
    } //while (isError)
    return -1; //should never be reached
}

float askQuestion(std::string question, float min, float max)
{
    std::cout << question << std::endl; //print question to console

    std::string result;

    float value;
    bool isError = true;

    while (isError) {
        std::getline(std::cin, result); //get user input
        try {
            value = stof(result); //check if string can be converted to float
        
            if(value < min) {
                std::cout << "Value must be at least " << min << "\n" << std::endl;
            } else if (value > max) {
                std::cout << "Value must be lower than " << max << "\n" <<std::endl;
            } else {
                return value; //return value if value is between range
            }
        } catch (const std::exception& e) {
            std::cout << "Value must be a number\n" << std::endl;
        }
    }
    return -1; //should never be reached
}

bool askQuestion(std::string question)
{
    std::string trueOptions[8] = {"y", "Y", "yes", "ja",  "j", "true",  "True",  "TRUE"};

    std::string falseOptions[8] = {"n", "N", "no",  "nee", "n", "false", "False", "FALSE"};

    std::cout << question << std::endl; //print question to console

    std::string result;
    bool value;
    bool isError = true;

    while (isError) {
        std::getline(std::cin, result); //get user input

        if (std::find(std::begin(trueOptions), std::end(trueOptions), result) != std::end(trueOptions))
        {
            value = true;
            return value;
        } else if (std::find(std::begin(falseOptions), std::end(falseOptions), result) != std::end(falseOptions)) {
            value = false;
            return value;
        } else {
            std::cout << "Invalid input\n" << std::endl;
        }
    } //while (isError)
    return false; //should never be reached
}