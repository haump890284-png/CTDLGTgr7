#ifndef QUANLYTHANHVIEN_H
#define QUANLYTHANHVIEN_H

#include "Tree.h"
#include "LinkedList.h"

// Khai bao cac chuc nang them, sua, xem, xoa va hien thi thanh vien gia pha.
void themThanhVien(FamilyTree& t);
void suaThongTin(FamilyTree& t);
void xemThongTin(FamilyTree& t);
void xoaThanhVien(FamilyTree& t);
void hienThiCay(FamilyTree& t);

// Giai phong mot node va toan bo nhanh con theo lien ket duyet.
void huyNode(Person* p);
void giaiPhongCay(Person* root);

#endif
