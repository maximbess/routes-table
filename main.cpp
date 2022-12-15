#include <iostream>
#include <map>
#include <string>

class RoutesTable{
private:
    std::multimap<std::string, std::string> routes_from;
    std::multimap<std::string, std::string> routes_to;
public:
    RoutesTable();
    ~RoutesTable() = default;
    void add(const std::string& a, const std::string& b);
    void del(const std::string& a, const std::string& b);
    void print(const std::string& a);
};

RoutesTable::RoutesTable() {
    routes_from.clear();
    routes_to.clear();
}

void RoutesTable::add(const std::string &a, const std::string &b) {
    bool flag = true;
    if (auto search = routes_from.find(a); search != routes_from.end()) {
        typedef std::multimap<std::string, std::string>::iterator iterator;
        std::pair<iterator, iterator> iterpair = routes_from.equal_range(a);
        auto it = iterpair.first;
        for (; it != iterpair.second; ++it) {
            if (it->second == b) {
                flag = false;
                break;
            }
        }
    }
    if (flag) {
        routes_from.insert({a, b});
        routes_to.insert({b, a});
    }
}

void RoutesTable::del(const std::string &a, const std::string &b) {
    if (auto search = routes_from.find(a); search != routes_from.end()) {
        bool flag = false;
        auto iterpair = routes_from.equal_range(a);
        auto it = iterpair.first;
        for (; it != iterpair.second; ++it) {
            if (it->second == b) {
                routes_from.erase(it);
                flag = true;
                break;
            }
        }
        if (flag) {
            auto iterpair_ = routes_to.equal_range(b);
            auto it_ = iterpair_.first;
            for (; it_ != iterpair_.second; ++it_) {
                if (it_->second == a) {
                    routes_to.erase(it_);
                    break;
                }
            }
        }
    }
}

void RoutesTable::print(const std::string &a) {
    if (auto search = routes_from.find(a); search != routes_from.end()) {
        auto range = routes_from.equal_range(a);
        std::cout << "Routes from " << a << ": " << std::endl;
        for (auto i = range.first; i != range.second; ++i) {
            std::cout << i->first << " -> " << i->second << std::endl;
        }
    }
    else{
        std::cout << "There are no routes from " << a << std::endl;
    }
    if (auto search = routes_to.find(a); search != routes_to.end()) {
        auto range = routes_to.equal_range(a);
        std::cout << "Routes to " << a << ": " << std::endl;
        for (auto i = range.first; i != range.second; ++i) {
            std::cout << i->second << " -> " << i->first << std::endl;
        }
    }
    else{
        std::cout << "There are no routes to " << a << std::endl;
    }
}


int main() {
    RoutesTable example;
    example.add("London", "Paris");
    example.add("London", "Paris"); //equal pairs {key, value} isn't added
    example.add("London", "Moscow");
    example.add("Rome", "London");
    example.add("Manchester", "Liverpool");
    example.add("Moscow", "St. Petersburg");
    example.print("London");
    example.del("London", "Paris");
    example.del("Moscow", "Minsk"); //non-existing elements cause no troubles in deleting
    example.print("London");
    example.print("Abu Dhabi");
    return 0;
}
