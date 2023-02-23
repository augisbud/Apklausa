#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Student {
    string name;
    int average;
};

struct Subject {
    string subject;
    int popularity;
    vector<int> people;
};

int main() {
    int m;

    ifstream data("U2.txt");
    data >> m;

    vector<Student> students;
    vector<Subject> subjects;

    for(int i = 0; i < m; i++) {
        string name, subject;
        int n, grade, average = 0;
        data >> name >> subject >> n;

        for(int j = 0; j < n; j++) {
            data >> grade;
            average += grade;
        }

        average = average / n;

        if(average >= 9) {
            students.push_back({name, average});
            int found = 0;
            for(int j = 0; j < subjects.size(); j++) {
                if(subjects[j].subject == subject && found == 0) {
                    subjects[j].popularity++;
                    subjects[j].people.push_back(students.size() - 1);
                    found = 1;
                }
            }
            if(found == 0) {
                subjects.push_back({subject, 1, { students.size() - 1 }});
            }
        }
    }

    for(int i = 0; i < subjects.size(); i++) {
        for(int j = i + 1; j < subjects.size(); j++) {
            if(subjects[i].popularity < subjects[j].popularity)
                swap(subjects[i], subjects[j]);
            else if(subjects[i].popularity == subjects[j].popularity && subjects[i].subject > subjects[j].subject)
                swap(subjects[i], subjects[j]);
        }
    }

    if(subjects.size() != 0) {
        for(int i = 0; i < subjects.size(); i++) {
            cout << subjects[i].subject << " " << subjects[i].popularity << endl;
            for(int j = 0; j < subjects[i].people.size(); j++)
                cout << students[subjects[i].people[j]].name << endl;
        }
    } else
        cout << "Neatitinka vidurkis";

    return 0;
}
