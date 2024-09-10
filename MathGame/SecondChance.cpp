#include "header.h"

enum enQuestionLevel
{
  EasyLevel = 1,
  MedLevel = 2,
  HardLevel = 3,
  Mix = 4,
};
enum enOperationType
{
  Add = 1,
  Sub = 2,
  Mul = 3,
  Div = 4,
  MixOp = 5
};
string GetOperationSymbol(enOperationType OperationType)
{
  switch (OperationType)
  {
  case enOperationType::Add:
    return "+";
  case enOperationType::Sub:
    return "-";
  case enOperationType::Mul:
    return "*";
  case enOperationType::Div:
    return "/";
  default:
    return "Mix";
  }
}
string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
  switch (QuestionLevel)
  {
  case enQuestionLevel::EasyLevel:
    return "Easy";
  case enQuestionLevel::MedLevel:
    return "Med";
  case enQuestionLevel::HardLevel:
    return "Hard";
  default:
    return "Mix";
  }
}
int RandomNumber(int From, int To)
{
  int randomNum = rand() % (To - From + 1) + From;
  return randomNum;
}
void SetScreenColor(bool Right)
{
  if (Right)
    system("color 2F");
  else
  {
    system("color 4F");
    cout << "\a";
  }
}
int ReadHowManyQuestions()
{
  int Num = 0;
  do
  {
    cout << "How Many Questions Do You Want To Answer? ";
    cin >> Num;
  } while (Num < 1 || Num > 10);
  return Num;
}
enQuestionLevel ReadQuestionLevel()
{
  int Num = 0;
  do
  {
    cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
    cin >> Num;
  } while (Num < 1 || Num > 4);
  return (enQuestionLevel)Num;
}
enOperationType ReadOperationType()
{
  int Num = 0;
  do
  {
    cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
    cin >> Num;
  } while (Num < 1 || Num > 5);
  return (enOperationType)Num;
}
struct stQuestion
{
  int Number1 = 0;
  int Number2 = 0;
  enQuestionLevel QuestionLevel;
  enOperationType OperationType;
  int CorrectAnswer = 0;
  int PlayerAnswer = 0;
  bool AnswerResult = false;
};

struct stQuizz
{
  stQuestion QuestionsList[100];
  int NumberOfQuestions = 0;
  enQuestionLevel QuestionLevel;
  enOperationType OperationType;
  int NumberOfWrongAnswers = 0;
  int NumberOfRightAnswers = 0;
  bool IsPass = false;
};

