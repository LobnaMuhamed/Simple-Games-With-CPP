#include "header.h"
// Math Game :)

enum enQuizLevel
{
  Easy = 1,
  Med = 2,
  Hard = 3,
  MixLevel = 4,
};
enum enOpType
{
  Add = 1,
  Sub = 2,
  Mul = 3,
  Div = 4,
  MixType = 5,
};
enum enResult
{
  Right = 0,
  Wrong = 1
};
struct stQuizz
{
  short NumOfQs = 0;
  enQuizLevel QuizLevel;
  enOpType OpType;
  short CountOfRightAnswer = 0;
  short CountOfWrongAnswer = 0;
  string FinalResult;
};
int RandomNumber(int From, int To)
{
  int randomNum = rand() % (To - From - 1) + From;
  return randomNum;
}
enQuizLevel ReadQuizLevel()
{
  int Number = 0;
  cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
  cin >> Number;
  return (enQuizLevel)Number;
}
enOpType ReadOpType()
{
  int Number = 0;
  cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
  cin >> Number;
  return (enOpType)Number;
}
string LevelName(enQuizLevel QuizLevel)
{
  if (QuizLevel == enQuizLevel::Easy)
    return "Easy";
  else if (QuizLevel == enQuizLevel::Med)
    return "Med";
  else if (QuizLevel == enQuizLevel::Hard)
    return "Hard";
  else
    return "Mix";
}
int GetNumOfLevel(enQuizLevel QuizLevel)
{
  if (QuizLevel == enQuizLevel::Easy)
    return RandomNumber(1, 10);
  else if (QuizLevel == enQuizLevel::Med)
    return RandomNumber(10, 20);
  else if (QuizLevel == enQuizLevel::Hard)
    return RandomNumber(20, 100);
  else
    return RandomNumber(1, 100);
}
char GetOpType(enOpType OpType)
{
  switch (OpType)
  {
  case enOpType::Add:
    return '+';
  case enOpType::Sub:
    return '-';
  case enOpType::Div:
    return '/';
  case enOpType::Mul:
    return '*';
  default:
    return (char)RandomNumber(1, 2);
    break;
  }
}
void PrintQuestion(int Num1, int Num2, char Op)
{
  cout << Num1 << "\n";
  cout << Num2 << " " << Op << "\n\n";
}
int GenerateQuestion(enQuizLevel QuizLevel, enOpType OpType)
{
  int Num1 = GetNumOfLevel(QuizLevel);
  int Num2 = GetNumOfLevel(QuizLevel);
  char Op = GetOpType(OpType);
  PrintQuestion(Num1, Num2, Op);
  switch (Op)
  {
  case '+':
    return Num1 + Num2;
  case '-':
    return Num1 - Num2;
  case '*':
    return Num1 * Num2;
  case '/':
    return Num1 / Num2;
  default:
    return -1;
  }
}
string GetFinalResultsText(short NumOfRightAnswers, short NumOfWrongAnsers)
{
  if (NumOfRightAnswers >= NumOfWrongAnsers)
    return "Final Result is PASS :-)";
  else
    return "Final Result is FAIL :-(";
}
stQuizz FillGameResult(short NumOfQuestions, enQuizLevel NumOfLevel, enOpType OpType, short NumOfRightAnswers, short NumOfWrongAnsers)
{
  stQuizz Quiz;
  Quiz.NumOfQs = NumOfQuestions;
  Quiz.QuizLevel = NumOfLevel;
  Quiz.OpType = OpType;
  Quiz.CountOfRightAnswer = NumOfRightAnswers;
  Quiz.CountOfWrongAnswer = NumOfWrongAnsers;
  Quiz.FinalResult = GetFinalResultsText(NumOfRightAnswers, NumOfWrongAnsers);
  return Quiz;
}
void PrintQuizzResults(stQuizz Quizz)
{
  cout << "\n___________________________________\n";
  cout << Quizz.FinalResult << "\n";
  cout << "\n___________________________________\n";
  cout << "Number Of Questions: " << Quizz.NumOfQs << "\n";
  cout << "Question Level     : " << LevelName(Quizz.QuizLevel) << "\n";
  cout << "OpType             : " << GetOpType(Quizz.OpType) << "\n";
  cout << "Number Of Right Answers : " << Quizz.CountOfRightAnswer << "\n";
  cout << "Number Of Wrong Answers : " << Quizz.CountOfWrongAnswer << "\n";
  cout << "\n___________________________________" << endl;
}
int ReadAnswer()
{
  int Result;
  cout << "Enter Your Answer\n";
  cin >> Result;
  cout << "\n";
  return Result;
}
enResult CheckReuslt(int RightQues, int MyQues)
{
  if (RightQues == MyQues)
    return enResult::Right;
  else
    return enResult::Wrong;
}
void SetResultScreenColor(enResult Result)
{
  if (Result == enResult::Right)
    system("color 2F");
  else
  {
    system("color 4F");
    cout << "\a";
  }
}
void ResetScreen()
{
  system("cls");
  system("color 0F");
}
short ReadNumOfQuestions()
{
  short Num = 0;
  do
  {
    cout << "How Many Questions Do You Want To Answer? ";
    cin >> Num;
  } while (Num <= 0);
  return Num;
}
stQuizz PlayMathGame(short NumOfQuestions)
{
  short CountOfRightAnswers = 0, CountOfWrongAnswers = 0;
  enQuizLevel QuizLevel = ReadQuizLevel();
  enOpType OpType = ReadOpType();
  for (short QuestionNum = 1; QuestionNum <= NumOfQuestions; QuestionNum++)
  {
    int RightAnswer = GenerateQuestion(QuizLevel, OpType);
    int MyAnswer = ReadAnswer();
    enResult result = CheckReuslt(RightAnswer, MyAnswer);
    if (result == enResult::Right)
      CountOfRightAnswers++;
    else
      CountOfWrongAnswers++;
    SetResultScreenColor(result);
  }
  return FillGameResult(NumOfQuestions, QuizLevel, OpType, CountOfRightAnswers, CountOfWrongAnswers);
}
void StartGame()
{
  char answer = 'Y';
  do
  {
    ResetScreen();
    PrintQuizzResults(PlayMathGame(ReadNumOfQuestions()));
    cout << "\n Do You Want To Play Again? Y / N ? ";
    cin >> answer;
  } while (answer == 'Y' || answer == 'y');
}
int main()
{
  srand((unsigned)time(NULL));
  StartGame();

  return 0;
}