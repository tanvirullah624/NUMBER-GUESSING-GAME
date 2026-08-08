#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

// Check Perfect Square
bool isPerfectSquare(int number)
{
    int root = sqrt(number);
    return root * root == number;
}
// Calculate Digit Sum
int digitSum(int number)
{
    int sum = 0;
    while (number > 0)
    {
        sum += number % 10;
        number /= 10;
    }

    return sum;
}
// Check Already Guessed

bool alreadyGuessed(const vector<int>& guesses, int number)
{
    for (int value : guesses)
    {
        if (value == number)
        {
            return true;
        }
    }
    return false;
}

// Give Hint
void giveHint(int secretNumber, int maxNumber)
{
    int hintType = rand() % 5;

    cout << "\n Hint: ";

    // Hint 1: Even / Odd
    if (hintType == 0)
    {
        if (secretNumber % 2 == 0)
        {
            cout << "The number is even.\n";
        }
        else
        {
            cout << "The number is odd.\n";
        }
    }

    // Hint 2: Multiple
    else if (hintType == 1)
    {
        if (secretNumber % 5 == 0)
        {
            cout << "The number is a multiple of 5.\n";
        }
        else if (secretNumber % 3 == 0)
        {
            cout << "The number is a multiple of 3.\n";
        }
        else if (secretNumber % 2 == 0)
        {
            cout << "The number is a multiple of 2.\n";
        }
        else
        {
            cout << "The number is not a multiple of 2, 3, or 5.\n";
        }
    }

    // Hint 3: Perfect Square
    else if (hintType == 2)
    {
        if (isPerfectSquare(secretNumber))
        {
            cout << "The number is a perfect square.\n";
        }
        else
        {
            cout << "The number is not a perfect square.\n";
        }
    }

    // Hint 4: Range
    else if (hintType == 3)
    {
        int range = maxNumber / 5;

        int lower = secretNumber - range;
        int upper = secretNumber + range;

        if (lower < 1)
        {
            lower = 1;
        }

        if (upper > maxNumber)
        {
            upper = maxNumber;
        }

        cout << "The number is between "
             << lower << " and " << upper << ".\n";
    }

    // Hint 5: Digit Sum
    else
    {
        cout << "The sum of the digits is "
             << digitSum(secretNumber) << ".\n";
    }
}



// Play Game
void playGame()
{
    int choice;
    int maxNumber;
    int maxAttempts;

    cout << "\n";
    cout << "====================================\n";
    cout << "       NUMBER GUESSING GAME\n";
    cout << "====================================\n";

    cout << "\nChoose Difficulty:\n";

    cout << "1. Easy   (1 - 50)\n";
    cout << "2. Medium (1 - 100)\n";
    cout << "3. Hard   (1 - 500)\n";

    cout << "\nEnter your choice: ";
    cin >> choice;

    // Input Validation
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );
        cout << "\n Invalid input!\n";
        return;
    }
   
    // Difficulty
    if (choice == 1)
    {
        maxNumber = 50;
        maxAttempts = 10;
    }
    else if (choice == 2)
    {
        maxNumber = 100;
        maxAttempts = 7;
    }
    else if (choice == 3)
    {
        maxNumber = 500;
        maxAttempts = 10;
    }
    else
    {
        cout << "\n Invalid difficulty choice!\n";

        return;
    }

    // Generate Random Number
    int secretNumber =
        rand() % maxNumber + 1;

    // Store previous guesses
    vector<int> guesses;
    int guess;
    int attempts = 0;
    bool correct = false;
    cout << "\n------------------------------------\n";
    cout << "I have selected a number between 1 and "
         << maxNumber << ".\n";
    cout << "You have "
         << maxAttempts
         << " attempts.\n";
    cout << "------------------------------------\n";

    // Main Game Loop
    while (attempts < maxAttempts)
    {
        cout << "\nEnter your guess: ";

        cin >> guess;
        // Check Invalid Input
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );
            cout << "\n Please enter a valid number.\n";

            continue;
        }
        // Check Range
        if (guess < 1 || guess > maxNumber)
        {
            cout << "\n Please enter a number between 1 and "
                 << maxNumber << ".\n";
            continue;
        }
        // Check Duplicate Guess
        if (alreadyGuessed(guesses, guess))
        {
            cout << "\n You already guessed "
                 << guess << "!\n";
            cout << "Please enter a different number.\n";
            // Duplicate guess does NOT
            // consume an attempt.
            continue;
        }
        // Save new guess
        guesses.push_back(guess);
        attempts++;
        
        // Correct Guess
        if (guess == secretNumber)
        {
            correct = true;
            int score =
                (maxAttempts - attempts + 1) * 10;
            // Bonus for very quick answer
            if (attempts <= 2)
            {
                score += 20;
            }
            cout << "\n";
            cout << "====================================\n";
            cout << "          CONGRATULATIONS!\n";
            cout << "====================================\n";

            cout << "You guessed the correct number!\n";

            cout << "Correct Number: "
                 << secretNumber << endl;

            cout << "Attempts Used: "
                 << attempts << endl;

            cout << "Your Score: "
                 << score << endl;

            break;
        }
        // Wrong Guess
        if (guess < secretNumber)
        {
            cout << "\nWrong! Too Low!\n";
        }
        else
        {
            cout << "\nWrong! Too High!\n";
        }
        cout << "Attempts Remaining: "
             << maxAttempts - attempts
             << endl;
        // Ask for Hint
        char hintChoice;
        cout << "\nDo you want a hint? (Y/N): ";
        cin >> hintChoice;
        if (hintChoice == 'Y' ||
            hintChoice == 'y')
        {
            giveHint(
                secretNumber,
                maxNumber
            );
        }
        else if (hintChoice == 'N' ||
                 hintChoice == 'n')
        {
            cout << "Okay, no hint.\n";
        }
        else
        {
            cout << "Invalid choice. No hint given.\n";
        }
    }
    // Game Over
    if (!correct)
    {
        cout << "\n";
        cout << "====================================\n";
        cout << "            GAME OVER \n";
        cout << "====================================\n";
        cout << "You used all your attempts.\n";
        cout << "The correct number was: "
             << secretNumber << endl;
    }
}
// Main Function
int main()
{
    // Initialize random number generator
    srand(time(0));
    char playAgain;
    // Play Again Loop
    do
    {
        playGame();
        cout << "\nDo you want to play again? (Y/N): ";
        cin >> playAgain;
    }
    while (
        playAgain == 'Y' ||
        playAgain == 'y'
    );
    cout << "\n====================================\n";
    cout << "       Thanks for playing! \n";
    cout << "====================================\n";
    return 0;
}
