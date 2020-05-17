//
// Created by Vladimir on 17.05.2020.
//

#include <iostream>
#include <map>

using namespace std;

class DataBase {
  private:
    map<int, int> user_to_order;
    map<int, int> order_to_user;
    const int max_buffer_size;
  public:
    explicit DataBase(int buffer_size) : max_buffer_size(buffer_size) {}
    bool getUser(const int &user_id, const int &order);
};

bool DataBase::getUser(const int &user_id, const int &order) {
    if (user_to_order.find(user_id) == user_to_order.end()) {
        user_to_order[user_id] = order;
        order_to_user[order] = user_id;
        if (user_to_order.size() > max_buffer_size) {
            user_to_order.erase(order_to_user.begin()->second);
            order_to_user.erase(order_to_user.begin()->first);
        }
        return true;
    }
    order_to_user.erase(user_to_order[user_id]);
    user_to_order.erase(user_id);
    user_to_order[user_id] = order;
    order_to_user[order] = user_id;
    if (user_to_order.size() > max_buffer_size) {
        user_to_order.erase(order_to_user.begin()->second);
        order_to_user.erase(order_to_user.begin()->first);
    }
    return false;
}

int main() {
    int buffer_size;
    cin >> buffer_size;
    DataBase db(buffer_size);
    int id, order = 0;
    while (cin >> id) {
        cout << db.getUser(id, order++) << ' ';
    }
    return 0;
}