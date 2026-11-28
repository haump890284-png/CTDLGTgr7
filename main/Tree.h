#ifndef TREE_H
#define TREE_H

#include <string>
#include <vector>

struct Person {
    int id;
    std::string hoTen;
    std::string gioiTinh; // "nam", "nu", "khac"/"chua ro"
    int namSinh;
    int namMat;           // 0 = chua ro/con song
    Person* father;
    Person* mother;
    Person* nextMember;
};

struct MarriageNode {
    Person* person1;
    Person* person2;
    int namKetHon;        // 0 = chua ro
    int namKetThuc;       // 0 = chua ro/chua ket thuc
    MarriageNode* next;
};

struct FamilyTree {
    Person* members;          // dau danh sach tat ca thanh vien
    MarriageNode* marriages;  // dau danh sach cac quan he hon nhan
    int nextId;
};

void khoiTaoCay(FamilyTree& t);
bool laCayRong(const FamilyTree& t); // true neu chua co thanh vien
Person* TaoNode(FamilyTree& t, const std::string& ten,
                const std::string& gioiTinh, int ns, int nm);
Person* TaoNode(FamilyTree& t, const std::string& ten, int ns, int nm);

// Them mot Person vao danh sach chung; khong tu dong gan cha/me.
bool themThanhVien(FamilyTree& t, Person* p);
Person* taoCuTo(FamilyTree& t, const std::string& ten,
                const std::string& gioiTinh, int ns, int nm);

// Gan cha va me cho con. Cha/me co the nullptr neu chua biet.
// Tu choi neu tao vong lap to tien.
bool ganChaMe(Person* con, Person* cha, Person* me);

// Them mot quan he hon nhan; moi cap nguoi chi co mot ban ghi cho
// mot cuoc hon nhan. Cho phep mot nguoi co nhieu cuoc hon nhan.
bool themHonNhan(FamilyTree& t, Person* a, Person* b,
                 int namKetHon = 0, int namKetThuc = 0);
bool ketThucHonNhan(FamilyTree& t, Person* a, Person* b, int namKetThuc);

// Tim kiem
Person* TimTheoId(const FamilyTree& t, int id);
void TimTheoTen(const FamilyTree& t, const std::string& ten,
                std::vector<Person*>& kq);
bool soSanhTen(const std::string& a, const std::string& b);

// Truy van quan he
void layVoChong(const FamilyTree& t, const Person* p,
                std::vector<Person*>& kq);
void layCon(const FamilyTree& t, const Person* p,
            std::vector<Person*>& kq);
void layAnhChiEm(const FamilyTree& t, const Person* p,
                 std::vector<Person*>& kq);
std::string loaiAnhChiEm(const Person* a, const Person* b);

// Lay toan bo to tien / hau due, tranh lap bang visited.
void layToTien(const Person* p, std::vector<Person*>& kq);
void layHauDue(const FamilyTree& t, const Person* p,
               std::vector<Person*>& kq);

// Cac thanh vien khong co thong tin cha va me duoc xem la dau nhanh
// to tien dang ghi nhan, khong khang dinh la thuy to dau tien thuc te.
void layDauNhanhToTien(const FamilyTree& t, std::vector<Person*>& kq);

// Hien thi
void inDanhSachThanhVien(const FamilyTree& t);
void inQuanHeHonNhan(const FamilyTree& t);
void inGiaPhaTheoTheHe(const FamilyTree& t);

// Giai phong toan bo bo nho do FamilyTree quan ly.
void giaiPhongCay(FamilyTree& t);

#endif