int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
  switch (OpType)
  {
  case enOperationType::Add:
    return Number1 + Number2;
  case enOperationType::Sub:
    return Number1 - Number2;
  case enOperationType::Mul:
    return Number1 * Number2;
  case enOperationType::Div:
    return Number1 / Number2;
  default:
    return Number1 + Number2;
  }
}
enOperationType GetRandomOperationType()
{
  int OpType = RandomNumber(1, 4);
  return enOperationType(OpType);
}
enQuestionLevel GetRandomQuestionLevel()
{
  int QuestionLevel = RandomNumber(1, 3);
  return enQuestionLevel(QuestionLevel);
}
stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OperationType)
{
  stQuestion Question;
  if (QuestionLevel == enQuestionLevel::Mix)
    QuestionLevel = GetRandomQuestionLevel();
  if (OperationType == enOperationType::MixOp)
    OperationType = GetRandomOperationType();
  Question.OperationType = OperationType;
  Question.QuestionLevel = QuestionLevel;
  switch (QuestionLevel)
  {
  case enQuestionLevel::EasyLevel:
  {
    Question.Number1 = RandomNumber(1, 10);
    Question.Number2 = RandomNumber(1, 10);
    Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
    return Question;
  }
  case enQuestionLevel::MedLevel:
  {
    Question.Number1 = RandomNumber(10, 50);
    Question.Number2 = RandomNumber(10, 50);
    Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
    return Question;
  }
  case enQuestionLevel::HardLevel:
  {
    Question.Number1 = RandomNumber(50, 100);
    Question.Number2 = RandomNumber(50, 100);
    Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
    return Question;
  }
  }
  return Question;
}
void GenerateQuizzQuestions(stQuizz &Quizz)
{
  for (int QuestionNum = 0; QuestionNum < Quizz.NumberOfQuestions; QuestionNum++)
  {
    Quizz.QuestionsList[QuestionNum] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OperationType);
  }
}
int ReadQuestionAnswer()
{
  int Num;
  cin >> Num;
  return Num;
}
void PrintTheQuestion(stQuizz Quizz, short QuestionNumber)
{
  cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n";
  cout << Quizz.QuestionsList[QuestionNumber].Number1 << "\n";
  cout << Quizz.QuestionsList[QuestionNumber].Number2 << " ";
  cout << GetOperationSymbol(Quizz.QuestionsList[QuestionNumber].OperationType) << "\n";
  cout << "_______________" << endl;
}
void CorrectTheQuestionAnswer(stQuizz Quizz, short QuestionNumber)
{
  if (Quizz.QuestionsList[QuestionNumber].CorrectAnswer != Quizz.QuestionsList[QuestionNumber].PlayerAnswer)
  {
    Quizz.NumberOfWrongAnswers++;
    Quizz.QuestionsList[QuestionNumber].AnswerResult = false;
    cout << "Wrong Answer :-(\n";
    cout << "The right answer is: " << Quizz.QuestionsList[QuestionNumber].CorrectAnswer;
  }
  else
  {
    Quizz.NumberOfRightAnswers++;
    cout << "\nRight Answer :-)\n\n\n";
    Quizz.QuestionsList[QuestionNumber].AnswerResult = true;
  }
  SetScreenColor(Quizz.QuestionsList[QuestionNumber].AnswerResult);
}
void AskAndCorrectQuestionListAnswers(stQuizz &Quizz)
{
  for (int QuestionNum = 0; QuestionNum < Quizz.NumberOfQuestions; QuestionNum++)
  {
    PrintTheQuestion(Quizz, QuestionNum);
    Quizz.QuestionsList[QuestionNum].PlayerAnswer = ReadQuestionAnswer();
    CorrectTheQuestionAnswer(Quizz, QuestionNum);
  }
  Quizz.IsPass = Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers;
}
string GetFinalResultsText(bool Pass)
{
  if (Pass)
    return "PASS :-)";
  else
    return "FAIL :-(";
}
void PrintQuizzResults(stQuizz Quizz)
{
  cout << "\n\n______________________________\n";
  cout << "Final Results is" << GetFinalResultsText(Quizz.IsPass);
  cout << "\n______________________________\n";
  cout << "Number Of Questions: " << Quizz.NumberOfQuestions << "\n";
  cout << "Questions Level    : " << GetQuestionLevelText(Quizz.QuestionLevel) << "\n";
  cout << "Opration Type      : " << GetOperationSymbol(Quizz.OperationType) << "\n";
  cout << "Number Of Right Answers: " << Quizz.NumberOfRightAnswers << "\n";
  cout << "Number Of Wrong Answers: " << Quizz.NumberOfWrongAnswers << "\n";
  cout << "______________________________" << endl;
}
void PlayMathGame()
{
  stQuizz Quizz;
  Quizz.NumberOfQuestions = ReadHowManyQuestions();
  Quizz.QuestionLevel = ReadQuestionLevel();
  Quizz.OperationType = ReadOperationType();
  GenerateQuizzQuestions(Quizz);
  AskAndCorrectQuestionListAnswers(Quizz);
  PrintQuizzResults(Quizz);
}
void ResetScreen()
{
  system("cls");
  system("color 0F");
}
void StartGame()
{
  char PlayAgain = 'Y';
  do {
    ResetScreen();
    PlayMathGame();
    cout << "Do You Want To Play Again Y/N : " ;
    cin >> PlayAgain; 
  }while(PlayAgain != 'y' || PlayAgain != 'Y');
}
int main()
{
  srand((unsigned)time(NULL));
  StartGame();
}