
#include "Tree.h"
#include <iostream>
using namespace std;

int soLoi = 0;
void kiemTra(bool dk, const string& moTa) {
    cout << (dk ? "[PASS] " : "[FAIL] ") << moTa << '\n';
    if (!dk) ++soLoi;
}

int main() {
    FamilyTree t;
    khoiTaoCay(t);

   
    Person* H = taoCuTo(t, "Nguyen Van H", "nam", 1880, 1950);
    Person* I = taoCuTo(t, "Nguyen Thi I", "nu", 1885, 1955);
    Person* A = TaoNode(t, "Nguyen Van A", "nam", 1910, 1980);
    Person* B = TaoNode(t, "Nguyen Thi B", "nu", 1915, 1990);
    Person* E = TaoNode(t, "Tran Thi E", "nu", 1920, 2000);
    Person* C = TaoNode(t, "Nguyen Van C", "nam", 1940, 0);
    Person* D = TaoNode(t, "Nguyen Thi D", "nu", 1943, 0);
    Person* F = TaoNode(t, "Nguyen Van F", "nam", 1948, 0);

    kiemTra(themThanhVien(t, A) && themThanhVien(t, B) &&
            themThanhVien(t, E) && themThanhVien(t, C) &&
            themThanhVien(t, D) && themThanhVien(t, F),
            "Them cac thanh vien vao danh sach chung");
    kiemTra(ganChaMe(A, H, I), "Gan H va I la cha me cua A");
    kiemTra(ganChaMe(C, A, B) && ganChaMe(D, A, B),
            "Gan A/B la cha me cua C va D");
    kiemTra(ganChaMe(F, A, E), "Gan A/E la cha me cua F");

    kiemTra(themHonNhan(t, H, I, 1905), "Luu hon nhan cua cap cu to H-I");
    kiemTra(themHonNhan(t, A, B, 1938), "Luu hon nhan A-B");
    kiemTra(themHonNhan(t, A, E, 1946), "A co the co hon nhan thu hai voi E");
    kiemTra(!themHonNhan(t, A, B, 1938), "Khong tao ban ghi trung cho cung mot cap");

    vector<Person*> v;
    layVoChong(t, A, v);
    kiemTra(v.size() == 2, "Tim vo/chong cua A tra ve B va E");

    v.clear(); layCon(t, A, v);
    kiemTra(v.size() == 3, "Tim con cua A tra ve C, D, F");

    v.clear(); layAnhChiEm(t, C, v);
    bool coD = false, coF = false;
    for (Person* x : v) { if (x == D) coD = true; if (x == F) coF = true; }
    kiemTra(v.size() == 2 && coD && coF,
            "C tim duoc D la anh chi em ruot va F la anh chi em cung cha khac me");

    v.clear(); layToTien(C, v);
    bool coA=false, coH=false, coI=false, coB=false;
    for (Person* p : v) {
        if (p == A) coA=true;
        if (p == H) coH=true;
        if (p == I) coI=true;
        if (p == B) coB=true;
    }
    kiemTra(coA && coH && coI && coB, "Truy nguoc duoc ca hai nhanh to tien");

    v.clear(); layHauDue(t, A, v);
    kiemTra(v.size() == 3, "Tim hau due cua A");

    v.clear(); layDauNhanhToTien(t, v);
    kiemTra(v.size() == 4, "Tim cac dau nhanh chua co cha/me: H, I, B, E");

    kiemTra(ketThucHonNhan(t, A, E, 1970), "Cap nhat nam ket thuc hon nhan");

    cout << "\n--- Danh sach thanh vien ---\n";
    inDanhSachThanhVien(t);
    cout << "\n--- Hon nhan ---\n";
    inQuanHeHonNhan(t);
    cout << "\n--- Gia pha theo the he ---\n";
    inGiaPhaTheoTheHe(t);

    giaiPhongCay(t);
    kiemTra(laCayRong(t), "Giai phong va khoi tao lai thanh cong");
    cout << "\nTong loi: " << soLoi << '\n';
    return soLoi == 0 ? 0 : 1;
}
