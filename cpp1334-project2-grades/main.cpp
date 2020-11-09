/*
 Plan:
    Ask the user the student name
    Ask the user for a test score 5 times (One for each test)
    Sum all scores and divide them by 5 to get the average
    Determine the letter grade for each test and for the average using if else statements
    Output a table to the console showing this information
    Write student name and the table with the tests information to a file
    Ask the user if they want to run the program again for another student
        if yes - run the program again
        if no - stop the program
 */


#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

void displayScores(int score1, int score2, int score3, int score4, int score5);
void writeScores(int score1, int score2, int score3, int score4, int score5, string studentName, ofstream& file);
void getScores(int& score1, int& score2, int& score3, int& score4, int& score5);
int _calculateAverage(int score1, int score2, int score3, int score4, int score5);
char _determineLetterGrade(int score);
int _getTestScore();

// GLOBAL VARIABLES AND CONSTANTS
const int numberOfTests = 5; // Global variable since this program is hardcoded to be with 5 tests, no reason to be passing them as argument
const string divider = "------------------------------------------------------------"; // Global variable for divider for reusability

int main(){
    // MAIN VARIABLES AND CONSTANTS
    bool running = true; // Boolean value used to stop the loop when user enters no
    string continueInput; // Input to capture user input when asked if he want to enter scores for another student
    ofstream studentGradeReport; // Variable to hold the txt file we will be writing to
    int score1,score2,score3,score4,score5; // All 5 scores variables that will be used to store the tests results
    string studentName; // Variable to store student name;
    
    // Open the file - It creates it if it's not already created
    studentGradeReport.open("studentGradeReport.txt");

    // THIS LOOP RUNS THE MAIN PROGRAM OVER AND OVER UNTIL USER DECIDES TO STOP IT.
    while(running){
        // GET USER INPUT - STUDENT NAME (getline) to grab the whole string
        cout << "Enter the student name [last, first]:" << endl;
        getline(cin,studentName);
        
        // GET USER INPUT - Tests scores for all 5 tests
        getScores(score1,score2,score3,score4,score5);
        
        // CONSOLE OUTPUT - Scores with corresponding letter grade equivalent and average of all 5 scores
        displayScores(score1,score2,score3,score4,score5);
        
        // FILE OUTPUT - Student name, and scores with corresponding letter grade equivalent and average of all 5 scores
        writeScores(score1,score2,score3,score4,score5,studentName,studentGradeReport);
        
        // GET USER INPUT - If the user want to run the program again to calculate another student grade
        cout << "Do you want to enter more test scores?" << endl;
        cin >> continueInput;
        if(continueInput == "no") running = false;
        else if(continueInput != "yes") {
            running = false;
            cout << "Invalid entry, program exiting" << endl;
        }
        cin.ignore(10000, '\n'); // Ignore the typed string if user decides to continue
    }
    // Close the file stream
    studentGradeReport.close();
    
    // Program exits successfully
    return 0;
}

void getScores(int& score1, int& score2, int& score3, int& score4, int& score5){
    /*
     Wrappper function to remove repetition from main function. Was thinking of using a loop instead but ran into an issue where
     I could not dynamically set the exact variable that this score should be saved to, only way I thought was doing an if else
     statement but that would just make the code harder to read. Would use an array if we had the option to.
     
     Function Input - All 5 scores references to be able to reassign them.
     */
    score1 = _getTestScore();// Get a specific score
    score2 = _getTestScore();// Get a specific score
    score3 = _getTestScore();// Get a specific score
    score4 = _getTestScore();// Get a specific score
    score5 = _getTestScore();// Get a specific score
}

