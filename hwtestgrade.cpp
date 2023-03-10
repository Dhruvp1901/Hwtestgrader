#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_STUDENTS = 100; // maximum number of students
const int MAX_QUESTIONS = 50; // maximum number of questions

// Function prototypes
char getAnswerKey(int numQuestions, string keyString);
int gradeStudent(int numQuestions, string answerKey, string studentAnswers);
char getLetterGrade(int score);
void printReport(int studentNum, string name, int score, char grade, int numQuestions, string answerKey, string studentAnswers);

int main(int argc, char *argv[])
{
    // Check for correct number of command line arguments
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " exam.txt report.txt" << endl;
        return 1;
    }

    // Open input and output files
    ifstream inFile(argv[1]);
    if (!inFile) {
        cerr << "Error: could not open input file " << argv[1] << endl;
        return 1;
    }
    ofstream outFile(argv[2]);
    if (!outFile) {
        cerr << "Error: could not open output file " << argv[2] << endl;
        return 1;
    }

    // Read the answer key
    string keyString;
    getline(inFile, keyString);
    int numQuestions = keyString.length();
    char answerKey[MAX_QUESTIONS];
    for (int i = 0; i < numQuestions; i++) {
        answerKey[i] = keyString.at(i);
    }

    // Read the student data and grade each student
    int studentNum = 0;
    string name, answers;
    int score[MAX_STUDENTS];
    char grade[MAX_STUDENTS];
    int totalScore = 0;
    int numStudents = 0;
    int maxScore = -1;
    while (inFile >> name >> answers) {
        score[studentNum] = gradeStudent(numQuestions, answerKey, answers);
        grade[studentNum] = getLetterGrade(score[studentNum]);
        totalScore += score[studentNum];
        numStudents++;
        if (score[studentNum] > maxScore) {
            maxScore = score[studentNum];
        }
        studentNum++;
    }

    // Calculate the average score and grade
    double averageScore = (double)totalScore / numStudents;
    char averageGrade = getLetterGrade(averageScore);

    // Output the report header
    outFile << "Score Report" << endl;
    outFile << "-------------" << endl;
    outFile << "Answer Key: " << keyString << endl;
    outFile << "Number of Questions: " << numQuestions << endl;
    outFile << "Number of Students: " << numStudents << endl;
    outFile << endl;

    // Output the individual student reports
    for (int i = 0; i < studentNum; i++) {
        printReport(i+1, name, score[i], grade[i], numQuestions, keyString, answers);
    }

    // Output the class average and grade
    outFile << "Class Average: " << averageScore << " (" << averageGrade << ")" << endl;

    // Output the names and averages of students with the highest grades
    outFile << "Highest Scoring Students:" << endl;
    for (int i = 0; i < studentNum; i++) {
        if (score[i] == maxScore) {
            outFile << name << ": " << score[i] << endl;
        }
    }
}


   
