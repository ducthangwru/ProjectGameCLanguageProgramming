#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <math.h>
#include "console/console.h"
#include <time.h>
#pragma comment(lib, "libwinmm")

#define ConsoleHeight 25
#define ConsoleWidth  80
#define GameHeight    18

#define up        1
#define down      2
#define left      3
#define right     4
#define upleft    5
#define upright   6
#define downleft  7
#define downright 8

typedef struct
{
    char kitu;
	int mau;
} MotO;

typedef struct
{
    int x, y;
} ToaDo;

typedef struct
{
    char a[3][3];
} HinhDangNhanVat;

typedef struct
{
    ToaDo td;
    HinhDangNhanVat hd;
    int Diem;
    int ThoiGianDoiMau;
    int Mau;
    int ThoiGianPhaHuy;
    int Pow;
    int Mang;
} NhanVat;

typedef struct
{
    ToaDo td;
    int TrangThai;
} VatCan;

typedef struct
{
    VatCan vc[50];
    int n;
} soluongvatcan;

typedef struct
{
    ToaDo td;
} iTem;

typedef struct
{
    iTem item[3];
    int dem;
} ArriTem;

//khoitao.c
void GanO (int dong, int cot, char kitu, int mau);
void khoitaovatcan(soluongvatcan *psl, int i);
void KhoiTao (NhanVat *pnv, soluongvatcan *psl, ArriTem *parritem);
void ThoiGianNV(NhanVat *pnv);

//Hienthi.c
void xuatbuffer();
void HienThi (NhanVat nv, soluongvatcan sl, ArriTem arritem);
void HienThiNhanVat(NhanVat nv);
//XuLy.c
void DiChuyen (soluongvatcan *psl);
void VatCanChamBien(soluongvatcan *psl);
void DieuKhien(NhanVat *pnv, soluongvatcan *psl);
int XuLy(NhanVat *pnv, ArriTem *parritem, soluongvatcan *psl);

//Menu.c
int KhoiTaoMenu();
void HuongDan();
void menu();
void PlayGame();
void HighScore();
void DeleteScore();
void SaveScore();
