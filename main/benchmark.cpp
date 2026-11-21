
#include "Tree.h"
#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

void chayBenchmark(int n) {
    FamilyTree t;
    khoiTaoCay(t);

    // Tao cu to
    Person* root = TaoNode(t, "Nguoi 1", "cu to", 1900, 0);
    themVaoCay(t, nullptr, root);

    // Tao n - 1 thanh vien con truc tiep
    for (int i = 2; i <= n; i++) {
        Person* p = TaoNode(t, "Nguoi " + to_string(i),
                            "con", 1900 + i, 0);
        themVaoCay(t, root, p);
    }

    // Do thoi gian tim kiem ID cuoi cung
    int idCanTim = n;
    const int soLan = 10000;

    auto batDau = high_resolution_clock::now();

    for (int i = 0; i < soLan; i++) {
        TimTheoId(t.root, idCanTim);
    }

    auto ketThuc = high_resolution_clock::now();

    double thoiGian = duration<double, milli>(
        ketThuc - batDau
    ).count();

    cout << "So thanh vien: " << n << endl;
    cout << "So lan tim kiem: " << soLan << endl;
    cout << "Tong thoi gian: " << thoiGian << " ms" << endl;
    cout << "Trung binh moi lan: "
         << thoiGian / soLan << " ms" << endl;
    cout << "-----------------------------" << endl;
}

int main() {
    cout << "=== BENCHMARK TIM KIEM THEO ID ===" << endl;

    chayBenchmark(100);
    chayBenchmark(500);
    chayBenchmark(1000);

    return 0;
}
