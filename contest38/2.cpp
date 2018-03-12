#include <set>
#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

struct Appointment {
    int start_time;
    int duration;
    std::vector<std::string> people_names;
    void OuptutAppointment() const {
        int hours = (start_time % 1440) / 60;
        int minutes = start_time % 60;
        std::cout << hours / 10 << hours % 10 << ":" << minutes / 10 << minutes % 10 << " " << duration;
        for (auto& name: people_names) {
            std::cout << " " << name;
        }
        std::cout << std::endl;
    }
    bool operator<(const Appointment& other) const {
        return std::forward_as_tuple(start_time, duration, people_names) < std::forward_as_tuple(other.start_time, other.duration, other.people_names);
    }
    bool DoAppointmentsIntersect(const Appointment& other) const {
        if (start_time <= other.start_time && start_time + duration > other.start_time) {
            return true;
        }
        if (other.start_time <= start_time && other.start_time + other.duration > start_time) {
            return true;
        }
        return false;
    }
};

struct Person {
    std::string name;
    std::set<Appointment> appointments;

    bool CanAppointmentBeAssigned(const Appointment& new_appointment) const {
        auto it = appointments.upper_bound(new_appointment);
        if (it != appointments.end()) {
            if (new_appointment.DoAppointmentsIntersect(*it)) {
                return false;
            }
        }
        if (it != appointments.begin()) {
            --it;
            if (new_appointment.DoAppointmentsIntersect(*it)) {
                return false;
            }
        }
        return true;
    }
    void AssignAppointment(const Appointment& new_appointment) {
        appointments.insert(new_appointment);
    }
    void OutputAppointmentsInrange(const int start_time, const int finish_time) const {
        for (auto it = appointments.lower_bound(Appointment{start_time, 0, {}}); it != appointments.lower_bound(Appointment{finish_time, 0, {}}); ++it) {
            it->OuptutAppointment();
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::vector<Person> people(10);
    std::unordered_map<std::string, int> name_index;
    int max_person_index = 0;
    for (int i = 0; i < n; ++i) {
        std::string action;
        std::cin >> action;
        if (action == "APPOINT") {
            int day, hours, minutes, duration, k;
            char symbol;
            std::cin >> day >> hours >> symbol >> minutes >> duration >> k;
            Appointment new_appointment{day * 1440 + hours * 60 + minutes, duration, {}};
            std::vector<int> person_indexes;
            for (int j = 0; j < k; ++j) {
                std::string name;
                std::cin >> name;
                int person_index;
                if (name_index.count(name) > 0) {
                    person_index = name_index[name];
                } else {
                    name_index[name] = max_person_index;
                    person_index = max_person_index++;
                }
                people[person_index].name = name;
                person_indexes.push_back(person_index);
            }
            std::vector<int> failed_people_indexes;
            for (auto& person_index: person_indexes) {
                if (!people[person_index].CanAppointmentBeAssigned(new_appointment)) {
                    failed_people_indexes.push_back(person_index);
                }
                new_appointment.people_names.push_back(people[person_index].name);
            }
            if (failed_people_indexes.size() > 0) {
                std::cout << "FAIL\n";
                for (auto& person_index: failed_people_indexes) {
                    std::cout << people[person_index].name << " ";
                }
                std::cout << std::endl;
            } else {
                std::cout << "OK\n";
                for (auto& person_index: person_indexes) {
                    people[person_index].AssignAppointment(new_appointment);
                }
            }
        } else {
            int day;
            std::string name;
            std::cin >> day >> name;
            if (name_index.count(name) > 0) {
                int person_index = name_index[name];
                people[person_index].OutputAppointmentsInrange(day * 1440, (day + 1) * 1440);
            }
        }
    }
    return 0;
}
