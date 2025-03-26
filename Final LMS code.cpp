#include <iostream>
#include <string>
using namespace std;

// Student structure definition
struct Student {
    int rollNo;
    char name[50];
    int marks[3]; // 3 subjects
    float cgpa[3];
    float overallCGPA;
    char attendance[7]; // Attendance for 7 days (P=Present, A=Absent)
};

// Subject structure definition
struct Subject {
    string name;
    string syllabus[4];
};

// Calculate CGPA for a single subject
float calculateCGPA(int marks) {
    return marks / 10.0;
}

// Calculate overall CGPA across all subjects
float calculateOverallCGPA(float cgpa[]) {
    return (cgpa[0] + cgpa[1] + cgpa[2]) / 3;
}

// Display all student records in a formatted table
void displayStudents(Student students[], int size) {
    cout << "\n **********************************************************************************" << endl;
    cout << " ***                         Student Records                                     ***" << endl;
    cout << " **********************************************************************************" << endl;
    cout << "  *** Roll No  |   Name    |     PF   |   AP     |    Calculus   |    Overall CGPA  ***" << endl;
    for (int i = 0; i < size; i++) {
        cout << "  ***   " << students[i].rollNo << "    |    " << students[i].name << "  |   "<< students[i].marks[0] << "   |  " << students[i].marks[1] << "  |   "<< students[i].marks[2] << "    |     " << students[i].overallCGPA<<"  *** " << endl;
    }
    cout << " **********************************************************************************\n";
}

// Edit grades for a specific student
void editGrade(Student students[], int size) {
    int rollNo, newMarks[3], choice;
    do {
        displayStudents(students, size);
        cout << " *** Enter Roll No to Edit Grades (0 to Exit): ";
        cin >> rollNo;
        if (rollNo == 0) break;

        bool found = false;
        for (int i = 0; i < size; i++) {
            if (students[i].rollNo == rollNo) {
                cout << " *** Enter New Marks for " << students[i].name << " ***\n";
                cout << " Programming Fundamentals: ";
                cin >> newMarks[0];
                cout << " Applied Physics: ";
                cin >> newMarks[1];
                cout << " Calculus: ";
                cin >> newMarks[2];

                for (int j = 0; j < 3; j++) {
                    students[i].marks[j] = newMarks[j];
                    students[i].cgpa[j] = calculateCGPA(newMarks[j]);
                }
                students[i].overallCGPA = calculateOverallCGPA(students[i].cgpa);
                
                found = true;
                cout << " *** Grades Updated Successfully! ***\n";
                break;
            }
        }
        if (!found) cout << " *** Student Not Found! ***\n";

        displayStudents(students, size);
        cout << " *** Edit Another? (1: Yes, 0: No): ";
        cin >> choice;
    } while (choice == 1);
}

// Function to display all students' attendance
void displayAttendance(Student students[], int size) {
    cout << "\n  ***  Roll No          Name             Attendance (P=Present, A=Absent)  *** \n";
    cout << " ***                                                                          *** \n";
    
    for (int i = 0; i < size; i++) {
        cout <<"  **** " << students[i].rollNo << "  ***** " << students[i].name << "  ******       ";
        for (int j = 0; j < 7; j++) {
            cout <<"|"<< students[i].attendance[j] << " | "<<" ";
        }
        cout << endl;
    }
}

