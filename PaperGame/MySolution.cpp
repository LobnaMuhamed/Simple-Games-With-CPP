#include "header.h"

// Stone - Paper - Scissor
enum enTool
{
  Stone = 1,
  Paper = 2,
  Scissor = 3,
  DrawTool = 4,
};

enum enPlayer
{
  User = 0,
  Computer = 1,
  Draw = 2,
};

struct stPlayer
{
  enPlayer Player;
  enTool Choice;
};

int ReadPositiveNumber(string Message, int From, int To)
{
  int Number = 0;
  do
  {
    cout << Message << endl;
    cin >> Number;
  } while (Number < From || Number > To);
  return Number;
}

int RandomNumber(int From, int To)
{
  int randomNum = rand() % (To - From + 1) - From;
  return randomNum;
}

enTool PlayerChoice()
{
  int Num = 0;
  do
  {
    cout << "Your Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
    cin >> Num;
  } while (Num <= 0);
  return (enTool)Num;
}

enTool ComputerChoice()
{
  int Num = RandomNumber(1, 3);
  return (enTool)Num;
}

enTool CompareTools(enTool choice1, enTool choice2)
{
  if ((choice1 == enTool::Paper && choice2 == enTool::Stone) || (choice1 == enTool::Stone && choice2 == enTool::Paper))
    return enTool::Paper;
  else if ((choice1 == enTool::Stone && choice2 == enTool::Scissor) || (choice1 == enTool::Scissor && choice2 == enTool::Stone))
    return enTool::Stone;
  else if ((choice1 == enTool::Paper && choice2 == enTool::Scissor) || (choice1 == enTool::Scissor && choice2 == enTool::Paper))
    return enTool::Scissor;
  else
    return enTool::DrawTool;
}
string ChoiceMenu(enTool choice)
{
  switch (choice)
  {
  case enTool::Stone:
    return "Stone";
  case enTool::Paper:
    return "Paper";
  case enTool::Scissor:
    return "Scissor";
  default:
    return "Invalid Tool";
  }
}
string PlayerMenu(enPlayer player)
{
  switch (player)
  {
  case enPlayer::User:
    return "Player1";
  case enPlayer::Computer:
    return "Computer";
  case enPlayer::Draw:
    return "No One";
  default:
    return "No One :)";
  }
}
void ShowDetails(enTool UserChoice, enTool ComputerChoice, enPlayer Winner)
{
  cout << "Player1 Choice: " << ChoiceMenu(UserChoice) << endl;
  cout << "Computer Choice: " << ChoiceMenu(ComputerChoice) << endl;
  cout << "Round Winner: [ " << PlayerMenu(Winner) << " ]" << endl;
  if (Winner == enPlayer::User)
    system("color 2F"); // Green
  else if (Winner == enPlayer::Computer)
    system("color 4F"); // Red
  else
    system("color 6F"); // Yellow
}

void CheckResult(stPlayer User, stPlayer Computer)
{
  User.Choice = PlayerChoice();
  Computer.Choice = ComputerChoice();
  enTool Tool = CompareTools(User.Choice, Computer.Choice);
  if (User.Choice == Tool)
  {
    User.Player = enPlayer::User;
    ShowDetails(User.Choice, Computer.Choice, User.Player);
  }
  else if (Computer.Choice == Tool)
  {
    Computer.Player = enPlayer::Computer;
    ShowDetails(User.Choice, Computer.Choice, Computer.Player);
  }
  else
    ShowDetails(User.Choice, Computer.Choice, enPlayer::Draw);
}
void RoundsOfGame(int Num)
{
  stPlayer User, Computer;
  for (int i = 1; i <= Num; i++)
  {
    cout << "_____________Round [" << i << "] _____________\n\n";
    CheckResult(User, Computer);
    cout << "\n___________________________________\n" << endl;
  }
}

int main()
{
  int NumberOfRounds = ReadPositiveNumber("How Many Rounds 1 to 10 ?", 1, 10);
  RoundsOfGame(NumberOfRounds);

  return 0;
}