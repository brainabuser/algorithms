//
// Created by vladimir on 25.09.2020.
//

#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct Segment {
    int bound;
    int penalty;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    //Количество участков дороги
    int sec_number;
    cin >> sec_number;
    //Ограничения скорости на участках дороги
    vector<int> vel_lim(sec_number);
    for (auto &elem: vel_lim) {
        cin >> elem;
    }
    //Длины участков
    vector<int> sec_len(sec_number);
    for (auto &elem: sec_len) {
        cin >> elem;
    }
    //Количество диапазонов превышения скорости
    int lim_number;
    cin >> lim_number;
    //Диапазоны превышения скорости
    vector<Segment> segments(lim_number - 1);
//    segments.front() = {0, 0};
    for (auto &elem: segments) {
        cin >> elem.bound;
    }
    //Штрафы на каждом из диапазонов
    for (auto &elem: segments) {
        cin >> elem.penalty;
    }
    //Максимально возможный штраф
    int max_penalty;
    cin >> max_penalty;
    //Количество автомобилей
    int q;
    cin >> q;
    //Пары времен для каждого
    vector<double> autos(q);
    for (auto &elem: autos) {
        double start, end;
        cin >> start >> end;
        elem = end - start;
    }
    for (const auto &car_time : autos) {
        auto beg = segments.begin();
        auto end = segments.end();
        auto mid = beg;
        //Проверка, можем ли обойтись без штрафов
        auto time = 0.0;
        for (int i = 0; i < sec_number; ++i) {
            time += (double) sec_len[i] / vel_lim[i];
        }
        if (car_time >= time) {
            cout << 0 << endl;
            continue;
        }
        //Вырожденные случаи для < 3 диапазонов
        int ans = max_penalty;
        if (lim_number == 2) {
            for (int i = 0; i < lim_number; ++i) {
                time = 0.0;
                for (int j = 0; j < sec_number; ++j) {
                    time += (double) sec_len[j] / ((mid->bound) + vel_lim[j]);
                }
                ans = (car_time >= time) ? min(ans, mid->penalty) : ans;
                mid = next(mid);
            }
            cout << ans << endl;
            continue;
        }
        while (distance(beg, end) > 1) {
            time = 0.0;
            for (int i = 0; i < sec_number; ++i) {
                time += (double) sec_len[i] / (mid->bound + vel_lim[i]);
            }
            ans = (car_time >= time) ? min(ans, mid->penalty) : ans;
            beg = (car_time >= time) ? beg : mid;
            end = (car_time >= time) ? mid : end;
            mid = next(beg, distance(beg, end) / 2);
        }
        cout << ans << endl;
    }
    return 0;
}