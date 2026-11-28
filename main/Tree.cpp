#include "Tree.h"
#include <iostream>
#include <queue>
#include <cctype>

using namespace std;

// Tim mot node con trong danh sach canh duyet cua phu huynh.
static ChildNode* timNutCon(ChildNode* dau, const Person* p) {
    for (ChildNode* cur = dau; cur != nullptr; cur = cur->next) {
        if (cur->p == p) return cur;
    }
    return nullptr;
}

// Kiem tra viec gan con co tao chu trinh hoac gan mot nguoi vao hai nhanh duyet hay khong.
static bool themCanhDuyet(Person* phuHuynh, Person* con) {
    if (phuHuynh == nullptr || con == nullptr || phuHuynh == con) return false;

    // Moi node chi co mot cha duyet; khong cho gan lai sang nhanh khac.
    if (con->cha != nullptr && con->cha != phuHuynh) return false;

    // Khong cho gan mot to tien vao lam con chau cua chinh no.
    for (Person* toTien = phuHuynh; toTien != nullptr; toTien = toTien->cha) {
        if (toTien == con) return false;
    }

    // Them canh vao dung mot danh sach con; neu da co thi khong them trung.
    if (timNutCon(phuHuynh->con, con) == nullptr) {
        ChildNode* nutMoi = new ChildNode;
        nutMoi->p = con;
        nutMoi->next = nullptr;

        if (phuHuynh->con == nullptr) {
            phuHuynh->con = nutMoi;
        } else {
            ChildNode* cuoi = phuHuynh->con;
            while (cuoi->next != nullptr) cuoi = cuoi->next;
            cuoi->next = nutMoi;
        }
    }

    con->cha = phuHuynh;
    return true;
}

// Tim node lien ket vo/chong theo dia chi Person.
static SpouseNode* timNutVoChong(SpouseNode* dau, const Person* p) {
    for (SpouseNode* cur = dau; cur != nullptr; cur = cur->next) {
        if (cur->p == p) return cur;
    }
    return nullptr;
}

// Them mot chieu lien ket vo/chong neu lien ket do chua ton tai.
static void themVoChongMotChieu(Person* nguoi, Person* voChong) {
    if (timNutVoChong(nguoi->vc, voChong) != nullptr) return;

    SpouseNode* nutMoi = new SpouseNode;
    nutMoi->p = voChong;
    nutMoi->next = nullptr;

    if (nguoi->vc == nullptr) {
        nguoi->vc = nutMoi;
    } else {
        SpouseNode* cuoi = nguoi->vc;
        while (cuoi->next != nullptr) cuoi = cuoi->next;
        cuoi->next = nutMoi;
    }
}

// Khoi tao cay rong va dat lai bo dem ID.
void khoiTaoCay(FamilyTree& t) {
    t.root = nullptr;
    t.nextId = 1;
}

// Kiem tra cay co node goc hay chua.
bool laCayRong(const FamilyTree& t) {
    return t.root == nullptr;
}

// Tao mot thanh vien moi va khoi tao day du cac lien ket.
Person* TaoNode(FamilyTree& t, const string& ten, const string& qh,
                int ns, int nm, GioiTinh gioiTinh) {
    Person* node = new Person;
    node->id = t.nextId++;
    node->hoTen = ten;
    node->quanHe = qh;
    node->gioiTinh = gioiTinh;
    node->namSinh = ns;
    node->namMat = nm;
    node->chaRuot = nullptr;
    node->meRuot = nullptr;
    node->cha = nullptr;
    node->vc = nullptr;
    node->con = nullptr;
    return node;
}

// Gan mot nguoi vao danh sach con duyet va cap nhat thong tin cha/me neu biet gioi tinh.
void ThemCon(Person* cha, Person* con) {
    if (!themCanhDuyet(cha, con)) return;

    // Lien ket nay chi xac dinh cha/me ruot khi gioi tinh cua phu huynh da ro.
    if (cha->gioiTinh == GioiTinh::Nam) {
        if (con->chaRuot == nullptr || con->chaRuot == cha) con->chaRuot = cha;
    } else if (cha->gioiTinh == GioiTinh::Nu) {
        if (con->meRuot == nullptr || con->meRuot == cha) con->meRuot = cha;
    }
}

