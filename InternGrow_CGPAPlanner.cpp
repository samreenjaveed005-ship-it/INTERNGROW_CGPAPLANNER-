/*
    InternGrow C++ Programming Track - Task 1
    Automated Semester CGPA Planner
    ---------------------------------------------------------------
    Features:
    - Take input for courses, grade scales, credit hours
    - Compute individual semester GPA
    - Compute cumulative CGPA across multiple semesters
    - Upgrade Feature: Predictive simulation - calculates the
      minimum GPA needed in upcoming semesters to hit a target CGPA
*/

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>

using namespace std;

// -----------------------------------------------------------------
// Grade scale mapping (4.0 scale - standard university system)
// -----------------------------------------------------------------
map<string, double> gradeScale = {
    {"A+", 4.0}, {"A", 4.0}, {"A-", 3.7},
    {"B+", 3.3}, {"B", 3.0}, {"B-", 2.7},
    {"C+", 2.3}, {"C", 2.0}, {"C-", 1.7},
    {"D+", 1.3}, {"D", 1.0},
    {"F", 0.0}
};

// -----------------------------------------------------------------
// Course structure
// -----------------------------------------------------------------
struct Course {
    string name;
    string grade;
    double creditHours;
    double gradePoints;

    Course(string n, string g, double ch) : name(n), grade(g), creditHours(ch) {
        gradePoints = getGradePoint(g) * ch;
    }

    static double getGradePoint(const string& g) {
        auto it = gradeScale.find(g);
        if (it != gradeScale.end()) return it->second;
        return -1; // invalid grade marker
    }
};

// -----------------------------------------------------------------
// Semester structure - holds courses and computes semester GPA
// -----------------------------------------------------------------
struct Semester {
    string semesterName;
    vector<Course> courses;

    double getTotalCredits() const {
        double total = 0;
        for (const auto& c : courses) total += c.creditHours;
        return total;
    }

    double getTotalGradePoints() const {
        double total = 0;
        for (const auto& c : courses) total += c.gradePoints;
        return total;
    }

    double getSemesterGPA() const {
        double credits = getTotalCredits();
        if (credits == 0) return 0.0;
        return getTotalGradePoints() / credits;
    }
};

// -----------------------------------------------------------------
// CGPA Planner - manages all semesters and computes cumulative CGPA
// -----------------------------------------------------------------
class CGPAPlanner {
private:
    vector<Semester> semesters;

public:
    void addSemester(const Semester& s) {
        semesters.push_back(s);
    }

    double getCumulativeCredits() const {
        double total = 0;
        for (const auto& s : semesters) total += s.getTotalCredits();
        return total;
    }

    double getCumulativeGradePoints() const {
        double total = 0;
        for (const auto& s : semesters) total += s.getTotalGradePoints();
        return total;
    }

    double getCGPA() const {
        double credits = getCumulativeCredits();
        if (credits == 0) return 0.0;
        return getCumulativeGradePoints() / credits;
    }

    void printReport() const {
        cout << "\n===================================================\n";
        cout << "              CGPA PROFILE REPORT\n";
        cout << "===================================================\n";

        for (const auto& s : semesters) {
            cout << "\n--- " << s.semesterName << " ---\n";
            cout << left << setw(20) << "Course" << setw(10) << "Grade"
                 << setw(10) << "Credits" << "Grade Points\n";
            cout << string(50, '-') << "\n";
            for (const auto& c : s.courses) {
                cout << left << setw(20) << c.name << setw(10) << c.grade
                     << setw(10) << c.creditHours << fixed << setprecision(2)
                     << c.gradePoints << "\n";
            }
            cout << "Semester GPA: " << fixed << setprecision(3)
                 << s.getSemesterGPA() << " (Credits: " << s.getTotalCredits() << ")\n";
        }

        cout << "\n===================================================\n";
        cout << "Cumulative Credits     : " << getCumulativeCredits() << "\n";
        cout << "Cumulative Grade Points: " << fixed << setprecision(2)
             << getCumulativeGradePoints() << "\n";
        cout << "CURRENT CGPA            : " << fixed << setprecision(3)
             << getCGPA() << "\n";
        cout << "===================================================\n";
    }

