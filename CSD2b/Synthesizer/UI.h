#pragma once

        int validateSelection(std::string selection, std::vector<std::string> selectionOptions);
        
        /*Check if user input occurs inside the options, if so return index of selected option, else ask question again.
        
        question: Question to be asked
        options: list of valide options
        allowEmpty: if true allows empty input
        max: sets maximum string length*/
        int askQuestion(std::string question, std::vector<std::string> options, bool allowEmpty, unsigned int max);


        /*Check if value is between range, if so return value, else ask question again.
        
        question: Question to be asked
        min: sets lower bound of range
        max: sets higher bound of range*/
        float askQuestion(std::string question, float min, float max);

        /*Check if question is answered with yes/no, if so return bool state, else ask question again.
        
        question: Question to be askedint*/
        bool askQuestion(std::string question);