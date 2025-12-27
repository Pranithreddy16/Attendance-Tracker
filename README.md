# Attendance Tracker

A lightweight command-line application designed to help students track their academic attendance, monitor eligibility status, and predict future attendance requirements.

---

## 📖 Project Overview
The **Attendance Management System** is a tool that automates the tracking of course-wise attendance. It calculates real-time percentages and determines if a student meets the mandatory **75% eligibility criteria**. Beyond simple tracking, it provides a "Predictor" tool that tells students exactly how many more classes they need to attend to stay in the "Safe" zone.

---

## 🧠 Core Concepts Used
* **Data Structures:** Utilizes `struct` to organize course attributes and `std::vector` for dynamic storage.
* **File Handling:** Implements `fstream` for persistent data storage in `attendance.txt`.
* **Algorithmic Logic:** Uses mathematical formulas to calculate the minimum classes required to reach the 75% threshold.
* **Input Validation:** Ensures data integrity by preventing illogical entries (e.g., attending more classes than conducted).

---

## 🔄 Project Workflow



1.  **Load:** On startup, the system reads existing data from `attendance.txt`.
2.  **Input:** The user interacts with a menu to add, modify, or remove course data.
3.  **Process:** The system calculates percentages and categorizes status (Safe/Warning/Critical).
4.  **Forecast:** Users can predict future attendance by simulating upcoming classes.
5.  **Save:** Upon exiting, all updates are written back to the data file.

---

## 🛠️ Key Features
* **Attendance Tracking:** Maintain a clear record of classes attended vs. conducted.
* **Status Categorization:**
    * 🟢 **SAFE:** $\geq$ 75%
    * 🟡 **WARNING:** 65% – 74%
    * 🔴 **CRITICAL:** < 65%
* **Eligibility Predictor:** Calculates the specific number of consecutive classes required to reach the 75% goal.
* **Semester Summary:** Provides an overall average across all registered courses.
* **Persistent Storage:** Automatically saves your progress so you never lose your data.

---

## 🎯 Main Applications
* **Student Productivity:** Helps students avoid being debarred from exams due to low attendance.
* **Academic Planning:** Assists in deciding which classes can be skipped or require mandatory attendance.
* **Educational Foundation:** Serves as a practical example of CRUD operations and file persistence in C++.

---

## 🚀 How to Run
1. **Clone the repository:**
   ```bash
   git clone [https://github.com/yourusername/attendance-system.git](https://github.com/yourusername/attendance-system.git)
