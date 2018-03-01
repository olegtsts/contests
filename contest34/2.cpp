#include <vector>
#include <iostream>
#include <set>
#include <cstdlib>
#include <tuple>

struct Point {
    int x;
    int y;
};

struct Track {
    Point start_position;
    Point finish_position;
    int start_time;
    int finish_time;
};

struct Car {
    Point position;
    int time_passed;
    std::vector<size_t> assigned_tracks;
};

class City {
private:
    struct AssignPriority {
        long double functional_value;
        size_t car_index;
        size_t track_index;

        bool operator< (const AssignPriority& other) const {
            return std::forward_as_tuple(functional_value, car_index, track_index)
                < std::forward_as_tuple(other.functional_value, other.car_index, other.track_index);;
        }
    };
public:
    City() {
        size_t cars_number, tracks_number;
        std::cin >> rows >> cols >> cars_number >> tracks_number >> start_on_time_bonus >> max_time;
        tracks.resize(tracks_number);
        cars.resize(cars_number, {{0, 0}, 0, {}});
        for (auto& track: tracks) {
            std::cin >> track.start_position.x >> track.start_position.y >> track.finish_position.x >> track.finish_position.y >> track.start_time >> track.finish_time;
        }
    }
    int GetDistance(const Point& first_point, const Point& second_point) {
        return abs(first_point.x - second_point.x) + abs(first_point.y - second_point.y);
    }
    std::tuple<int, int> GetBonusAndPassedTime(const size_t car_index, const size_t track_index) {
        Car& car = cars[car_index];
        Track& track = tracks[track_index];
        int current_time = car.time_passed;
        int real_start_time = current_time + GetDistance(car.position, track.start_position);
        int total_bonus = 0;
        if (real_start_time <= track.start_time) {
            total_bonus += start_on_time_bonus;
            real_start_time = track.start_time;
        }
        int track_length = GetDistance(track.start_position, track.finish_position);
        int real_finish_time = real_start_time + track_length;
        if (real_finish_time <= track.finish_time) {
            total_bonus += track_length;
        }
        int total_passed_time = real_finish_time - current_time;
        return std::make_tuple(total_bonus, total_passed_time);
    }
    long double GetFunctionalValue(const size_t car_index, const size_t track_index) {
        int total_bonus, total_passed_time;
        std::tie(total_bonus, total_passed_time) = GetBonusAndPassedTime(car_index, track_index);
        return static_cast<long double>(total_bonus) / static_cast<long double>(total_passed_time);
    }
    void MoveCar(const size_t car_index, const size_t track_index) {
        int total_passed_time;
        std::tie(std::ignore, total_passed_time) = GetBonusAndPassedTime(car_index, track_index);
        Car& car = cars[car_index];
        Track& track = tracks[track_index];
        car.time_passed += total_passed_time;
        car.position = track.finish_position;
    }
    void Process() {
        std::set<AssignPriority> priorities;
        std::vector<bool> skip_tracks(tracks.size(), false);
        for (size_t track_index = 0; track_index < tracks.size(); ++track_index) {
            auto& track = tracks[track_index];
            if (track.start_position.x >= 4500 || track.finish_position.x >= 4500 || track.start_position.y >= 3300 || track.finish_position.y >= 3300) {
                skip_tracks[track_index] = true;
            }
        }
        for (size_t car_index = 0; car_index < cars.size(); ++car_index) {
            for (size_t track_index = 0; track_index < tracks.size(); ++track_index) {
                if (!skip_tracks[track_index]) {
                    priorities.insert({GetFunctionalValue(car_index, track_index), car_index, track_index});
                }
            }
        }
        while (priorities.size()) {
            AssignPriority max_priority = *priorities.rbegin();
            priorities.erase(max_priority);
            if (skip_tracks[max_priority.track_index]) {
                continue;
            }
            for (size_t new_track_index = 0; new_track_index < tracks.size(); ++new_track_index) {
                priorities.erase({GetFunctionalValue(max_priority.car_index, new_track_index), max_priority.car_index, new_track_index});
            }
            cars[max_priority.car_index].assigned_tracks.push_back(max_priority.track_index);
            skip_tracks[max_priority.track_index] = true;
            MoveCar(max_priority.car_index, max_priority.track_index);
            for (size_t new_track_index = 0; new_track_index < tracks.size(); ++new_track_index) {
                if (!skip_tracks[new_track_index]) {
                    priorities.insert({GetFunctionalValue(max_priority.car_index, new_track_index), max_priority.car_index, new_track_index});
                }
            }
        }
    }
    void Output() {
        for (auto& car: cars) {
            std::cout << car.assigned_tracks.size();
            for (auto& track: car.assigned_tracks) {
                std::cout << " " << track;
            }
            std::cout << std::endl;
        }
    }
private:
    int rows;
    int cols;
    int start_on_time_bonus;
    int max_time;
    std::vector<Car> cars;
    std::vector<Track> tracks;
};

int main() {
    City city;
    city.Process();
    city.Output();
    return 0;
}
