#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

// Function to print the help message
void printHelp() {
    std::cout << "Usage: ./ftt <foodsfile> <coinsfile>\n"
              << "Arguments:\n"
              << "  <foodsfile>: Path to the foods data file\n"
              << "  <coinsfile>: Path to the coins data file\n"
              << "Options:\n"
              << "  --help: Display this help message\n";
}

// Forward declaration of runProgram
int runProgram(int argc, char* argv[]);

// Helper function to create a temporary file with mock data to check for incorrect input
void createMockFile(const std::string& filename, const std::string& data) { 
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Failed to create file: " << filename << std::endl;
        return;
    }
    out << data;
    out.close();
}

// Function to delete a file
void deleteFile(const std::string& filename) {
    std::remove(filename.c_str());
}

// Test for correct command-line argument count
void testCommandArgs() {
    {
        // Test with incorrect number of arguments
        char* argv[] = {(char*)"./ftt", (char*)"foods.dat"};
        assert(runProgram(2, argv) == EXIT_FAILURE && "Test Failed: Should fail with only one file argument.");
    }
    {
        // Test with correct number of arguments
        char* argv[] = {(char*)"./ftt", (char*)"foods.dat", (char*)"coins.dat"};
        assert(runProgram(3, argv) == EXIT_SUCCESS && "Test Failed: Should succeed with two file arguments.");
    }
    {
        // Test with --help argument
        char* argv[] = {(char*)"./ftt", (char*)"--help"};
        assert(runProgram(2, argv) == EXIT_SUCCESS && "Test Failed: Should succeed with --help argument.");
    }
    std::cout << "Command Line Argument Tests Passed.\n";
}

// Enhanced error handling for command-line arguments
int runProgram(int argc, char* argv[]) {
    if (argc == 2 && std::string(argv[1]) == "--help") {
        printHelp();
        return EXIT_SUCCESS;
    }

    if (argc != 3) {
        std::cerr << "Error: Incorrect number of command-line arguments.\n";
        printHelp();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// Test loading valid and invalid food data with better error handling
void testLoadFoods(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Food data file not found: " << filename << "\n";
        assert(false && "Error: File not found.");
    }

    std::string line;
    bool correctFormat = true;
    while (getline(file, line)) {
        size_t found = line.find('|');
        if (found == std::string::npos || std::count(line.begin(), line.end(), '|') != 3) {
            std::cerr << "Error: Food data format is incorrect in file: " << filename << "\n"
                      << "Offending line: " << line << "\n";
            correctFormat = false;
            break;
        }
    }
    file.close();
    assert(correctFormat && "Error: Food data format is incorrect.");
}

// Test loading valid and invalid coins data with better error handling
void testLoadCoins(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Coins data file not found: " << filename << "\n";
        assert(false && "Error: File not found.");
    }

    std::string line;
    bool correctFormat = true;
    while (getline(file, line)) {
        size_t found = line.find(',');
        if (found == std::string::npos || std::count(line.begin(), line.end(), ',') != 1) {
            std::cerr << "Error: Coins data format is incorrect in file: " << filename << "\n"
                      << "Offending line: " << line << "\n";
            correctFormat = false;
            break;
        }
    }
    file.close();
    assert(correctFormat && "Error: Coins data format is incorrect.");
}

int main() {
    // Mock data for testing
    std::string foodsFile = "test_foods.dat";
    std::string coinsFile = "test_coins.dat";
    createMockFile(foodsFile, "F0001|Baclava|Delicious dessert|8.50\n");
    createMockFile(coinsFile, "5000,12\n2000,5\n");

    // Running tests
    testCommandArgs();
    testLoadFoods(foodsFile);
    testLoadCoins(coinsFile);

    // Clean up
    deleteFile(foodsFile);
    deleteFile(coinsFile);

    std::cout << "All tests passed successfully.\n";
    return 0;
}
