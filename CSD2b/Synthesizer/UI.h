#pragma once

        bool validateSelection(std::string selection, std::vector<std::string> selectionOptions);
        
        //Check if user input occurs inside the options, if so return input, else ask question again.
        //
        //question: Question to be asked
        //options: list of valide options
        //allowEmpty: if true allows empty input
        //max: sets maximum string length
        std::string askQuestion(std::string question, std::vector<std::string> options, bool allowEmpty, unsigned int max);

        float askQuestion(std::string question, float min, float max);
        bool askQuestion(std::string question);