// Function to edit attendance for a specific student
void editAttendance(Student &student) {
    int day;            // Day to edit attendance (0-6 for Sunday-Saturday)
    char status;        // 'P' for Present, 'A' for Absent

    while (true) {
        cout << "  ***  Enter the day to edit attendance (0=Sunday, 6=Saturday):    ";
        cin >> day;
        cout<<"   *** ";
        if (day < 0 || day > 6) {
            cout << "  *** Invalid day entered. Please enter a number between 0 and 6.  *** " << endl;
            continue;
        }

        cout << " *** Enter the new attendance status (P=Present, A=Absent):   ";
        cin >> status;
        cout<<"   *** ";
       

        student.attendance[day] = status;
        cout << "  ***  Attendance updated successfully!   *** " << endl;

        // Ask if the user wants to edit another day for this student
        char choice;
        cout << " *** Do you want to edit attendance for another day for  " << student.name << " (Y/N)?   ";
        cin >> choice;
        cout<<"   *** ";

        if (choice != 'Y' && choice != 'y') {
            break;  // Exit the loop if the user doesn't want to continue
        }
	}
}

// Function to handle the process of editing student attendance
void manageAttendance(Student students[], int size) {
    int rollNo;
    bool studentFound = false;

    while (true) {
        // Display all students' attendance before asking to edit
        displayAttendance(students, size);

        // Ask user for the roll number of the student to edit
        cout << "\n  ***  Enter the roll number of the student to edit (0 to return to main menu):     ";
        cin >> rollNo;
        cout<<"   *** ";
        
        if (rollNo == 0) {
            break; // Return to main menu
        }

        studentFound = false; // Reset for each search
        // Find the student by roll number
        for (int i = 0; i < size; i++) {
            if (students[i].rollNo == rollNo) {
                studentFound = true;
                cout << "\n ***  Current attendance for " << students[i].name << " (Roll No: " << rollNo << "): *** \n ";
                
                // Display current attendance for the selected student
                for (int j = 0; j < 7; j++) {
                    cout << "  *** Day " << j << ": " << students[i].attendance[j] <<" ***"<< endl;
                }

                // Edit attendance for the student
                editAttendance(students[i]);

                // Show the updated attendance
                cout << "\n *** Updated attendance for " << students[i].name << " (Roll No: " << rollNo << "):  *** \n";
                for (int j = 0; j < 7; j++) {
                    cout << "  *** Day " << j << ": " << students[i].attendance[j] <<"***"<< endl;
                }
                break;
            }
        }

        if (!studentFound) {
            cout << "*** No student found with roll number " << rollNo <<"***"<< endl;
        }

        // Ask if the user wants to edit another student's attendance
        char choice;
        cout << "\n *** Do you want to edit another student's attendance (Y/N)? *** ";
        cin >> choice;

        if (choice != 'Y' && choice != 'y') {
            break;  // Exit the loop if the user doesn't want to continue
        }
    }
}

// Display syllabus for a specific subject
void displaySyllabus(const Subject &subject) {
    cout << "\n==" << subject.name << "==\n";
    cout << "Description:\n";
    for (int i = 0; i < 4; ++i) {
        cout << i + 1 << ") " << subject.syllabus[i] << endl;
    }
}

// Edit syllabus for a specific subject
void editSyllabus(Subject &subject) {
    cout << "\nEnter the new syllabus (4 topics):\n";
    for (int i = 0; i < 4; ++i) {
        cout << "Topic " << i + 1 << ": ";
        cin >> subject.syllabus[i];
    }
    cout << "\nUpdated Syllabus:";
    displaySyllabus(subject);
}

// Manage syllabus for all subjects
void manageSyllabus(Subject subjects[], int numSubjects) {
    while (true) {
        cout << "\n******************\nCOURSE OUTLINE:\n******************\n";
        for (int i = 0; i < numSubjects; ++i) {
            cout << i + 1 << ") " << subjects[i].name << endl;
        }
        cout << numSubjects + 1 << ") Back to Main Menu" << endl;
        
        int choice;
        cout << "\nEnter course number to view details: ";
        cin >> choice;
        
        if (choice == numSubjects + 1) break;
        if (choice < 1 || choice > numSubjects) {
            cout << "Invalid choice. Try again.\n";
            continue;
        }
        
        displaySyllabus(subjects[choice - 1]);
        
        char response;
        cout << "\nDo you want to edit this syllabus? (y/n): ";
        cin >> response;
        
        if (response == 'y' || response == 'Y') {
            editSyllabus(subjects[choice - 1]);
        }
        
        cout << "\nDo you want to view another subject? (y/n): ";
        cin >> response;
        if (response != 'y' && response != 'Y') {
            break;
        }
    }
}

