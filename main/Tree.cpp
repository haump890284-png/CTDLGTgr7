#include "Tree.h"
#include <iostream>
#include <queue>
#include <algorithm>
#include <cctype>
#include <unordered_set>

using namespace std;

static string chuanHoaTen(const string& s) {
    string out;
    bool space = true;
    for (unsigned char ch : s) {
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
            if (!space) out += ' ';
            space = true;
        } else {
            out += static_cast<char>(tolower(ch));
            space = false;
        }
    }
    if (!out.empty() && out.back() == ' ') out.pop_back();
    return out;
}

bool soSanhTen(const string& a, const string& b) {
    return chuanHoaTen(a) == chuanHoaTen(b);
}

void khoiTaoCay(FamilyTree& t) {
    t.members = nullptr;
    t.marriages = nullptr;
    t.nextId = 1;
}

bool laCayRong(const FamilyTree& t) {
    return t.members == nullptr;
}

Person* TaoNode(FamilyTree& t, const string& ten,
                const string& gioiTinh, int ns, int nm) {
    Person* p = new Person;
    p->id = t.nextId++;
    p->hoTen = ten;
    p->gioiTinh = gioiTinh;
    p->namSinh = ns;
    p->namMat = nm;
    p->father = nullptr;
    p->mother = nullptr;
    p->nextMember = nullptr;
    return p;
}

Person* TaoNode(FamilyTree& t, const string& ten, int ns, int nm) {
    return TaoNode(t, ten, "chua ro", ns, nm);
}

bool themThanhVien(FamilyTree& t, Person* p) {
    if (!p) return false;
    for (Person* q = t.members; q; q = q->nextMember)
        if (q == p || q->id == p->id) return false;
    p->nextMember = nullptr;
    if (!t.members) {
        t.members = p;
    } else {
        Person* last = t.members;
        while (last->nextMember) last = last->nextMember;
        last->nextMember = p;
    }
    return true;
}

Person* taoCuTo(FamilyTree& t, const string& ten,
                const string& gioiTinh, int ns, int nm) {
    Person* p = TaoNode(t, ten, gioiTinh, ns, nm);
    if (!themThanhVien(t, p)) {
        delete p;
        return nullptr;
    }
    return p;
}

static bool laThanhVien(const FamilyTree& t, const Person* p) {
    for (Person* q = t.members; q; q = q->nextMember)
        if (q == p) return true;
    return false;
}

static bool laToTienCua(const Person* possibleAncestor, const Person* p) {
    if (!possibleAncestor || !p) return false;
    unordered_set<const Person*> visited;
    vector<const Person*> st;
    if (p->father) st.push_back(p->father);
    if (p->mother) st.push_back(p->mother);
    while (!st.empty()) {
        const Person* cur = st.back(); st.pop_back();
        if (!visited.insert(cur).second) continue;
        if (cur == possibleAncestor) return true;
        if (cur->father) st.push_back(cur->father);
        if (cur->mother) st.push_back(cur->mother);
    }
    return false;
}

bool ganChaMe(Person* con, Person* cha, Person* me) {
    if (!con || cha == con || me == con || (cha && cha == me)) return false;
    if (cha && laToTienCua(con, cha)) return false;
    if (me && laToTienCua(con, me)) return false;
    if (cha && con->namSinh && cha->namSinh &&
        cha->namSinh > con->namSinh) return false;
    if (me && con->namSinh && me->namSinh &&
        me->namSinh > con->namSinh) return false;
    con->father = cha;
    con->mother = me;
    return true;
}

bool themHonNhan(FamilyTree& t, Person* a, Person* b,
                 int namKetHon, int namKetThuc) {
    if (!a || !b || a == b || !laThanhVien(t, a) || !laThanhVien(t, b))
        return false;
    if (namKetHon < 0 || namKetThuc < 0) return false;
    if (namKetHon && a->namSinh && namKetHon < a->namSinh) return false;
    if (namKetHon && b->namSinh && namKetHon < b->namSinh) return false;
    for (MarriageNode* m = t.marriages; m; m = m->next) {
        if ((m->person1 == a && m->person2 == b) ||
            (m->person1 == b && m->person2 == a)) {
            // Cap doi da co ban ghi; khong tao ban ghi trung.
            return false;
        }
    }
    MarriageNode* m = new MarriageNode{a, b, namKetHon, namKetThuc, nullptr};
    if (!t.marriages) t.marriages = m;
    else {
        MarriageNode* last = t.marriages;
        while (last->next) last = last->next;
        last->next = m;
    }
    return true;
}

bool ketThucHonNhan(FamilyTree& t, Person* a, Person* b, int namKetThuc) {
    if (!a || !b || namKetThuc <= 0) return false;
    for (MarriageNode* m = t.marriages; m; m = m->next) {
        if ((m->person1 == a && m->person2 == b) ||
            (m->person1 == b && m->person2 == a)) {
            if (m->namKetHon && namKetThuc < m->namKetHon) return false;
            m->namKetThuc = namKetThuc;
            return true;
        }
    }
    return false;
}

Person* TimTheoId(const FamilyTree& t, int id) {
    for (Person* p = t.members; p; p = p->nextMember)
        if (p->id == id) return p;
    return nullptr;
}

void TimTheoTen(const FamilyTree& t, const string& ten, vector<Person*>& kq) {
    for (Person* p = t.members; p; p = p->nextMember)
        if (soSanhTen(p->hoTen, ten)) kq.push_back(p);
}

