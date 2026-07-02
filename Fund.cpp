#include <iostream>
#include <string>
#include <limits>   // Added back for secure buffer purging
#include <unistd.h> // for sleep()

using namespace std;

// ==========================================
// ANSI Color Codes for terminal styling
// ==========================================
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define BOLD "\033[1m"
#define RESET "\033[0m"

// ==========================================
// Loading animation
// ==========================================
void loadingAnimation(string message)
{
    cout << message;
    for (int i = 0; i < 3; i++)
    {
        cout << ".";
        cout.flush();
        sleep(1);
    }
    cout << "\n";
}

// ==========================================
// Display star rating
// ==========================================
void displayStars(int stars)
{
    cout << "Stars: ";
    for (int i = 0; i < stars; i++)
        cout << YELLOW << "*" << RESET;
    for (int i = stars; i < 5; i++)
        cout << "-";
    cout << "\n";
}

// ==========================================
// Check if movie already in watchlist
// ==========================================
bool isDuplicate(string watchlist[], int count, string movieName)
{
    for (int i = 0; i < count; i++)
    {
        if (watchlist[i] == movieName)
            return true;
    }
    return false;
}

// ==========================================
// Display watchlist
// ==========================================
void displayWatchlist(string watchlist[], int count)
{
    cout << BOLD << CYAN;
    cout << "\n==========================================\n";
    cout << "           YOUR WATCHLIST                 \n";
    cout << "==========================================\n"
         << RESET;

    if (count == 0)
    {
        cout << RED << "No movies in your watchlist.\n"
             << RESET;
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            cout << GREEN << i + 1 << ". " << watchlist[i] << "\n"
                 << RESET;
        }
    }
}

