
#include <iostream>
#include <string>
#include <cmath>
using namespace std;


// Enumeration: enGameChoice
// Purpose: Defines the choices available in the game.
enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };

// Enumeration: enWinner
// Purpose: Defines possible winners for a round or game.

enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

// Structure: stRoundInfo
// Purpose: Stores details of a single round of the game.
struct stRoundInfo
{
    short RoundNumber = 0;          // Round number.
    enGameChoice Player1Choice;     // Player's choice.
    enGameChoice ComputerChoice;    // Computer's choice.
    enWinner Winner;                // Stores the winner of the round.
    string WinnerName="";               // Stores the winner's name.
};

// Structure: stGameResults
// Purpose: Stores overall game results after all rounds are played.
struct stGameResults
{
    short GameRounds = 0;        // Number of rounds played.
    short Player1WinTimes = 0;   // Count of Player1's wins.
    short ComputerWinTimes = 0;  // Count of Computer's wins.
    short DrawTimes = 0;         // Number of rounds that ended in a draw.
    enWinner GameWinner;         // Stores the overall game winner.
    string WinnerName = "";      // Name of the game winner.
};

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

// Function: GetComputerChoice
// Purpose: Randomly selects the computer's choice.
// Returns: An enGameChoice value representing the computer's move.
enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandomNumber(1, 3);
}

// Function: WhoWonTheRound
// Purpose: Determines the winner of a round based on player and computer choices.
enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    // If both choices are the same, it's a draw.
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
        return enWinner::Draw;

    // Determine the winner based on game rules.
    switch (RoundInfo.Player1Choice)
    {
    case enGameChoice::Stone:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoice::Stone)
        {
            return enWinner::Computer;
        }
    }
    return enWinner::Player1;
}

// Function: WhoWonTheGame


string ChoiceName(enGameChoice Choice)
{
    string arrGameChoices[3] = { "Stone", "Paper", "Scissors" };
    return arrGameChoices[Choice - 1];
}

string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] = { "Player1", "Computer", "No Winner (Draw)" };
    return arrWinnerName[Winner - 1];
}


enGameChoice ReadPlayer1Choice()
{
    short Choice;
    do
    {
        cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);
    return (enGameChoice)Choice;
}

void SetWinnerScreenColor(enWinner Winner)
{
    switch (Winner)
    {
    case enWinner::Player1:
       system("color 2F");
       break;
    case enWinner::Computer:
        system("color 4F");
        cout << "\a";
        break;
    default:
        system("color 6F");
        break;
    }

}


void PrintRoundResults(stRoundInfo RoundInfo)
{
    cout << "\n____________ Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
    cout << "Player1 Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
    cout << "_________________________________________\n" << endl;

    SetWinnerScreenColor(RoundInfo.Winner);
}

enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes);

stGameResults FillGameResults(short GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{

    stGameResults GameResults;
    GameResults.GameRounds = GameRounds;
    GameResults.Player1WinTimes = Player1WinTimes;
    GameResults.ComputerWinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;
}

enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
    if (Player1WinTimes > ComputerWinTimes) return enWinner::Player1;
    else if (ComputerWinTimes > Player1WinTimes) return enWinner::Computer;
    else return enWinner::Draw;
}

stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
        cout << "\nRound [" << GameRound << "] begins:\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Player1)
            Player1WinTimes++;
        else if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;

        PrintRoundResults(RoundInfo);
    }

    return FillGameResults(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);
}

string Tabs(short NumberOfTabs)
{
    string t = "";
    for (int i = 1; i < NumberOfTabs; i++)
    {
        t = t + "\t";
        cout << t;
    }
    return t;
}

void ShowGameOverScreen()
{
    cout << Tabs(2) << "--------------------------------------\n\n";
    cout << Tabs(2) << "                +++ G a m e  O v e r +++\n";
    cout << Tabs(2) << "--------------------------------------\n\n";
}

void ShowFinalGameResult(stGameResults GameResult)
{
    cout << Tabs(2) << "___________________ [Game Result ]_____________________\n\n";
    cout << Tabs(2) << "Game Round          : " << GameResult.GameRounds << endl;
    cout << Tabs(2) << "Player1 won times   : " << GameResult.Player1WinTimes << endl;
    cout << Tabs(2) << "Computer won times  : " << GameResult.ComputerWinTimes << endl;
    cout << Tabs(2) << "Draw times          : " << GameResult.DrawTimes << endl;
    cout << Tabs(2) << "Fianal Winner       : " << GameResult.WinnerName << endl;
    cout << Tabs(2) << "____________________________________________________________\n";
    SetWinnerScreenColor(GameResult.GameWinner);
}

short ReadHowManyRounds()
{
    short GameRounds = 1;
    do
    {
        cout << "How Many Round 1 to 10 \n";
        cin >> GameRounds;
    } while (GameRounds < 1 || GameRounds>10);
    return GameRounds;
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRounds()); // Play 3 rounds.
        //cout << "\nGame Over! Winner: " << GameResults.WinnerName << endl;
        ShowGameOverScreen();
        ShowFinalGameResult(GameResults);
          cout << endl << Tabs(3) << "Do you want to play again? Y/N?";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));	
	StartGame();
	


	return 0;
}