void layVoChong(const FamilyTree& t, const Person* p, vector<Person*>& kq) {
    for (MarriageNode* m = t.marriages; m; m = m->next) {
        if (m->person1 == p) kq.push_back(m->person2);
        else if (m->person2 == p) kq.push_back(m->person1);
    }
}

void layCon(const FamilyTree& t, const Person* p, vector<Person*>& kq) {
    for (Person* child = t.members; child; child = child->nextMember)
        if (child->father == p || child->mother == p) kq.push_back(child);
}

string loaiAnhChiEm(const Person* a, const Person* b) {
    if (!a || !b || a == b) return "";
    bool sameFather = a->father && a->father == b->father;
    bool sameMother = a->mother && a->mother == b->mother;
    if (sameFather && sameMother) return "anh/chi/em ruot";
    if (sameFather) return "anh/chi/em cung cha khac me";
    if (sameMother) return "anh/chi/em cung me khac cha";
    return "";
}

void layAnhChiEm(const FamilyTree& t, const Person* p, vector<Person*>& kq) {
    for (Person* q = t.members; q; q = q->nextMember)
        if (loaiAnhChiEm(p, q) != "") kq.push_back(q);
}

void layToTien(const Person* p, vector<Person*>& kq) {
    if (!p) return;
    unordered_set<const Person*> visited;
    vector<const Person*> st;
    if (p->father) st.push_back(p->father);
    if (p->mother) st.push_back(p->mother);
    while (!st.empty()) {
        const Person* cur = st.back(); st.pop_back();
        if (!visited.insert(cur).second) continue;
        kq.push_back(const_cast<Person*>(cur));
        if (cur->father) st.push_back(cur->father);
        if (cur->mother) st.push_back(cur->mother);
    }
}

void layHauDue(const FamilyTree& t, const Person* p, vector<Person*>& kq) {
    if (!p) return;
    unordered_set<const Person*> visited;
    queue<const Person*> q;
    q.push(p);
    visited.insert(p);
    while (!q.empty()) {
        const Person* cur = q.front(); q.pop();
        for (Person* child = t.members; child; child = child->nextMember) {
            if ((child->father == cur || child->mother == cur) &&
                visited.insert(child).second) {
                kq.push_back(child);
                q.push(child);
            }
        }
    }
}

void layDauNhanhToTien(const FamilyTree& t, vector<Person*>& kq) {
    for (Person* p = t.members; p; p = p->nextMember)
        if (!p->father && !p->mother) kq.push_back(p);
}

void inDanhSachThanhVien(const FamilyTree& t) {
    for (Person* p = t.members; p; p = p->nextMember) {
        cout << "ID " << p->id << " | " << p->hoTen
             << " | Cha: " << (p->father ? p->father->hoTen : "chua ro")
             << " | Me: " << (p->mother ? p->mother->hoTen : "chua ro")
             << '\n';
    }
}

void inQuanHeHonNhan(const FamilyTree& t) {
    for (MarriageNode* m = t.marriages; m; m = m->next) {
        cout << m->person1->hoTen << " <-> " << m->person2->hoTen
             << " | Ket hon: " << (m->namKetHon ? to_string(m->namKetHon) : "chua ro")
             << " | Ket thuc: " << (m->namKetThuc ? to_string(m->namKetThuc) : "chua ro")
             << '\n';
    }
}

void inGiaPhaTheoTheHe(const FamilyTree& t) {
    if (!t.members) {
        cout << "Gia pha dang rong.\n";
        return;
    }
    vector<Person*> roots;
    layDauNhanhToTien(t, roots);
    unordered_set<Person*> scheduled;
    queue<pair<Person*, int> > q;
    for (Person* r : roots) {
        if (scheduled.insert(r).second) q.push(make_pair(r, 1));
    }
    while (!q.empty()) {
        int level = q.front().second;
        vector<Person*> current;
        while (!q.empty() && q.front().second == level) {
            Person* cur = q.front().first;
            q.pop();
            current.push_back(cur);
        }
        if (current.empty()) continue;
        cout << "The he " << level << ": ";
        for (size_t i = 0; i < current.size(); ++i) {
            if (i) cout << ", ";
            Person* cur = current[i];
            cout << cur->hoTen << "[ID " << cur->id << "]";
        }
        cout << '\n';
        for (Person* cur : current) {
            for (Person* child = t.members; child; child = child->nextMember) {
                if ((child->father == cur || child->mother == cur) &&
                    scheduled.insert(child).second) {
                    q.push(make_pair(child, level + 1));
                }
            }
        }
    }
    // Thanh vien con lai co the thuoc du lieu chua du thong tin cha/me
    // hoac nhanh chua ket noi voi cac dau nhanh duoc ghi nhan.
    for (Person* p = t.members; p; p = p->nextMember) {
        if (!scheduled.count(p))
            cout << "Chua xep duoc vao nhanh: " << p->hoTen
                 << "[ID " << p->id << "]\n";
    }
}

void giaiPhongCay(FamilyTree& t) {
    MarriageNode* m = t.marriages;
    while (m) {
        MarriageNode* next = m->next;
        delete m;
        m = next;
    }
    Person* p = t.members;
    while (p) {
        Person* next = p->nextMember;
        delete p;
        p = next;
    }
    khoiTaoCay(t);
}