// ==========================================
// Remove movie from watchlist
// ==========================================
int removeFromWatchlist(string watchlist[], int count)
{
    if (count == 0)
    {
        cout << RED << "Your watchlist is empty!\n"
             << RESET;
        return count;
    }

    displayWatchlist(watchlist, count);

    int removeChoice;
    cout << "\nEnter movie number to remove (0 to cancel): ";

    while (!(cin >> removeChoice))
    {
        cout << RED << "Invalid entry. Enter a valid list number: " << RESET;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (removeChoice <= 0 || removeChoice > count)
    {
        cout << YELLOW << "No changes made.\n"
             << RESET;
        return count;
    }

    // Shift elements left to fill the gap
    for (int i = removeChoice - 1; i < count - 1; i++)
    {
        watchlist[i] = watchlist[i + 1];
    }
    count--;

    cout << GREEN << "Movie removed from watchlist!\n"
         << RESET;
    return count;
}

// ==========================================
// MAIN PROGRAM
// ==========================================
int main()
{
    string name;
    int age;
    int choice;
    char again;

    // Watchlist storage
    string watchlist[20];
    int watchlistCount = 0;

    // Session tracking
    int totalRecommendations = 0;
    int genresExplored[5] = {0}; // track which genres were visited

    // ==========================================
    // ASCII Art Netflix Logo
    // ==========================================
    cout << RED << BOLD;
    cout << " ##  ##  #####  ######  #####  ##     ##  ##  ##\n";
    cout << " ### ##  ##       ##    ##     ##     ##  ####\n";
    cout << " ## ###  #####    ##    #####  ##     ##    ##\n";
    cout << " ##  ##  ##       ##    ##     ##     ##  ####\n";
    cout << " ##  ##  #####    ##    ##     #####  ##  ##  ##\n";
    cout << RESET;

    cout << BOLD << CYAN;
    cout << "==========================================\n";
    cout << "    NETFLIX MOVIE RECOMMENDATION SYSTEM  \n";
    cout << "==========================================\n"
         << RESET;

    // Loading animation
    loadingAnimation("Initializing");

    // ==========================================
    // Get user details
    // ==========================================
    cout << "\nEnter your name: ";
    getline(cin, name);

    cout << "Enter your age: ";
    while (!(cin >> age) || age < 0)
    {
        cout << RED << "Invalid age tracking metric. Enter a number: " << RESET;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // ==========================================
    // Main recommendation loop
    // ==========================================
    do
    {
        bool movieRecommended = false;
        string movieName;
        int movieStars = 0;
        int movieMinAge = 0;

        cout << BOLD << YELLOW;
        cout << "\n==========================================\n";
        cout << "  Welcome, " << name << "!\n";
        cout << "==========================================\n"
             << RESET;

        // ==========================================
        // Genre menu
        // ==========================================
        cout << CYAN << "\nSelect a Genre:\n"
             << RESET;
        cout << "  1. " << RED << "Action" << RESET << "  (Age: 16+)\n";
        cout << "  2. " << GREEN << "Comedy" << RESET << "  (Age: 13+)\n";
        cout << "  3. " << YELLOW << "Horror" << RESET << "  (Age: 18+)\n";
        cout << "  4. " << CYAN << "Romance" << RESET << "  (Age: 13+)\n";
        cout << "  5. " << WHITE << "Sci-Fi" << RESET << "  (Age: 13+)\n";
        cout << "  6. " << YELLOW << "Manage Watchlist\n"
             << RESET;
        cout << "\nChoice: ";

        while (!(cin >> choice))
        {
            cout << RED << "Please select a number (1-6): " << RESET;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "\n==========================================\n";

        // ==========================================
        // Genre switch with age restrictions
        // ==========================================
        switch (choice)
        {
        case 1: // Action
            movieMinAge = 16;
            if (age < movieMinAge)
            {
                cout << RED << "Sorry! Action movies require age 16+. You are " << age << ".\n"
                     << RESET;
            }
            else
            {
                movieName = "Extraction";
                movieStars = 4;
                movieRecommended = true;
                genresExplored[0]++;

                cout << BOLD << "Recommended Movie: " << RED << movieName << RESET << "\n";
                cout << "Rating: 16+ | Genre: Action\n";
                displayStars(movieStars);
                cout << "Description: A mercenary embarks on a dangerous rescue mission\n";
                cout << "             in the heart of Bangladesh.\n";
            }
            break;

        case 2: // Comedy
            movieMinAge = 13;
            if (age < movieMinAge)
            {
                cout << RED << "Sorry! Comedy movies require age 13+. You are " << age << ".\n"
                     << RESET;
            }
            else
            {
                movieName = "Murder Mystery";
                movieStars = 4;
                movieRecommended = true;
                genresExplored[1]++;

                cout << BOLD << "Recommended Movie: " << GREEN << movieName << RESET << "\n";
                cout << "Rating: PG-13 | Genre: Comedy\n";
                displayStars(movieStars);
                cout << "Description: A couple gets entangled in a hilarious crime\n";
                cout << "             investigation aboard a luxury yacht.\n";
            }
            break;

        case 3: // Horror
            movieMinAge = 18;
            if (age < movieMinAge)
            {
                cout << RED << "Sorry! Horror movies require age 18+. You are " << age << ".\n"
                     << RESET;
            }
            else
            {
                movieName = "Bird Box";
                movieStars = 5;
                movieRecommended = true;
                genresExplored[2]++;

                cout << BOLD << "Recommended Movie: " << YELLOW << movieName << RESET << "\n";
                cout << "Rating: 18+ | Genre: Horror\n";
                displayStars(movieStars);
                cout << "Description: Survivors must navigate blindfolded against\n";
                cout << "             a mysterious supernatural force.\n";
            }
            break;

		case 4: // Romance
            movieMinAge = 13;
            if (age < movieMinAge)
            {
                cout << RED << "Sorry! Romance movies require age 13+. You are " << age << ".\n"
                     << RESET;
            }
            else
            {
                movieName = "Purple Hearts";
                movieStars = 4;
                movieRecommended = true;
                genresExplored[3]++;

                cout << BOLD << "Recommended Movie: " << CYAN << movieName << RESET << "\n";
                cout << "Rating: PG-13 | Genre: Romance\n";
                displayStars(movieStars);
                cout << "Description: A musician and a soldier form an unexpected bond\n";
                cout << "             in a marriage of convenience.\n";
            }
            break;

        default:
            cout << RED << "Invalid choice! Please choose between 1 and 6.\n"
                 << RESET;
        }

        cout << "==========================================\n";

        // ==========================================
        // Watchlist add logic (with duplicate check)
        // ==========================================
        if (movieRecommended)
        {
            totalRecommendations++;
            char watchChoice;

            cout << "\nAdd " << BOLD << movieName << RESET << " to watchlist? (Y/N): ";
            cin >> watchChoice;

            if (watchChoice == 'Y' || watchChoice == 'y')
            {
                if (isDuplicate(watchlist, watchlistCount, movieName))
                {
                    cout << YELLOW << "\"" << movieName << "\" is already in your watchlist!\n"
                         << RESET;
                }
                else if (watchlistCount >= 20)
                {
                    cout << RED << "Watchlist is full! Remove a movie first.\n"
                         << RESET;
                }
                else
                {
                    watchlist[watchlistCount] = movieName;
                    watchlistCount++;
                    cout << GREEN << "\"" << movieName << "\" added to your watchlist!\n"
                         << RESET;
                }
            }
            else
            {
                cout << YELLOW << "Movie not added.\n"
                     << RESET;
            }
        }

        cout << "\nWould you like to return to the main menu? (Y/N): ";
        cin >> again;

        // Clear the stream buffer to avoid menu lock up trailing from previous iterations
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (again == 'Y' || again == 'y');

    // ==========================================
    // Final watchlist display
    // ==========================================
    displayWatchlist(watchlist, watchlistCount);

    // ==========================================
    // Session summary
    // ==========================================
    string genreNames[5] = {"Action", "Comedy", "Horror", "Romance", "Sci-Fi"};

    cout << BOLD << CYAN;
    cout << "\n==========================================\n";
    cout << "           SESSION SUMMARY               \n";
    cout << "==========================================\n"
         << RESET;
    cout << "Total recommendations received : " << GREEN << totalRecommendations << RESET << "\n";
    cout << "Total movies in watchlist      : " << GREEN << watchlistCount << RESET << "\n";
    cout << "Genres explored                : ";

    bool anyGenre = false;
    for (int i = 0; i < 5; i++)
    {
        if (genresExplored[i] > 0)
        {
            if (anyGenre)
                cout << ", ";
            cout << CYAN << genreNames[i] << RESET;
            anyGenre = true;
        }
    }
    if (!anyGenre)
        cout << RED << "None" << RESET;
    cout << "\n";

    // ==========================================
    // Goodbye message
    // ==========================================
    loadingAnimation("\nSaving your session");

    cout << BOLD << RED;
    cout << "\n==========================================\n";
    cout << "  Thank you for using Netflix Recommender!\n";
    cout << "  Enjoy your movies, " << name << "!\n";
    cout << "==========================================\n"
         << RESET;

    return 0;
}