// Display teacher menu
void displayTeacherMenu() {
    cout << " **********************************************************************************" << endl;
    cout << " ***                                                                            ***" << endl;
    cout << " ***  Welcome...........           Sir Hunain                 search here...    ***" << endl;
    cout << " ***                                                                            ***" << endl;
    cout << " ***                                                                            ***" << endl;
    cout << " ***                       Choose What You Want to do                           ***" << endl;
    cout << " ***                                                                            ***" << endl;
    cout << " ***  1. Want To Edit Grades                                                    ***" << endl;
    cout << " ***  2. Want To Edit Attendance                                                ***" << endl;
    cout << " ***  3. Want To Edit Syllabus                                                  ***" << endl;
    cout << " ***  4. Back to Main Menu                                                      ***" << endl;
    cout << " ***                                                                            ***" << endl;
    cout << " **********************************************************************************" << endl;
}

// Function to display course outline for student view
void courseoutline(int courseCode) {
    switch (courseCode) {
    case 1:
        cout << "\n==PROGRAMMING FUNDAMENTAL==" << "\n";
        cout << "\nDescription : " << endl;
        cout << "1)Basics of programming\n" << "2)Problem solving\n" << "3)Operators\n" << "4)Functions\n";    
        break;
    case 2:
        cout << "\n==MATHEMATICS-I==" << "\n";
        cout << "\nDescription : " << endl;
        cout << "1)Basics of maths\n" << "2)functions\n" << "3)Limits\n" << "4)differentiation\n";    
        break;    
    case 3:
        cout << "\n==APPLIED PHYSICS==" << "\n";
        cout << "\nDescription : " << endl;
        cout << "1)Basics of physics\n" << "2)coulomb's law\n" << "3)electric field\n" << "4)gauss's law\n";    
        break;    
        
    default:
        cout << "\nInvalid number please try again.\n";    
    }
}

// Function to display student marks
void displayMarks(string name, string rollNo, int marks[]) {
    string subjects[3] = {"Math", "Physics", "Programming Fundamentals"};
    cout << "\nName: " << name << "\nRoll No: " << rollNo << "\n";
    cout << "\n STUDENT MARKS SUMMARY:\n";
    
    for (int i = 0; i < 3; i++) {
        cout << subjects[i] << " - " << marks[i] << " marks\n";
    }
}

// Function to display attendance records for student view
void displayStudentAttendance(int program, int rollNo) {
    switch(rollNo) {
    case 301:
        cout<<  "\n ****     Name: Hibatullah  RollNo: 301     ****" << endl;
		cout << "PROGRAMMING FUNDAMENTAL         |           85% " << endl;
        cout << "APPLIED PHYSICS                 |           76% " << endl;
        cout << "FUNDAMENTAL OF IT               |           90% " << endl;    
        cout << "MATHS                           |           69% " << endl;
        break;
    case 302:
        cout<<  "\n****     Name: Asad        RollNo: 302     ****" << endl;
		cout << "PROGRAMMING FUNDAMENTAL         |           68% " << endl;
        cout << "APPLIED PHYSICS                 |           82% " << endl;
        cout << "FUNDAMENTAL OF IT               |           55% " << endl;    
        cout << "MATHS                           |           70% " << endl;
        break;    
    case 303:
        cout<<  "\n ****     Name: Azher       RollNo: 303     ****" << endl;
		cout << "PROGRAMMING FUNDAMENTAL         |           90% " << endl;
        cout << "APPLIED PHYSICS                 |           80% " << endl;
        cout << "FUNDAMENTAL OF IT               |           89% " << endl;    
        cout << "MATHS                           |           95% " << endl;
        break;    
    case 304:
        cout<<  " \n****     Name: Hafsa       RollNo: 304     ****" << endl;
		cout << "PROGRAMMING FUNDAMENTAL         |           82% " << endl;
        cout << "APPLIED PHYSICS                 |           73% " << endl;
        cout << "FUNDAMENTAL OF IT               |           97% " << endl;    
        cout << "MATHS                           |           62% " << endl;
        break;    
    case 305:
        cout<<  "\n ****     Name: Adnan       RollNo: 305     ****" << endl;
		cout << "PROGRAMMING FUNDAMENTAL         |           55% " << endl;
        cout << "APPLIED PHYSICS                 |           45% " << endl;
        cout << "FUNDAMENTAL OF IT               |           60% " << endl;    
        cout << "MATHS                           |           60% " << endl;
        break;
    default: 
        cout << "INVALID ROLL NUMBER";
    }
}

