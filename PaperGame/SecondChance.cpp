#include "header.h"

enum enGameChoice
{
  Stone = 1,
  Paper = 2,
  Scissors = 3,
};
enum enWinner
{
  Player = 1,
  Computer = 2,
  Draw = 3,
};
struct stRoundInfo
{
  short RoundNumber = 0;
  enGameChoice Player1Choice;
  enGameChoice ComputerChoice;
  enWinner RoundWinner;
  string WinnerName;
};
struct stGameResult
{
  short GameRoundsNumber = 0;
  short Player1WonTimes = 0;
  short ComputerWonTimes = 0;
  short DrawTimes = 0;
  enWinner GameWinner;
  string WinnerName;
};

int RandomNumber(int From, int To)
{
  int randomNum = rand() % (To - From + 1) + From;
  return randomNum;
}
string WinnerName(enWinner Winner)
{
  string arrWinnerNames[3] = {"Player1", "Computer", "No One"};
  return (arrWinnerNames[Winner - 1]);
}
enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
  if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
    return enWinner::Draw;
  switch (RoundInfo.Player1Choice)
  {
  case enGameChoice::Paper:
    if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
      return enWinner::Computer;
    break;
  case enGameChoice::Stone:
    if (RoundInfo.ComputerChoice == enGameChoice::Paper)
      return enWinner::Computer;
    break;
  case enGameChoice::Scissors:
    if (RoundInfo.ComputerChoice == enGameChoice::Stone)
      return enWinner::Computer;
    break;
  }
  return enWinner::Player;
}
string ChoiceName(enGameChoice Choice)
{
  string GameChoices[3] = {"Stone", "Paper", "Scissors"};
  return (GameChoices[Choice - 1]);
}
void SetWinnerScreenColor(enWinner Winner)
{
  if (Winner == enWinner::Player)
    system("color 2F"); // Green
  else if (Winner == enWinner::Computer)
  {
    system("color 4F"); // Red
    cout << "\a";
  }
  else
    system("color 6F"); // Yellow
}

void PrintRoundResult(stRoundInfo RoundInfo)
{
  cout << "________________ Round [" << RoundInfo.RoundNumber << "] ________________\n";
  cout << "Player1  Choice:  " << ChoiceName(RoundInfo.Player1Choice) << endl;
  cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
  cout << "Round Winner   : " << RoundInfo.WinnerName << endl;
  cout << "________________________________________" << endl;
}
enWinner WhoWonTheGame(short Player1WonTimes, short ComputerWonTimes)
{
  if (Player1WonTimes < ComputerWonTimes)
    return enWinner::Computer;
  else if (Player1WonTimes > ComputerWonTimes)
    return enWinner::Player;
  else
    return enWinner::Draw;
}
stGameResult FillGameResult(short GameRoundsNumber, short Player1WonTimes, short ComputerWonTimes, short DrawTimes)
{
  stGameResult GameResults;
  GameResults.GameRoundsNumber = GameRoundsNumber;
  GameResults.Player1WonTimes = Player1WonTimes;
  GameResults.ComputerWonTimes = ComputerWonTimes;
  GameResults.DrawTimes = DrawTimes;
  GameResults.GameWinner = WhoWonTheGame(Player1WonTimes, ComputerWonTimes);
  GameResults.WinnerName = WinnerName(GameResults.GameWinner);
  return GameResults;
}
enGameChoice ReadPlayerChoice()
{
  int Number;
  do
  {
    cout << "Your Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
    cin >> Number;
  } while (Number < 1 || Number > 3);
  return enGameChoice(Number);
}
enGameChoice GetComputerChoice()
{
  return enGameChoice(RandomNumber(1, 3));
}
string Tabes(int Number)
{
  string tabes = "";
  for (int i = 0; i < Number; i++)
    tabes += "\t";
  return tabes;
}
stGameResult PlayGame(short HowManyRounds)
{
  stRoundInfo RoundInfo;
  short Player1WonTimes = 0, ComputerWonTimes, DrawTimes = 0;
  for (short RoundNumber = 1; RoundNumber <= HowManyRounds; RoundNumber++)
  {
    RoundInfo.Player1Choice = ReadPlayerChoice();
    RoundInfo.ComputerChoice = GetComputerChoice();
    RoundInfo.RoundNumber = RoundNumber;
    RoundInfo.RoundWinner = WhoWonTheRound(RoundInfo);
    if (RoundInfo.RoundWinner == enWinner::Player)
      Player1WonTimes++;
    else if (RoundInfo.RoundWinner == enWinner::Computer)
      ComputerWonTimes++;
    else
      DrawTimes++;
    RoundInfo.WinnerName = WinnerName(RoundInfo.RoundWinner);
    PrintRoundResult(RoundInfo);
    SetWinnerScreenColor(RoundInfo.RoundWinner);
  }
  return FillGameResult(HowManyRounds, Player1WonTimes, ComputerWonTimes, DrawTimes);
}
void ShowGameOverScreen()
{
  cout << "\n\n";
  cout << Tabes(2) << "_____________________________________________________\n\n";
  cout << Tabes(4) << "+++ G a m e  O v e r +++\n";
  cout << Tabes(2) << "_____________________________________________________\n\n";
}
void ShowFinalGameResults(stGameResult GameResult)
{
  ShowGameOverScreen();
  cout << Tabes(2) << "________________ [Game Results] ____________________\n\n";
  cout << "Game Rounds          : " << GameResult.GameRoundsNumber << "\n";
  cout << "Player1 won times    : " << GameResult.Player1WonTimes << "\n";
  cout << "Computer won times   : " << GameResult.ComputerWonTimes << "\n";
  cout << "Draw times           : " << GameResult.DrawTimes << "\n";
  cout << "Final Winner         : " << GameResult.WinnerName << "\n";
  cout << Tabes(2) << "_____________________________________________________\n\n";
}
int ReadHowManyRounds()
{
  int Number = 0;
  do
  {
    cout << "How Many Rounds 1 To 10\n";
    cin >> Number;
  } while (Number < 1 || Number > 10);
  return Number;
}
void ResetScreen()
{
  system("cls");
  system("color 0F");
}
void StartGame()
{
  string answer = "";
  do
  {
    ResetScreen();
    ShowFinalGameResults(PlayGame(ReadHowManyRounds()));
    cout << Tabes(2)  << "Do you want to play again? Y / N ?  ";
    cin >> answer;
  } while (answer == "y" || answer == "Y");

}
int main()
{
  StartGame();
  srand((unsigned)time(NULL));

  return 0;
}