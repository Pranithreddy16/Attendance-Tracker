#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;

struct Course {
    string courseName;
    int present;
    int conducted;
};

const double ELIGIBILITY_PERCENT = 75.0;
const string DATA_FILE = "attendance.txt";

// Calculating attendance percentage
double calculatePercentage(int p, int c) {
    if (c == 0) return -1;
    return (double)p * 100 / c;
}

// Calculating required classes for eligibility
int requiredClasses(int p, int c) {
    if (c == 0) return 0;
    double req = (ELIGIBILITY_PERCENT * c - 100 * p) / (100 - ELIGIBILITY_PERCENT);
    if (req <= 0) return 0;
    return ceil(req);
}

// Loading data from file
void loadData(vector<Course> &courses) {
    ifstream fin(DATA_FILE);
    if (!fin) return;

    Course c;
    while (fin >> c.courseName >> c.present >> c.conducted) {
        courses.push_back(c);
    }
    fin.close();
}

// Saving data into a file
void saveData(const vector<Course> &courses) {
    ofstream fout(DATA_FILE);
    for (auto &c : courses) {
        fout << c.courseName << " "
             << c.present << " "
             << c.conducted << endl;
    }
    fout.close();
}

// Registering a new course
void addCourse(vector<Course> &courses) {
    Course c;
    cout << "Enter course name: ";
    cin >> c.courseName;
    cout << "Enter classes attended: ";
    cin >> c.present;
    cout << "Enter total classes conducted: ";
    cin >> c.conducted;

    if (c.present < 0 || c.conducted < 0 || c.present > c.conducted) {
        cout << "Invalid attendance details.\n";
        return;
    }

    courses.push_back(c);
    cout << "Course added successfully.\n";
}

// Modifying attendance of existing course
void modifyCourse(vector<Course> &courses) {
    if (courses.empty()) {
        cout << "No courses available.\n";
        return;
    }

    for (int i = 0; i < courses.size(); i++)
        cout << i + 1 << ". " << courses[i].courseName << endl;

    int ch;
    cout << "Select course number: ";
    cin >> ch;

    if (ch < 1 || ch > courses.size()) {
        cout << "Invalid selection.\n";
        return;
    }

    cout << "Enter updated attended classes: ";
    cin >> courses[ch - 1].present;
    cout << "Enter updated total classes: ";
    cin >> courses[ch - 1].conducted;

    cout << "Course attendance updated.\n";
}

// Removing a Course
void removeCourse(vector<Course> &courses) {
    if (courses.empty()) {
        cout << "No courses to remove.\n";
        return;
    }

    for (int i = 0; i < courses.size(); i++)
        cout << i + 1 << ". " << courses[i].courseName << endl;

    int ch;
    cout << "Select course to remove: ";
    cin >> ch;

    if (ch < 1 || ch > courses.size()) {
        cout << "Invalid selection.\n";
        return;
    }

    courses.erase(courses.begin() + ch - 1);
    cout << "Course removed successfully.\n";
}

// Predicting attendance after N classes
void PredictAttendance(const vector<Course> &courses) {
    if (courses.empty()) {
        cout << "No courses available.\n";
        return;
    }

    cout << "\n--- Attendance Forecast ---\n";
    for (auto &c : courses) {
        if (c.conducted == 0) {
            cout << c.courseName << ": N/A\n";
            continue;
        }

        int future;
        cout << "Future classes for " << c.courseName << ": ";
        cin >> future;

        double newPercent =
            calculatePercentage(c.present + future, c.conducted + future);

        cout << "Expected Attendance: " << newPercent << "%";

        if (newPercent >= ELIGIBILITY_PERCENT)
            cout << " (Eligible)";
        else
            cout << " (Not Eligible)";

        cout << endl;
    }
}

// Generating Course-wise report and semester summary
void generateReport(const vector<Course> &courses) {
    if (courses.empty()) {
        cout << "No courses available.\n";
        return;
    }

    int safe = 0, warn = 0, risk = 0;
    int totalPresent = 0, totalConducted = 0;

    cout << "\n----- Course Attendance Report -----\n";
    for (auto &c : courses) {
        cout << "\nCourse: " << c.courseName;

        if (c.conducted == 0) {
            cout << "\nAttendance: N/A\nStatus: N/A\n";
            continue;
        }

        double p = calculatePercentage(c.present, c.conducted);
        totalPresent += c.present;
        totalConducted += c.conducted;

        string status;
        if (p >= 75) { status = "SAFE"; safe++; }
        else if (p >= 65) { status = "WARNING"; warn++; }
        else { status = "CRITICAL"; risk++; }

        cout << "\nAttendance: " << c.present << "/" << c.conducted;
        cout << "\nPercentage: " << p << "%";
        cout << "\nCurrent Status: " << status;
        cout << "\nMinimum classes required for eligibility: "
             << requiredClasses(c.present, c.conducted) << endl;
    }

    double semesterPercent =
        calculatePercentage(totalPresent, totalConducted);

    cout << "\n----- Semester Summary -----";
    cout << "\nTotal Courses: " << courses.size();
    cout << "\nOverall Attendance: ";
    if (totalConducted == 0) cout << "N/A";
    else cout << semesterPercent << "%";

    cout << "\nSafe: " << safe;
    cout << "\nWarning: " << warn;
    cout << "\nCritical: " << risk;

    if (semesterPercent >= 75)
        cout << "\nSemester Status: ELIGIBLE FOR EXAMS";
    else
        cout << "\nSemester Status: NOT ELIGIBLE FOR EXAMS";

    cout << "\n----------------------------\n";
}

int main() {
    vector<Course> courses;
    int option;

    loadData(courses);

    do {
        cout << "\n===== ATTENDANCE MANAGEMENT SYSTEM =====";
        cout << "\n1. Add New Course";
        cout << "\n2. Modify Course Attendance";
        cout << "\n3. Remove Course";
        cout << "\n4. Predict Attendance";
        cout << "\n5. Generate Attendance Report";
        cout << "\n6. Exit";
        cout << "\nEnter option: ";
        cin >> option;

        switch (option) {
            case 1: addCourse(courses); 
                    break;
            case 2: modifyCourse(courses); 
                    break;
            case 3: removeCourse(courses);
                    break;
            case 4: PredictAttendance(courses); 
                    break;
            case 5: generateReport(courses);
                    break;
            case 6:
                saveData(courses);
                cout << "Data saved successfully. Exiting...\n";
                break;
            default:
                cout << "Invalid option.\n";
        }
    } while (option != 6);

    return 0;
}