// Teacher section main function
void teacherSection() {
    int choice;
    
    // Initialize student data
    Student students[5] = {
        {301, "Hibatullah", {85, 78, 90}, {}, 0, {'P', 'A', 'P', 'P', 'A', 'P', 'A'}},
        {302, "Asad", {78, 82, 88}, {}, 0, {'P', 'P', 'A', 'P', 'P', 'A', 'P'}},
        {303, "Azher", {92, 85, 79}, {}, 0, {'A', 'A', 'A', 'P', 'P', 'P', 'P'}},
        {304, "Hafsa", {74, 90, 83}, {}, 0, {'P', 'P', 'P', 'A', 'A', 'P', 'P'}},
        {305, "Adnan", {88, 76, 91}, {}, 0, {'A', 'P', 'P', 'P', 'A', 'P', 'P'}}
    };

   // Initialize subject data
    Subject subjects[3] = {
        {"Programming Fundamental", {"Basics", "Problem", "Operators", "Functions"}},
        {"Mathematics-I", {"Algebra", "Calculus", "Trigonometry", "Equations"}},
        {"Applied Physics", {"Motion", "Energy", "Waves", "Optics"}}
    };

    // Calculate CGPA values after initialization
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            students[i].cgpa[j] = calculateCGPA(students[i].marks[j]);
        }
        students[i].overallCGPA = calculateOverallCGPA(students[i].cgpa);
    }

    do {
        displayTeacherMenu();
        
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1:
                editGrade(students, 5);
                break;
            case 2:
                manageAttendance(students, 5);
                break;
            case 3:
                manageSyllabus(subjects, 3);
                break;
            case 4:
                cout << " *** Returning to Main Menu... ***" << endl;
                return;
            default:
                cout << " *** Invalid Choice! Please Try Again. ***" << endl;
        }
    } while (true);
}