// Gan cha ruot, me ruot va chi tao mot canh duyet tu phu huynh duoc chon.
bool GanChaMe(Person* con, Person* chaRuot, Person* meRuot, Person* nutChaDuyet) {
    if (con == nullptr || (chaRuot == nullptr && meRuot == nullptr)) return false;
    if (chaRuot == con || meRuot == con) return false;
    if (chaRuot != nullptr && chaRuot == meRuot) return false;

    // Kiem tra gioi tinh de tranh gan nham vai tro cha ruot va me ruot.
    if (chaRuot != nullptr && chaRuot->gioiTinh == GioiTinh::Nu) return false;
    if (meRuot != nullptr && meRuot->gioiTinh == GioiTinh::Nam) return false;

    // Khong ghi de thong tin cha/me ruot da duoc gan voi mot nguoi khac.
    if (con->chaRuot != nullptr && chaRuot != nullptr && con->chaRuot != chaRuot) return false;
    if (con->meRuot != nullptr && meRuot != nullptr && con->meRuot != meRuot) return false;

    // Mac dinh chon cha ruot; neu khong co cha ruot thi chon me ruot lam nut cha duyet.
    if (nutChaDuyet == nullptr) {
        nutChaDuyet = (chaRuot != nullptr) ? chaRuot : meRuot;
    }

    // Nut cha duyet bat buoc phai la mot trong hai cha/me ruot da khai bao.
    if (nutChaDuyet != chaRuot && nutChaDuyet != meRuot) return false;
    if (!themCanhDuyet(nutChaDuyet, con)) return false;

    // Luu hai quan he huyet thong rieng biet voi lien ket dung de duyet cay.
    if (chaRuot != nullptr) con->chaRuot = chaRuot;
    if (meRuot != nullptr) con->meRuot = meRuot;
    return true;
}

// Lien ket vo/chong hai chieu; danh sach nay khong tham gia cac thuat toan duyet cay.
bool ThemVoChong(Person* a, Person* b) {
    if (a == nullptr || b == nullptr || a == b) return false;
    themVoChongMotChieu(a, b);
    themVoChongMotChieu(b, a);
    return true;
}

// Them node vao cay rong hoac tao mot canh con trong cay duyet.
bool themVaoCay(FamilyTree& t, Person* cha, Person* p) {
    if (p == nullptr) return false;

    // Khi chua co goc, node moi tro thanh goc va khong co cha duyet.
    if (cha == nullptr) {
        if (t.root != nullptr || p->cha != nullptr) return false;
        p->quanHe = "cu to";
        t.root = p;
        return true;
    }

    // Khi da co goc, chi them node vao danh sach con duyet cua mot phu huynh.
    if (!themCanhDuyet(cha, p)) return false;
    if (cha->gioiTinh == GioiTinh::Nam) p->chaRuot = cha;
    else if (cha->gioiTinh == GioiTinh::Nu) p->meRuot = cha;
    return true;
}

// Tao va dat cu to lam nut goc cua cay neu cay dang rong.
Person* taoCuTo(FamilyTree& t, const string& ten, int ns, int nm, GioiTinh gioiTinh) {
    if (t.root != nullptr) return nullptr;
    Person* p = TaoNode(t, ten, "cu to", ns, nm, gioiTinh);
    t.root = p;
    return p;
}

// Lay node cu to hien tai.
Person* layCuTo(const FamilyTree& t) {
    return t.root;
}

// Tim cu to bang cach di nguoc theo lien ket cha duyet, khong di theo cha/me ruot.
Person* timCuTo(Person* p) {
    if (p == nullptr) return nullptr;
    while (p->cha != nullptr) p = p->cha;
    return p;
}

// Them mot cu to moi len tren cu to hien tai va cap nhat goc cay duyet.
bool themCuToMoi(FamilyTree& t, Person* cuToMoi, const string& qhCuToCu) {
    if (cuToMoi == nullptr) return false;
    if (cuToMoi->cha != nullptr || cuToMoi->con != nullptr) return false;

    // Neu cay rong thi node moi duoc dat lam goc.
    if (t.root == nullptr) return themVaoCay(t, nullptr, cuToMoi);

    // Kiem tra nam sinh de dam bao cu to moi khong sinh sau cu to cu.
    if (cuToMoi->namSinh > t.root->namSinh) return false;

    // Khong ghi de thong tin cha ruot/me ruot da ton tai cua node goc cu.
    if (cuToMoi->gioiTinh == GioiTinh::Nam && t.root->chaRuot != nullptr) return false;
    if (cuToMoi->gioiTinh == GioiTinh::Nu && t.root->meRuot != nullptr) return false;

    // Chuyen cu to cu thanh con cua nut moi thong qua duy nhat mot canh duyet.
    Person* cuToCu = t.root;
    if (!themCanhDuyet(cuToMoi, cuToCu)) return false;
    if (cuToMoi->gioiTinh == GioiTinh::Nam) cuToCu->chaRuot = cuToMoi;
    else if (cuToMoi->gioiTinh == GioiTinh::Nu) cuToCu->meRuot = cuToMoi;
    cuToCu->quanHe = qhCuToCu;
    cuToMoi->quanHe = "cu to";
    t.root = cuToMoi;
    return true;
}