    // ---------------------------------------------------------
    // UPGRADE FEATURE: Predictive Simulation
    // Calculates minimum average GPA needed in upcoming semesters
    // to reach a target CGPA, given planned future credit hours.
    // ---------------------------------------------------------
    void predictRequiredGPA(double targetCGPA, double futureCredits) const {
        double currentCredits = getCumulativeCredits();
        double currentPoints = getCumulativeGradePoints();
        double totalFutureCredits = currentCredits + futureCredits;

        double requiredTotalPoints = targetCGPA * totalFutureCredits;
        double requiredFuturePoints = requiredTotalPoints - currentPoints;

        if (futureCredits <= 0) {
            cout << "\nInvalid future credit hours entered.\n";
            return;
        }

        double requiredGPA = requiredFuturePoints / futureCredits;

        cout << "\n=========== PREDICTIVE SIMULATION ===========\n";
        cout << "Current CGPA          : " << fixed << setprecision(3) << getCGPA() << "\n";
        cout << "Current Credits Earned: " << currentCredits << "\n";
        cout << "Target CGPA           : " << targetCGPA << "\n";
        cout << "Planned Future Credits: " << futureCredits << "\n";
        cout << "-----------------------------------------------\n";

        if (requiredGPA > 4.0) {
            cout << "NOT ACHIEVABLE: Even a perfect 4.0 GPA in all\n";
            cout << "remaining semesters cannot reach this target.\n";
            cout << "Maximum possible CGPA with " << futureCredits
                 << " more credits at 4.0 GPA: "
                 << fixed << setprecision(3)
                 << ((currentPoints + (4.0 * futureCredits)) / totalFutureCredits) << "\n";
        } else if (requiredGPA < 0.0) {
            cout << "Target already achieved / exceeded!\n";
            cout << "You could get 0.0 GPA in remaining credits and still\n";
            cout << "meet the target (not recommended!).\n";
        } else {
            cout << "You need an average GPA of at least: "
                 << fixed << setprecision(3) << requiredGPA
                 << " in your upcoming " << futureCredits << " credit hours\n";
            cout << "to achieve your target CGPA of " << targetCGPA << ".\n";
        }
        cout << "===============================================\n";
    }
};

// -----------------------------------------------------------------
// Input helper: validates grade against grade scale
// -----------------------------------------------------------------
bool isValidGrade(const string& g) {
    return gradeScale.find(g) != gradeScale.end();
}

void printGradeScale() {
    cout << "\nAvailable Grades: A+, A, A-, B+, B, B-, C+, C, C-, D+, D, F\n";
    cout << "(4.0 Scale: A+/A=4.0, A-=3.7, B+=3.3, B=3.0, B-=2.7,\n";
    cout << " C+=2.3, C=2.0, C-=1.7, D+=1.3, D=1.0, F=0.0)\n";
}

Semester takeSemesterInput(const string& semName) {
    Semester sem;
    sem.semesterName = semName;

    int numCourses;
    cout << "\nEnter number of courses in " << semName << ": ";
    cin >> numCourses;

    printGradeScale();

    for (int i = 0; i < numCourses; i++) {
        string courseName, grade;
        double credits;

        cout << "\n-- Course " << (i + 1) << " --\n";
        cout << "Course Name: ";
        cin.ignore();
        getline(cin, courseName);

        do {
            cout << "Grade Obtained (e.g. A, B+, C-): ";
            cin >> grade;
            if (!isValidGrade(grade)) {
                cout << "Invalid grade. Please re-enter from the available list.\n";
            }
        } while (!isValidGrade(grade));

        cout << "Credit Hours: ";
        cin >> credits;

        sem.courses.push_back(Course(courseName, grade, credits));
    }

    return sem;
}

// -----------------------------------------------------------------
// Main Menu
// -----------------------------------------------------------------
void printMenu() {
    cout << "\n===================================\n";
    cout << "   InternGrow CGPA Planner\n";
    cout << "===================================\n";
    cout << "1. Add a New Semester\n";
    cout << "2. View Full CGPA Report\n";
    cout << "3. Predict Required GPA for Target CGPA\n";
    cout << "0. Exit\n";
    cout << "Enter choice: ";
}

int main() {
    CGPAPlanner planner;
    int choice;
    int semesterCount = 0;

    cout << "Welcome to InternGrow Automated Semester CGPA Planner\n";

    do {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                semesterCount++;
                string semName = "Semester " + to_string(semesterCount);
                cout << "Enter semester name (or press Enter to use \""
                     << semName << "\"): ";
                cin.ignore();
                string customName;
                getline(cin, customName);
                if (!customName.empty()) semName = customName;

                Semester sem = takeSemesterInput(semName);
                planner.addSemester(sem);
                cout << "\n" << semName << " added! GPA: "
                     << fixed << setprecision(3) << sem.getSemesterGPA() << "\n";
                break;
            }
            case 2:
                planner.printReport();
                break;
            case 3: {
                double targetCGPA, futureCredits;
                cout << "\nEnter your target CGPA (e.g. 3.5): ";
                cin >> targetCGPA;
                cout << "Enter total planned credit hours in upcoming semesters: ";
                cin >> futureCredits;
                planner.predictRequiredGPA(targetCGPA, futureCredits);
                break;
            }
            case 0:
                cout << "Thank you for using InternGrow CGPA Planner!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