// Student section main function
void studentSection() {
    int choice;
    
    do {
        // Display student menu
        cout << " \n\n *****                            WELCOME...                    Search here....   ******   " << endl;
        cout << "     *****                                                                             ******   " << endl << endl;
        cout << "  ***** What do you want to do?                                                          ******   " << endl;
        cout << "  ***** 1. View Course Outline                                                           ******   " << endl;
        cout << "  ***** 2. View Grades                                                                   ******   " << endl;
        cout << "  ***** 3. View Attendance                                                               ******   " << endl;
        cout << "  ***** 4. Back to Main Menu                                                             ******   " << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch(choice) {
        case 1: {
            // Course Outline Section
            int courseChoice;
            do {
                cout << "\n*****************\n COURSE OUTLINE : \n*****************";
                cout << "\n1)Programming fundamental\n";
                cout << "\n2)Mathematics-I\n";
                cout << "\n3)Applied physics\n";
                cout << "\n4)Return to main menu\n";
                cout << "\nEnter course number to view details\n";
                cin >> courseChoice;
                if(courseChoice != 4)
                    courseoutline(courseChoice);
            } while(courseChoice != 4);
            break;
        }
        case 2: {
            // Student Marks/Grades Section
            int n, x;
            
            cout << "Press:\n1 if you are a CS student\n2 if you are an S.W student\n";
            cin >> n;
            if (n == 1) {
                cout << "Enter your roll number:24BSCS";
                cin >> x;
                switch (x) {
                    case 301: {
                        int marks[] = {25, 21, 29};
                        displayMarks("Hibatullah", "24BSCS301", marks);
                        break;
                    }
                    case 302: {
                        int marks[] = {29, 24, 23};
                        displayMarks("Asad", "24BSCS302", marks);
                        break;
                    }
                    case 303: {
                        int marks[] = {28, 17, 20};
                        displayMarks("Azher", "24BSCS303", marks);
                        break;
                    }
                    case 304: {
                        int marks[] = {29, 27, 23};
                        displayMarks("Hafsa", "24BSCS304", marks);
                        break;
                    }
                    case 305: {
                        int marks[] = {19, 15, 16};
                        displayMarks("Adnan", "24BSCS305", marks);
                        break;
                    }
                    default:
                        cout << "? Invalid roll number. Please try again.\n";
                }
            } 
            else if (n == 2) {
                cout << "Enter your roll number:24BSSW";
                cin >> x;
                switch (x) {
                    case 301: {
                        int marks[] = {25, 21, 29};
                        displayMarks("Hibatullah", "24BSSW301", marks);
                        break;
                    }
                    case 302: {
                        int marks[] = {29, 24, 23};
                        displayMarks("Asad", "24BSSW302", marks);
                        break;
                       
                    }
                    case 303: {
                        int marks[] = {28, 17, 20};
                        displayMarks("Azher", "24BSSW303", marks);
                        break;
                    }
                    case 304: {
                        int marks[] = {29, 27, 23};
                        displayMarks("Hafsa", "24BSSW304", marks);
                        break;
                    }
                    case 305: {
                        int marks[] = {19, 15, 16};
                        displayMarks("Adnan", "24BSSW305", marks);
                        break;
                    }
                    default:
                        cout << "? Invalid roll number. Please try again.\n";
                }
            } 
            else {
                cout << "? Invalid choice. Please enter 1 or 2.\n";
            }
            break;
        }
        case 3: {
            // Attendance Record Section
            int x, y;
            cout << "Check your attendance record " << endl << "Press:\n1 if you are a CS student\n2 if you are an S.W student\n";   
            cin >> x;
            if (x == 1) {
                cout << "Enter your roll number" << endl << "24BSCS";
                cin >> y;
                displayStudentAttendance(x, y);
            } else if (x == 2) {
                cout << "Enter your roll number" << endl << "24BSSW";
                cin >> y;
                displayStudentAttendance(x, y);
            }
            break;
        }
        case 4:
            cout << "\nReturning to Main Menu...\n";
            return;
        default:
            cout << "\nInvalid choice. Please try again.\n";
        }
    } while(true);
}

int main() {
    int choice;
    
    do {
        // Display main menu (home page)
        cout << " *****          Welcome To LMS of HITMS         ***** " << endl;
        cout << " *****                                          ***** " << endl;
        cout << " *****                                          ***** " << endl;
        cout << " ***** Who are you?                             ***** " << endl;
        cout << " ***** 1. Teacher                               ***** " << endl;
        cout << " ***** 2. Student                               ***** " << endl;
        cout << " ***** 3. Exit                                  ***** " << endl;
        cout << " *****                                          ***** " << endl;
        cout << " ***** Enter your choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                // Teacher Section
                teacherSection();
                break;
            case 2:
                // Student Section
                studentSection();
                break;
            case 3:
                cout << "\nExiting the LMS. Thank you for using!\n";
                return 0;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    } while(true);
    
    return 0;
}
