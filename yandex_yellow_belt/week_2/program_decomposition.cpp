#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream &operator>>(istream &is, Query &q) {
    q.stops.clear();
    string query_type;
    cin >> query_type;
    if (query_type == "NEW_BUS") {
        q.type = QueryType::NewBus;
        cin >> q.bus;
        int stop_count;
        cin >> stop_count;
        for (int i = 0; i < stop_count; ++i) {
            string stop;
            cin >> stop;
            q.stops.push_back(stop);
        }
    } else if (query_type == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        cin >> q.stop;
    } else if (query_type == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        cin >> q.bus;
    } else if (query_type == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse {
    string output_line;
};

ostream &operator<<(ostream &os, const BusesForStopResponse &r) {
    os << r.output_line;
    return os;
}

struct StopsForBusResponse {
    string output_line;
};

ostream &operator<<(ostream &os, const StopsForBusResponse &r) {
    os << r.output_line;
    return os;
}

struct AllBusesResponse {
    string output_line;
};

ostream &operator<<(ostream &os, const AllBusesResponse &r) {
    os << r.output_line;
    return os;
}

class BusManager {
public:
    void AddBus(const string &bus, const vector<string> &stops) {
        buses_to_stops[bus] = stops;
        for (const string &stop : stops) {
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string &stop) const {
        BusesForStopResponse response = {""};
        if (stops_to_buses.count(stop) == 0) {
            response.output_line = "No stop";
        } else {
            for (const string &bus : stops_to_buses.at(stop)) {
                response.output_line += bus + " ";
            }
        }
        return response;
    }

    StopsForBusResponse GetStopsForBus(const string &bus) const {
        StopsForBusResponse response = {""};
        if (buses_to_stops.count(bus) == 0) {
            response.output_line = "No bus";
        } else {
            int counter = 1;
            for (const string &stop : buses_to_stops.at(bus)) {
                response.output_line += "Stop " + stop + ": ";
                if (stops_to_buses.at(stop).size() == 1) {
                    response.output_line += "no interchange";
                } else {
                    for (const string &other_bus : stops_to_buses.at(stop)) {
                        if (bus != other_bus) {
                            response.output_line += other_bus + " ";
                        }
                    }
                }
                if (counter < buses_to_stops.at(bus).size()) {
                    response.output_line += "\n";
                }
                ++counter;
            }
        }

        return
                response;
    }

    AllBusesResponse

    GetAllBuses() const {
        AllBusesResponse response = {""};
        if (buses_to_stops.empty()) {
            response.output_line = "No buses";
        } else {
            int counter = 1;
            for (const auto &bus_item : buses_to_stops) {
                response.output_line += "Bus " + bus_item.first + ": ";
                for (const string &stop : bus_item.second) {
                    response.output_line += stop + " ";
                }
                if (counter < buses_to_stops.size()) {
                    response.output_line += "\n";
                }
                ++counter;
            }
        }
        return response;
    }

private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }

    return 0;
}