void displayScores(const int score1, const int score2, const int score3, const int score4, const int score5){
    /*
     Function input - All 5 scores as const to prevent myself from reassigning any of them by accident.
     Function output - None
     
     Console input - None
     Console output - Table with scores for each test, along with the letter grade equivalent and average
     */
    
    // LOCAL VARIABLES AND CONSTANTS
    const int average = _calculateAverage(score1,score2,score3,score4,score5); // Save average variable locally so that I can reuse it.
    
    // Displays table with all scores
    cout << "Score\t" << "\tGrade\t" << "Letter Grade" << endl;
    cout << divider << endl;
    cout << "Score 1: " << setw(6) << score1 << setw(10) << _determineLetterGrade(score1) << endl;
    cout << "Score 2: " << setw(6) << score2 << setw(10) << _determineLetterGrade(score2) << endl;
    cout << "Score 3: " << setw(6) << score3 << setw(10) << _determineLetterGrade(score3) << endl;
    cout << "Score 4: " << setw(6) << score4 << setw(10) << _determineLetterGrade(score4) << endl;
    cout << "Score 5: " << setw(6) << score5 << setw(10) << _determineLetterGrade(score5) << endl;
    cout << divider << endl;
    cout << "The average is "<< average << setw(10) << _determineLetterGrade(average) << endl;
}

void writeScores(const int score1, const int score2, const int score3, const int score4, const int score5, const string studentName, ofstream& file){
    /*
     Function input - All 5 scores as const to prevent myself from reassigning any of them by accident.
                    - Student name
                    - File we will use to save scores as reference
     Function output - None
     
     File output - Student name with Table of scores for each test, along with the letter grade equivalent and average
     */
    
    // LOCAL VARIABLES AND CONSTANTS
    const int average = _calculateAverage(score1,score2,score3,score4,score5); // Save average variable locally so that I can reuse it.
    /*
     I could have saved the average and all the letterGrade equivalent of each score in variables in the main function and
     passed it down as an argument since we already calculated this in displayScores but these functions already have a lot of
     arguments, it's easier and cleaner to just recalculate it since it's a very inexpensive procedure.
     
     Could have also set it as global variables so that I don't have to pass them now but I think that would not be a good
     practice
     */
        
    // Writes the name of the student and table with all scores
    file << divider << endl;
    file << "Student: " << studentName << endl;
    file << "Score\t" << "\tGrade\t" << "Letter Grade" << endl;
    file << divider << endl;
    file << "Score 1: " << setw(6) << score1 << setw(10) << _determineLetterGrade(score1) << endl;
    file << "Score 2: " << setw(6) << score2 << setw(10) << _determineLetterGrade(score2) << endl;
    file << "Score 3: " << setw(6) << score3 << setw(10) << _determineLetterGrade(score3) << endl;
    file << "Score 4: " << setw(6) << score4 << setw(10) << _determineLetterGrade(score4) << endl;
    file << "Score 5: " << setw(6) << score5 << setw(10) << _determineLetterGrade(score5) << endl;
    file << divider << endl;
    file << "The average is "<< average << setw(10) << _determineLetterGrade(average) << endl;
}

int _getTestScore(){
    /*
     Function input - None
     Function output - score that we get from console input
     
     Console output - Prompt the user for the test score
     Console input - An int/double test score
     */
    
    // LOCAL VARIABLES AND CONSTANTS
    static int totalTestsRecorded = 0; // This static variable is used to display the correct test number in the user prompt
    totalTestsRecorded++; // Increments every time we run this function
    int score; // Variable to store the user input and return it back to the getScores function()
    
    // Prompt the user for the test score
    cout << "Enter score " << totalTestsRecorded << ": ";
    cin >> score;
    
    // Resets totalTestsRecorded static variable back to 0 when it gets to 5, in case the user wants to calculate the score for another student
    if(totalTestsRecorded == numberOfTests) totalTestsRecorded = 0;
    return score; // Return the score that the user saved.
}

char _determineLetterGrade(const int score){
    /*
     Function input - One score as a const to prevent myself from reassigning it by accident.
     Function output - Char grade that corresponds with the numerical score - A: 90+, B: 80+, C: 70+, D: 60+, F: 59-
     */
    
    // LOCAL VARIABLES AND CONSTANTS
    char grade;
    
    if(score >= 90) grade = 'A';
    else if(score >= 80) grade = 'B';
    else if(score >= 70) grade = 'C';
    else if(score >= 60) grade = 'D';
    else grade = 'F';
    return grade;
}

int _calculateAverage(const int score1, const int score2, const int score3, const int score4, const int score5){
    /*
     Function input - All 5 scores as const to prevent myself from reassigning any of them by accident.
     Function output - Average of the 5 scores
     */
    return (score1 + score2 + score3 + score4 + score5) / numberOfTests;
}



