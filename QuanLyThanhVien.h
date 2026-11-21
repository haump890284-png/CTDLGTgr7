#ifndef QUANLYTHANHVIEN_H
#define QUANLYTHANHVIEN_H

#include "Tree.h"

// Cac chuc nang quan ly thong tin thanh vien (module TV4).
void themThanhVien(FamilyTree& t);
void suaThongTin(FamilyTree& t);
void xemThongTin(FamilyTree& t);
void xemThongTin(FamilyTree& t);
void xoaThanhVien(FamilyTree& t);
void hienThiCay(FamilyTree& t);

// Giai phong mot node va toan bo nhanh con cua node do.
void huyNode(Person* p);
void giaiPhongCay(Person* root);

#endif
