#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib> // For random number generation
#include <ctime>   // For seeding the random number generator
#include <string>

// Define the ATM structure
struct ATM {
    // Add the necessary members for your ATM, for example:
    int balance;
    int availableBills[4]; // 20s, 50s, 100s, 200s
};

// Function prototypes
void initializeATM(ATM &atm);
void loadATM(ATM &atm, const std::string &filename);
void saveATM(const ATM &atm, const std::string &filename);
void refillATM(ATM &atm);
void withdrawMoney(ATM &atm);

// Function to read questions from a file
std::vector<std::string> readQuestions(const std::string &filename) {
    std::vector<std::string> questions;
    std::ifstream infile(filename);
    if (infile.is_open()) {
        std::string line;
        while (getline(infile, line)) {
            questions.push_back(line);
        }
        infile.close();
    } else {
        std::cout << "Error opening questions file.\n";
    }
    return questions;
}

// Function to read answers from a file
std::vector<std::string> readAnswers(const std::string &filename) {
    std::vector<std::string> answers;
    std::ifstream infile(filename);
    if (infile.is_open()) {
        std::string line;
        while (getline(infile, line)) {
            answers.push_back(line);
        }
        infile.close();
    } else {
        std::cout << "Error opening answers file.\n";
    }
    return answers;
}

int main() {
    ATM atm;
    initializeATM(atm);

    std::string filename = "atm.bin"; // Binary file for ATM state
    std::string questionsFilename = "questions.txt";
    std::string answersFilename = "answers.txt";

    // Load existing ATM state if file exists
    if (std::ifstream(filename)) {
        loadATM(atm, filename);
        std::cout << "ATM loaded successfully.\n";
        std::cout << "Current ATM state:\n";
        // Display the initial state of the ATM
    } else {
        std::cout << "ATM is empty.\n";
    }

    // Read questions and answers from files
    std::vector<std::string> questions = readQuestions(questionsFilename);
    std::vector<std::string> answers = readAnswers(answersFilename);

    // Main loop for ATM operations
    char operation;
    while (true) {
        std::cout << "Enter operation (+ for refill, - for withdrawal, q to quit): ";
        std::cin >> operation;

        switch (operation) {
            case '+':
                refillATM(atm);
                // Display a question about refilling
                if (!questions.empty()) {
                    std::cout << questions[0] << std::endl; 
                    // Display the corresponding answer
                    if (answers.size() > 0) {
                        std::cout << answers[0] << std::endl;
                    }
                }
                break;
            case '-':
                withdrawMoney(atm);
                // Display a question about withdrawing money
                if (!questions.empty()) {
                    std::cout << questions[1] << std::endl;
                    // Display the corresponding answer
                    if (answers.size() > 1) {
                        std::cout << answers[1] << std::endl;
                    }
                }
                break;
            case 'q':
                saveATM(atm, filename);
                std::cout << "ATM state saved. Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid operation. Please try again.\n";
        }
    }
    std::wcout << L"Возвращайтесь скорее. Пока :-) !" << std::endl;
    return 0;
}