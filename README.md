# INTERNGROW_CGPAPLANNER

Automated Semester CGPA Planner built in C++ as part of the **InternGrow C++ Programming Track (Task 1)**.

## 📋 Overview
This console-based application allows students to input course details, grades, and credit hours to calculate individual semester GPA and cumulative CGPA. It also includes a **predictive simulation feature** that calculates the minimum GPA required in upcoming semesters to reach a target CGPA.

## ✨ Features
- **Course Input**: Add multiple courses per semester with grade and credit hours
- **Grade Validation**: Supports standard 4.0 grade scale (A+, A, A-, B+, B, B-, C+, C, C-, D+, D, F)
- **Semester GPA Calculation**: Automatically computes GPA for each semester
- **Cumulative CGPA Tracking**: Tracks CGPA across multiple semesters
- **Detailed Report**: Full breakdown of courses, grades, credit hours, and grade points

### 🚀 Upgrade Feature: Predictive Simulation
Calculates the **minimum average GPA** needed in upcoming semesters to achieve a target CGPA, given:
- Current CGPA and credits earned so far
- Target CGPA
- Planned future credit hours

Handles three scenarios:
- ✅ Target is achievable — shows required GPA
- ⚠️ Target already achieved/exceeded
- ❌ Target not achievable even with a perfect 4.0 GPA

## 🛠️ Grade Scale (4.0 System)
| Grade | Points |
|-------|--------|
| A+/A  | 4.0    |
| A-    | 3.7    |
| B+    | 3.3    |
| B     | 3.0    |
| B-    | 2.7    |
| C+    | 2.3    |
| C     | 2.0    |
| C-    | 1.7    |
| D+    | 1.3    |
| D     | 1.0    |
| F     | 0.0    |

## 💻 How to Run

### Compile
```bash
g++ -std=c++17 InternGrow_CGPAPlanner.cpp -o cgpa_planner
```

### Run
```bash
./cgpa_planner
```
(On Windows: `cgpa_planner.exe`)

## 📖 Usage
1. **Add a New Semester** – Enter courses with grades and credit hours
2. **View Full CGPA Report** – See semester-wise GPA and overall CGPA
3. **Predict Required GPA** – Enter target CGPA and planned future credits to see what GPA you need

## 🧩 Tech Stack
- **Language**: C++ (C++17)
- **Concepts Used**: Structs, Classes, STL (vector, map), Input Validation

## 📌 Built For
**InternGrow C++ Programming Track** — Module 1, Task 1
Contact: interngrow.official@gmail.com

## 👤 Author
[Aapka Naam Yahan Likhen]

## 📄 License
This project was built for educational purposes as part of the InternGrow internship program.