// Tim thanh vien theo ID bang DFS, chi lan theo danh sach con duyet.
Person* TimTheoId(Person* r, int id) {
    if (r == nullptr) return nullptr;
    if (r->id == id) return r;

    // Moi canh trong danh sach con duyet chi den mot nhanh cua cay.
    for (ChildNode* c = r->con; c != nullptr; c = c->next) {
        Person* kq = TimTheoId(c->p, id);
        if (kq != nullptr) return kq;
    }
    return nullptr;
}

// Chuan hoa ten thanh chu thuong va rut gon cac khoang trang lien tiep.
static string chuanHoaTen(const string& s) {
    string kq;
    bool truocLaCach = true;

    // Chuyen chu ve dang thuong va chi giu mot khoang trang giua cac tu.
    for (char ch : s) {
        if (ch == ' ' || ch == '\t') {
            if (!truocLaCach) kq += ' ';
            truocLaCach = true;
        } else {
            kq += static_cast<char>(tolower(static_cast<unsigned char>(ch)));
            truocLaCach = false;
        }
    }

    if (!kq.empty() && kq.back() == ' ') kq.pop_back();
    return kq;
}

// So sanh hai ho ten sau khi da chuan hoa.
bool soSanhTen(const string& a, const string& b) {
    return chuanHoaTen(a) == chuanHoaTen(b);
}

// Tim tat ca nguoi trung ten bang DFS tren mot tap canh con duyet duy nhat.
void TimTheoTen(Person* r, const string& ten, vector<Person*>& kq) {
    if (r == nullptr) return;
    if (soSanhTen(r->hoTen, ten)) kq.push_back(r);

    // Khong duyet tiep qua cha/me ruot hoac vo/chong de tranh lap nguoi.
    for (ChildNode* c = r->con; c != nullptr; c = c->next) {
        TimTheoTen(c->p, ten, kq);
    }
}

// Tinh doi cua mot thanh vien theo chuoi cha duyet ve nut goc.
int layDoi(const Person* p) {
    if (p == nullptr) return 0;
    int doi = 1;
    while (p->cha != nullptr) {
        p = p->cha;
        doi++;
    }
    return doi;
}

// Tinh chieu cao cay con theo cac canh con duyet; node don le co chieu cao 0.
int chieuCao(const Person* r) {
    if (r == nullptr) return -1;
    int maxCon = -1;

    // Tinh chieu cao tung nhanh con va lay nhanh dai nhat.
    for (ChildNode* c = r->con; c != nullptr; c = c->next) {
        int h = chieuCao(c->p);
        if (h > maxCon) maxCon = h;
    }
    return maxCon + 1;
}

// Dem so canh con duyet truc tiep cua mot thanh vien.
int bacCuaNode(const Person* p) {
    if (p == nullptr) return 0;
    int dem = 0;
    for (ChildNode* c = p->con; c != nullptr; c = c->next) dem++;
    return dem;
}

// Dem tong so node co the den duoc tu node nay qua cac canh con duyet.
int demSoNode(const Person* r) {
    if (r == nullptr) return 0;
    int dem = 1;
    for (ChildNode* c = r->con; c != nullptr; c = c->next) {
        dem += demSoNode(c->p);
    }
    return dem;
}

// Dem so la cua cay duyet, khong tinh cac quan he huyet thong khong duoc chon de duyet.
int demSoLa(const Person* r) {
    if (r == nullptr) return 0;
    if (r->con == nullptr) return 1;
    int dem = 0;
    for (ChildNode* c = r->con; c != nullptr; c = c->next) {
        dem += demSoLa(c->p);
    }
    return dem;
}

// In cac thanh vien theo tung doi bang BFS, chi dua cac node con duyet vao hang doi.
void inTheoDoi(const FamilyTree& t) {
    if (t.root == nullptr) {
        cout << "  Cay gia pha dang rong.\n";
        return;
    }

    queue<Person*> q;
    q.push(t.root);
    int doi = 1;

    // Moi vong lap xu ly tron mot tang va dua tang con vao hang doi.
    while (!q.empty()) {
        int soNguoi = static_cast<int>(q.size());
        cout << "  Doi " << doi << ": ";

        for (int i = 0; i < soNguoi; i++) {
            Person* cur = q.front();
            q.pop();
            cout << cur->hoTen << " [ID " << cur->id << "]";
            if (i < soNguoi - 1) cout << ", ";

            // Chi danh sach con duyet duoc dua vao hang doi; khong dua vo/chong va cha/me ruot vao.
            for (ChildNode* c = cur->con; c != nullptr; c = c->next) {
                q.push(c->p);
            }
        }

        cout << "\n";
        doi++;
    }
}
