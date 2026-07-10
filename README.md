# InternGrow_CGPAPlanner

## 📌 Project Title
Automated Semester CGPA Planner

## 📖 Description
A C++ console application that takes course names, letter grades, and credit
hours as input, then calculates:
- Individual **Semester GPA** for each semester
- **Cumulative CGPA** across all entered semesters

### 🚀 Upgrade Feature — Predictive CGPA Simulation
After computing your current CGPA, the program can predict the **minimum
average GPA** you need to score in your upcoming semesters (based on planned
credit hours) in order to reach a **target CGPA** you specify. If the target
is mathematically impossible, it tells you the maximum CGPA you can still
achieve.

## 🛠️ Tech Stack
- Language: C++ (C++17)
- Compiler: g++ / any standard C++ compiler

## 📂 File Structure
```
InternGrow_CGPAPlanner/
├── Task1_CGPA_Planner.cpp
└── README.md
```

## ⚙️ How to Compile & Run
```bash
g++ -std=c++17 -o CGPAPlanner Task1_CGPA_Planner.cpp
./CGPAPlanner
```
On Windows (MinGW):
```bash
g++ -std=c++17 -o CGPAPlanner.exe Task1_CGPA_Planner.cpp
CGPAPlanner.exe
```

## ▶️ How to Use
1. Enter the number of semesters you want to record.
2. For each semester, enter the number of courses, then for each course:
   - Course name
   - Letter grade (A+, A, A-, B+, B, B-, C+, C, C-, D, F)
   - Credit hours
3. The program displays each Semester GPA and the overall Cumulative CGPA.
4. Choose `y` when prompted to run the **Predictive CGPA Simulation**:
   - Enter your target CGPA
   - Enter total planned credit hours for upcoming semesters
   - The program tells you the GPA you must maintain to hit that target.

## 📊 Sample Output
```
===== Automated Semester CGPA Planner =====
Enter number of completed semesters: 1

--- Semester 1 ---
Enter number of courses: 2
...
-> Semester 1 GPA: 3.50 (Credits: 6)

===== Summary =====
Semester 1 GPA: 3.50
Cumulative CGPA: 3.50

Run predictive CGPA simulation? (y/n): y
Enter your TARGET CGPA: 3.80
Enter TOTAL credit hours planned for upcoming semesters: 12
You need an average GPA of 4.00 in your upcoming 12 credit hours
to reach a CGPA of 3.80.
```

## 👤 Author
InternGrow C++ Programming Track — Module 1, Task 1

## 📄 License
This project was developed as part of the InternGrow internship program for
educational purposes.
