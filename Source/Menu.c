#include "header.h"

int gameover[5][48] =
{
    {1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,1,1,1,1,0,1,1,1,1,1,0,1,0,0,0,0,1,1,1,1,1,0,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,1,0,1,1,0,1,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,1,1,0,0,0,0,1,0,0,0,1},
    {1,0,0,1,1,1,0,0,1,1,1,1,1,0,0,1,0,1,0,1,0,1,1,1,1,0,1,0,0,0,1,0,0,1,0,0,1,0,1,1,1,1,0,1,1,1,1,1},
    {1,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0,0,1,0,0,0,0,1,1,0,0,0},
    {1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,0,1,1,1,1,0,1,1,1,1,1,0,0,0,1,1,0,0,1,1,1,1,0,1,0,1,1,1}
};

void GameOver(int gameover[][48])
{
    clrscr();
    int i, j, y = 5;
    for(i = 0; i < 5; i++)
    {
        gotoXY(17,y);
        for(j = 0; j < 48; j++)
            if(gameover[i][j] == 1)
                 printf("*");
            else
                printf(" ");
        y++;
    }

    gotoXY(17,11);
    printf("Nhan ENTER de luu diem la quay lai menu.....");
}

int KhoiTaoMenu()
{
        clrscr();

        TextColor(13);
        printf("       MENU \n");
        printf("1. START GAME \n");
        printf("2. GAME INSTRUCTIONS\n");
        printf("3. HIGH SCORE\n");
        printf("4. DELETE SCORE \n");
        printf("5: QUIT GAME \n");
        printf("Moi ban chon: ");

        Beep(4000,100);
        if(_getch());
}

void menu()
{
    char chon = KhoiTaoMenu();

    if (chon == '1')
    {
        mciSendStringA("stop Sounds\\nhacnen.wav", NULL, 0, NULL);
        PlayGame();
    }
    else if (chon == '2')
        HuongDan();
    else if (chon == '3')
        HighScore();
    else if (chon == '4')
        DeleteScore();
    else if (chon == '5')
        exit(0);
}

void BackMenu()
{
    if(_kbhit())
        menu();
}

void HuongDan()
{
    clrscr();
    gotoXY(0,0);
    TextColor(13);
    printf("\n \nCac doi tuong trong Game");

    gotoXY(0,3);
    printf(" : Vat Can \n");
    printf(" : Tien \n");
    printf(" : Buc Tuong \n");
    printf(" : Item Bat Tu \n");
    printf(" : Item Pha Huy 1 Vat Can \n");

    gotoXY(0,3);

    TextColor(12);
    printf("%c\n", 219);

    TextColor(8+rand() % 8);
    printf("$\n");

    TextColor(7);
    printf("%c\n", 219);

    TextColor(8 + rand() % 8);
    printf("%c\n", 219);

    TextColor(10);
    printf("%c\n", 219);

    TextColor(14);
    printf("\n \nHuong dan choi game: \n Dieu khien nhan vat di chuyen tranh vat can va an $ de tang diem va level, an item bat tu de bat tu trong 5s va an item pha huy 1 vat can bang cach: \n \n");
    printf("Phim W: di len \nPhim S: di xuong \nPhim A: sang trai \nPhim D: sang phai\n \n");
    printf("Kem theo do la cac phim ho tro khi choi:\nPhim P: Tam Dung Game \nPhim Q: Quit Game \n \n");
    printf("Chuc ban choi Game vui ve! \n");
    printf("\n \n Nhan phim bat ky de quay lai Menu.....");

    system("PAUSE>NULL");
    BackMenu();
}

void HighScore()
{
    int x;
    clrscr();
    TextColor(14);

    FILE *f1 = fopen("score.txt","rt");
    fscanf(f1,"%d", &x);
    printf("High Score: %d \n \n \n", x);
    fclose(f1);
    printf("Nhan phim bat ky de tro lai Menu......");

    system("PAUSE>NULL");
    BackMenu();
}

void DeleteScore()
{
    clrscr();
    TextColor(14);

    FILE *f1 = fopen("score.txt","wt");
    fprintf(f1,"%d", 0);
    fclose(f1);

    printf("Deleted High Score! \n \n");
    printf("Nhan phim bat ky de tro lai Menu......");

    system("PAUSE>NULL");
    BackMenu();
}

void SaveScore(soluongvatcan *psl)
{
    //lưu điểm
    int x;
    FILE *f1 = fopen("score.txt","rt");
    fscanf(f1, "%d", &x);
    fclose(f1);
    if(x <(*psl).n*5)
    {
        x = (*psl).n * 5;
        FILE *f2 = fopen("score.txt", "wt");

        fprintf(f2,"%d", (*psl).n * 5);
        fclose(f2);
    }
}

void PlayGame()
{
    srand (time (NULL));
    gameover[5][48];
    NhanVat nv;
    ArriTem arritem;
    soluongvatcan sl;

    int ma = 0;
    char key;
    KhoiTao(&nv, &sl, &arritem);

    mciSendStringA("play Sounds\\sound.wav", NULL, 0, NULL);

    while (1)
    {
        //hiển thị
        HienThi(nv, sl, arritem);

        //xử lý
        VatCanChamBien(&sl);
        ma = XuLy(&nv, &arritem, &sl);
        DiChuyen(&sl);

        //điều khiển
        if(_kbhit())
            DieuKhien(&nv, &sl);

        //Game over
        if(ma == 1)
        {
            mciSendStringA("stop Sounds\\sound.wav", NULL, 0, NULL);
            mciSendStringA("play Sounds\\gameover.wav", NULL, 0, NULL);

            while(1)
            {
                TextColor(14);
                GameOver(gameover);
                system("PAUSE>NULL");
                if(GetAsyncKeyState(VK_RETURN))
                {
                    SaveScore(&sl);
                    clrscr();
                    BackMenu();
                    break;
                }
            }


            mciSendStringA("stop Sounds\\gameover.wav", NULL, 0, NULL);


        }

        Sleep(10);
    }
    _getch();
}

