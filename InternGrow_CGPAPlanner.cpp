/*
    InternGrow C++ Programming Track
    TASK 1: Automated Semester CGPA Planner
    Feature: Takes course grades & credit hours, computes semester GPA and
             cumulative CGPA.
    Upgrade: Predictive simulation - calculates minimum GPA needed in
             upcoming semesters to reach a target CGPA.
*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

struct Course {
    string name;
    double gradePoint;   // e.g. A=4.0, B=3.0 ...
    int creditHours;
};

struct Semester {
    vector<Course> courses;
    double semesterGPA = 0.0;
    int totalCredits = 0;
};

// Converts a letter grade to a grade point (standard 4.0 scale)
double letterToPoint(const string &grade) {
    if (grade == "A+" || grade == "A")  return 4.0;
    if (grade == "A-") return 3.7;
    if (grade == "B+") return 3.3;
    if (grade == "B")  return 3.0;
    if (grade == "B-") return 2.7;
    if (grade == "C+") return 2.3;
    if (grade == "C")  return 2.0;
    if (grade == "C-") return 1.7;
    if (grade == "D")  return 1.0;
    if (grade == "F")  return 0.0;
    return -1.0; // invalid
}

double calculateSemesterGPA(Semester &sem) {
    double totalPoints = 0.0;
    int totalCredits = 0;
    for (size_t i = 0; i < sem.courses.size(); i++) {
        totalPoints += sem.courses[i].gradePoint * sem.courses[i].creditHours;
        totalCredits += sem.courses[i].creditHours;
    }
    sem.totalCredits = totalCredits;
    sem.semesterGPA = (totalCredits == 0) ? 0.0 : (totalPoints / totalCredits);
    return sem.semesterGPA;
}

double calculateCGPA(const vector<Semester> &semesters) {
    double totalPoints = 0.0;
    int totalCredits = 0;
    for (size_t s = 0; s < semesters.size(); s++) {
        for (size_t i = 0; i < semesters[s].courses.size(); i++) {
            totalPoints += semesters[s].courses[i].gradePoint * semesters[s].courses[i].creditHours;
            totalCredits += semesters[s].courses[i].creditHours;
        }
    }
    return (totalCredits == 0) ? 0.0 : (totalPoints / totalCredits);
}
Semester inputSemester(int semNumber) {
    Semester sem;
    int numCourses;
    cout << "\n--- Semester " << semNumber << " ---\n";
    cout << "Enter number of courses: ";
    cin >> numCourses;
    cin.ignore();

    for (int i = 0; i < numCourses; i++) {
        Course c;
        cout << "\nCourse " << (i + 1) << " name: ";
        getline(cin, c.name);

        string grade;
        double point;
        while (true) {
            cout << "Enter letter grade (A+,A,A-,B+,B,B-,C+,C,C-,D,F): ";
            cin >> grade;
            point = letterToPoint(grade);
            if (point >= 0) break;
            cout << "Invalid grade, try again.\n";
        }
        c.gradePoint = point;

        cout << "Enter credit hours: ";
        cin >> c.creditHours;
        cin.ignore();

        sem.courses.push_back(c);
    }
    calculateSemesterGPA(sem);
    return sem;
}

// ---------------- UPGRADE FEATURE ----------------
// Predictive simulation: given current CGPA (with credits completed so far),
// a target CGPA, and planned credit hours for upcoming semesters,
// calculate the minimum average GPA needed in those upcoming semesters.
void predictiveSimulation(const vector<Semester> &completedSemesters) {
    double currentCGPA = calculateCGPA(completedSemesters);
    int completedCredits = 0;
  for (size_t i = 0; i < completedSemesters.size(); i++) completedCredits += completedSemesters[i].totalCredits;
    cout << "\n=== Predictive CGPA Simulation ===\n";
    cout << "Current CGPA: " << fixed << setprecision(2) << currentCGPA << "\n";
    cout << "Completed Credit Hours: " << completedCredits << "\n";

    double targetCGPA;
    int upcomingCredits;
    cout << "Enter your TARGET CGPA: ";
    cin >> targetCGPA;
    cout << "Enter TOTAL credit hours planned for upcoming semesters: ";
    cin >> upcomingCredits;

    if (upcomingCredits <= 0) {
        cout << "Invalid credit hours entered.\n";
        return;
    }

    double totalCreditsAfter = completedCredits + upcomingCredits;
    double requiredTotalPoints = targetCGPA * totalCreditsAfter;
    double currentTotalPoints = currentCGPA * completedCredits;
    double neededPoints = requiredTotalPoints - currentTotalPoints;
    double requiredGPA = neededPoints / upcomingCredits;

    cout << fixed << setprecision(2);
    if (requiredGPA > 4.0) {
        cout << "Target CGPA of " << targetCGPA
             << " is NOT achievable even with a perfect 4.0 GPA in remaining "
             << upcomingCredits << " credit hours.\n";
        cout << "Maximum CGPA achievable: "
             << ((currentTotalPoints + 4.0 * upcomingCredits) / totalCreditsAfter) << "\n";
    } else if (requiredGPA < 0.0) {
        cout << "Target is already guaranteed even with 0.0 GPA in upcoming semesters!\n";
    } else {
        cout << "You need an average GPA of " << requiredGPA
             << " in your upcoming " << upcomingCredits
             << " credit hours to reach a CGPA of " << targetCGPA << ".\n";
    }
}

int main() {
    vector<Semester> semesters;
    int numSemesters;

    cout << "===== Automated Semester CGPA Planner =====\n";
    cout << "Enter number of completed semesters: ";
    cin >> numSemesters;

    for (int i = 1; i <= numSemesters; i++) {
        Semester s = inputSemester(i);
        semesters.push_back(s);
        cout << fixed << setprecision(2);
        cout << "-> Semester " << i << " GPA: " << s.semesterGPA
             << " (Credits: " << s.totalCredits << ")\n";
    }

    double cgpa = calculateCGPA(semesters);
    cout << fixed << setprecision(2);
    cout << "\n===== Summary =====\n";
    for (size_t i = 0; i < semesters.size(); i++) {
        cout << "Semester " << (i + 1) << " GPA: " << semesters[i].semesterGPA << "\n";
    }
    cout << "Cumulative CGPA: " << cgpa << "\n";

    char choice;
    cout << "\nRun predictive CGPA simulation? (y/n): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        predictiveSimulation(semesters);
    }

    cout << "\nThank you for using the CGPA Planner!\n";
    return 0;
}
