#pragma once

class UI {
    public:

        bool validateSelection(std::string selection, std::vector<std::string> selectionOptions);

        std::string askQuestion(std::string question, std::vector<std::string> options, bool allowEmpty, unsigned int max);
        float askQuestion(std::string question, float min, float max);
        bool askQuestion(std::string question);
};