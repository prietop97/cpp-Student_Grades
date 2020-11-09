#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

void displayScores(int score1, int score2, int score3, int score4, int score5);
void getScores(int& score1, int& score2, int& score3, int& score4, int& score5);
int _calculateAverage(int score1, int score2, int score3, int score4, int score5);
char _determineLetterGrade(int score);
int _getTestGrade();

const int numberOfTests = 5;

int main(){
    int score1,score2,score3,score4,score5;
    string studentName;
    ofstream studentGradeReport;

    studentGradeReport.open("./studentGradeReport.txt");


    cout << "Enter the student name [last, first]:" << endl;
    getline(cin,studentName);
    
    getScores(score1,score2,score3,score4,score5);
    displayScores(score1,score2,score3,score4,score5);

    return 0;
}

void getScores(int& score1, int& score2, int& score3, int& score4, int& score5){
    score1 = _getTestGrade();
    score2 = _getTestGrade();
    score3 = _getTestGrade();
    score4 = _getTestGrade();
    score5 = _getTestGrade();
}

void displayScores(const int score1, const int score2, const int score3, const int score4, const int score5){
    const int average = _calculateAverage(score1,score2,score3,score4,score5);
    cout << "Score\t" << "\tGrade\t" << "Letter Grade" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "Score 1: " << setw(6) << score1 << setw(10) << _determineLetterGrade(score1) << endl;
    cout << "Score 2: " << setw(6) << score2 << setw(10) << _determineLetterGrade(score2) << endl;
    cout << "Score 3: " << setw(6) << score3 << setw(10) << _determineLetterGrade(score3) << endl;
    cout << "Score 4: " << setw(6) << score4 << setw(10) << _determineLetterGrade(score4) << endl;
    cout << "Score 5: " << setw(6) << score5 << setw(10) << _determineLetterGrade(score5) << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "The average is "<< average << setw(10) << _determineLetterGrade(average) << endl;
}

int _getTestGrade(){
    static int totalTestsRecorded = 0;
    totalTestsRecorded++;
    int score;
    cout << "Enter score " << totalTestsRecorded << ": ";
    cin >> score;
    if(totalTestsRecorded == numberOfTests) totalTestsRecorded = 0;
    return score;
}

char _determineLetterGrade(const int score){
    char grade;
    if(score >= 90) grade = 'A';
    else if(score >= 80) grade = 'B';
    else if(score >= 70) grade = 'C';
    else if(score >= 60) grade = 'D';
    else grade = 'F';
    return grade;
}

int _calculateAverage(const int score1, const int score2, const int score3, const int score4, const int score5){
    return (score1 + score2 + score3 + score4 + score5) / numberOfTests;
}
