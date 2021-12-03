#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <Windows.h>
#include <cstring>
#include <fstream>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>
#define MAX 101
using namespace std;


//===========================//MỘT SỐ HÀM BỔ TRỢ TRONG TRÌNH BÀY//========================================//


void ClearScreen()                 // Ham don sach man hinh 
{
	system("cls");
}

void gotoXY(SHORT posX, SHORT posY)							// hàm dịch con trỏ hiện tại đến điểm có tọa độ(x, y) 
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position;
	Position.X = posX;
	Position.Y = posY;
	SetConsoleCursorPosition(hStdout, Position);
}


//===========================// PHẦN CHÍNH CỦA CHƯƠNG TRÌNH//===================================//


struct Information
{
    string Name;
    string NumberPhone;
    string Address;
};

struct Phonebook
{
    Information data;
    Phonebook *Next;
};

void Init(Phonebook *Heads[])
{
    for (int i = 0; i < MAX; i++)
    {
        Heads[i] = NULL;
    }
}

Phonebook *CreateNode(Information k)
{
    Phonebook *Pk = new Phonebook;
    Pk->data = k;
    Pk->Next = NULL;
    return Pk;
}

int HashWord(string s)
{
    int h = 0;
    for (int i = 0; i < s.length(); i++)
    {
        h += (int)tolower(s[i]) * (i + 1);
    }
    return h % MAX;
}

int Hash(Information k)
{
    return HashWord(k.Name);
}

void AddToContacts(Phonebook *Heads[], Information k)
{
    int h = Hash(k);
    Phonebook *r = Heads[h];
    Phonebook *p = CreateNode(k);
    if (r == NULL)
    {
        Heads[h] = p;
    }
    else
    {
        while (r->Next != NULL)
        {
            r = r->Next;
        }
        r->Next = p;
    }
}

void ReadListPhone(Phonebook *Heads[])
{
    fstream f;
    f.open("ListPhone1.txt", ios::in);
    while (!f.eof())
    {
        Information k;
        getline(f, k.Name);
        getline(f, k.NumberPhone);
        getline(f, k.Address);
        AddToContacts(Heads, k);
    }
    f.close();
}

void Add(Phonebook *Heads[])
{
    fstream f;
    f.open("Doc1.txt", ios::in);
    while (!f.eof())
    {
        Information k;
        getline(f, k.Name);
        getline(f, k.NumberPhone);
        getline(f, k.Address);
        AddToContacts(Heads, k);
    }
    f.close();
}

Phonebook *TimNode(Phonebook *Heads[], string numberphone)
{
    for (int i = 0; i < MAX; i++)
    {
        if (Heads[i] != NULL)
        {
            Phonebook *p = Heads[i];
            while (p != NULL)
            {
                if (p->data.NumberPhone == numberphone)
                    return p;
                p = p->Next;
            }
        }
    }
}

int TimNode1(Phonebook *Heads[], string name)
{
    int d = 0;
    for (int i = 0; i < MAX; i++)
    {
        if (Heads[i] != NULL)
        {
            Phonebook *p = Heads[i];
            while (p != NULL)
            {
                if (p->data.Name == name)
                    d++;
                p = p->Next;
            }
        }
    }
    return d;
}

bool Ischuoicon(string a, string b)
{
	char* ch = new char[a.length()];
	strcpy(ch, a.c_str());
	_strlwr_s(ch, strlen(ch) + 1);
	char* ch1 = new char[b.length()];
	strcpy(ch1, b.c_str());
	_strlwr_s(ch1, strlen(ch1) + 1);
	return strstr(ch, ch1);
}

void Ghifile(ofstream &fileout, Information k)
{
    fileout << k.Name << endl;
    fileout << k.NumberPhone << endl;
    fileout << k.Address << endl;
}

void SearchName(Phonebook *Heads[], ofstream &fileout, string name)
{
    bool flag = true;
    for (int i = 0; i < MAX; i++)
    {
        if (Heads[i] != NULL)
        {
            Phonebook *p = Heads[i];
            while (p != NULL)
            {
                if (Ischuoicon(p->data.Name, name))
                {
					gotoXY(50, 12);
                    cout << "Tim kiem thanh cong!!!\n";
                    Ghifile(fileout, p->data);
					gotoXY(30, 15);
                    cout << p->data.Name + "\t\t" + p->data.NumberPhone + "\t\t" + p->data.Address << endl;
                    flag = false;
                }
                p = p->Next;
            }
        }
    }
	gotoXY(50, 12);
    if (flag == true)
        cout << "Khong tim thay\n";
}

void SearchPhone(Phonebook *Heads[], ofstream &fileout, string name)
{
    bool flag = true;
    for (int i = 0; i < MAX; i++)
    {
        if (Heads[i] != NULL)
        {
            Phonebook *p = Heads[i];
            while (p != NULL)
            {
                if (Ischuoicon(p->data.NumberPhone, name))
                {
					gotoXY(50, 10);
                    Ghifile(fileout, p->data);
                    cout << "Tim kiem thanh cong\n";
                    cout << p->data.Name + "\t\t" + p->data.NumberPhone + "\t\t" + p->data.Address << endl;
                    flag = false;
                }
                p = p->Next;
            }
        }
    }
	gotoXY(50, 10);
    if (flag == true)
        cout << "Khong tim thay\n";
}

void SearchAddress(Phonebook *Heads[], ofstream &fileout, string name)
{
    bool flag = true;
    for (int i = 0; i < MAX; i++)
    {
        if (Heads[i] != NULL)
        {
            Phonebook *p = Heads[i];
            while (p != NULL)
            {
                if (p->data.Address.compare(name) == 0)
                {
					gotoXY(48, 12);
                    cout << "Tim kiem thanh cong !!!";
                    Ghifile(fileout, p->data);
					gotoXY(40, 14);
                    cout << p->data.Name + "\t\t" + p->data.NumberPhone + "\t\t" + p->data.Address << endl;
                    flag = false;
                }
                p = p->Next;
            }
        }
    }
	gotoXY(48, 12);
    if (flag == true)
        cout << "Khong tim thay !!!";
}

void UpdateInfoToName(Phonebook *Heads[], string name)
{

    for (int i = 0; i < MAX; i++)
    {
        if (Heads[i] != NULL)
        {
            int dem = 0;
            Phonebook *p = Heads[i];
            Phonebook *r = new Phonebook;
            while (p != NULL)
            {
                if (p->data.Name.compare(name) == 0)
                {
                    dem++;
                    r = p;
                }
                p = p->Next;
            }
            if (dem == 1)
            {
                string newname;
                string newphone;
                string newAddress;
				gotoXY(45, 12);
				rewind(stdin);
                cout << "Nhap Ten moi: ";
                getline( cin , newname );
				gotoXY(45, 14);
                cout << "Nhap SDT moi: ";
                getline(cin, newphone);
				gotoXY(45, 16);
                cout << "Nhap dia chi moi: ";
                getline(cin, newAddress);
                r->data.Name = newname;
                r->data.NumberPhone = newphone;
                r->data.Address = newAddress;
            }
            else if (dem > 1)
            {
				gotoXY(40, 12);
                cout << "Nhap SDT Muon Sua: ";
                string sdt;
				rewind(stdin);
                getline(cin,sdt);
                Phonebook *k = TimNode(Heads, sdt);
                string name;
                string phone;
                string address;
				gotoXY(40, 14);
                cout << "Nhap Ten moi ";
                getline(cin,name);
				gotoXY(40, 16);
                cout << "Nhap SDT moi ";
                getline(cin,phone);
				gotoXY(40, 18);
                cout << "Nhap dia chi moi ";
                getline(cin,address);
                k->data.Name = name;
                k->data.NumberPhone = phone;
                k->data.Address = address;
            }
        }
    }
}

void UpdateInfoToNumber(Phonebook *Heads[], string number)
{

    for (int i = 0; i < MAX; i++)
    {
        if (Heads[i] != NULL)
        {
            int dem = 0;
            Phonebook *p = Heads[i];
            Phonebook *r = new Phonebook;
            while (p != NULL)
            {
                if (p->data.NumberPhone.compare(number) == 0)
                {
                    dem++;
                    r = p;
                }
                p = p->Next;
            }
            if (dem == 1)
            {
                string newname;
                string newphone;
                string newAddress;
				rewind(stdin);
				gotoXY(50, 10);
                cout << "Nhap Ten moi ";
                getline(cin, newname);
				gotoXY(50, 10);
                cout << "Nhap SDT moi ";
                getline(cin, newphone);
				gotoXY(50, 10);
                cout << "Nhap dia chi moi ";
				getline(cin, newAddress);
                r->data.Name = newname;
                r->data.NumberPhone = newphone;
                r->data.Address = newAddress;
            }
        }
    }
}

void DeleteToName(Phonebook *Heads[], string name)
{
    bool flag = false;
    for (int i = 0; i < MAX; i++)
    {
        if (Heads[i] != NULL)
        {
            int dem = 0;
            Phonebook *p = Heads[i];
            Phonebook *Prev = NULL;
            while (p != NULL)
            {
                if (p->data.Name.compare(name) == 0)
                {
                    flag = true;
                    if (Prev == NULL)
                    {
                        Heads[i] = p->Next;
                    }
                    else
                    {
                        Prev->Next = p->Next;
                    }
                    p->Next = NULL;
                    delete (p);
                }
                Prev = p;
                p = p->Next;
            }
        }
    }
	gotoXY(50, 10);
    if (!flag )
    {
        cout << "Xoa khong thanh cong\n";
    }
    else
        cout << "Xoa thanh cong\n";
}

void DeleteToNumber(Phonebook *Heads[], string name)
{
    bool flag = false;
    for (int i = 0; i < MAX; i++)
    {
        if (Heads[i] != NULL)
        {
            int dem = 0;
            Phonebook *p = Heads[i];
            Phonebook *Prev = NULL;
            while (p != NULL)
            {
                if (p->data.NumberPhone.compare(name) == 0)
                {
                    flag = true;
                    if (Prev == NULL)
                    {
                        Heads[i] = p->Next;
                    }
                    else
                    {
                        Prev->Next = p->Next;
                    }
                    p->Next = NULL;
                    delete (p);
                }
                Prev = p;
                p = p->Next;
            }
        }
    }
	gotoXY(50, 10);
    if (!flag )
    {
        cout << "Xoa khong thanh cong\n";
    }
    else
        cout << "Xoa thanh cong\n";
}

void DisplayToFile(Phonebook *Heads[], ofstream &fileout)
{
    for (int i = 0; i < MAX; i++)
    {
        if (Heads[i] != NULL)
        {
            Phonebook *p = Heads[i];
            while (p != NULL)
            {
                Ghifile(fileout, p->data);
                p = p->Next;
            }
        }
    }
}

void Dem(Phonebook *Heads[])
{
    int dem = 0;
    for (int i = 0; i < MAX; i++)
    {
        if (Heads[i] != NULL)
        {
            Phonebook *p = Heads[i];
            while (p != NULL)
            {
                dem++;
                p = p->Next;
            }
        }
    }
    cout << dem << endl;
}


//===========================//PHẦN NÀY CHỨA CÁC HÀM, GỌI TRONG CÁC MENU DÙNG ĐỂ IN RA MÀN HÌNH CONSOLE//======================//


void EnterList(Phonebook *Heads[])                  //=======Ham nhap danh sach=========
{
	ClearScreen();
	ofstream fileout;
    string name;
	fileout.open("ListPhone1.txt", ios_base::out);
    Add(Heads);
    DisplayToFile(Heads, fileout);
    fileout.close();
}				

void Exportlist(Phonebook *Heads[])							//========Ham xuat danh sách=========
{
	for (int i = 0; i < MAX; i++)
	{
		if (Heads[i] != NULL)
		{
			cout << "\n\n\t\t" << " Bucket " << i << endl;
			Phonebook* p = Heads[i];
			while (p != NULL)
			{
				cout << "\n\t\t\t" << p->data.Name + "\t\t" + p->data.NumberPhone + "\t\t" + p->data.Address << endl;
				p = p->Next;
			}
		}
	}
}

void FindName(Phonebook *Heads[])								//=========Ham tim kiếm theo tên=========
{
	ofstream fileout;
    string name;
	rewind(stdin);
	gotoXY(30, 10);
	cout << "Nhap ten hoac so hoac ky tu can tim kiem: ";
	getline(cin, name);
	fileout.open("Timkiem.txt", ios_base::out);
    SearchName(Heads, fileout, name);
    fileout.close();
	gotoXY(40, 5);
	cout << "NHAN PHIM << SPACE >> DE TRO VE !";
}

void FindNumber(Phonebook *Heads[])							//=========Hàm tìm kiếm theo số điện thoại========
{
	ofstream fileout;
    string name;
	rewind(stdin);
	gotoXY(50, 10);
	cout << "Nhap so dien thoai can tim kiem: ";
	getline(cin, name);
    fileout.open("Timkiem.txt", ios_base::out);
    SearchPhone(Heads, fileout, name);
    fileout.close();
	gotoXY(40, 5);
	cout << "NHAN PHIM << SPACE >> DE TRO VE !";
}

void FindAddress(Phonebook *Heads[])						//=======Hàm tìm kiếm theo địa chỉ===============
{
	ofstream fileout;
    string name;
	string Address;
	rewind(stdin);
	gotoXY(40, 10);
    cout << "Nhap dia chi can tim kiem: ";
	getline(cin, Address);
    fileout.open("Timkiem.txt", ios_base::out);
    SearchAddress(Heads, fileout, Address);
    fileout.close();
	gotoXY(40, 5);
	cout << "NHAN PHIM << SPACE >> DE TRO VE !";
}

void DelName(Phonebook *Heads[])								//==========Hàm xóa theo tên============
{
	ofstream fileout;
    string name;
    int dem = 0;
	rewind(stdin);
	cout << "\n\t\tNhap ten: ";
	getline(cin, name);
    dem = TimNode1(Heads, name);
    if (dem == 1)
    {
        DeleteToName(Heads, name);
        fileout.open("ListPhone1.txt", ios_base::out);
        DisplayToFile(Heads, fileout);
        fileout.close();
    }
    else if (dem > 1)
    {
        string number;
		rewind(stdin);
        cout << "\n\t\tNhap so dien thoai: ";
		getline(cin, number);
        DeleteToNumber(Heads, number);
        fileout.open("ListPhone1.txt", ios_base::out);
        DisplayToFile(Heads, fileout);
        fileout.close();
    }
	cout << "\n\t\tNHAN PHIM << SPACE >> DE TRO VE !";
}

void DelNumber(Phonebook *Heads[])									//==========Hàm xóa theo số ===================
{
	ofstream fileout;
	string number;
	gotoXY(40, 10);
    cout << "Nhap so dien thoai:";
    cin >> number;
    DeleteToNumber(Heads, number);
    fileout.open("ListPhone1.txt", ios_base::out);
    DisplayToFile(Heads, fileout);
    fileout.close();
	cout << "\n\n\t\tNHAN PHIM << SPACE >> DE TRO VE !";
}

void EditName(Phonebook *Heads[])            //============Hàm chỉnh sửa theo tên=============
{
	ofstream fileout;
    string name;
	rewind(stdin);
	gotoXY(40, 10);
	cout << "Nhap ten: ";
	getline(cin, name);
    fileout.open("ListPhone1.txt", ios_base::out);
    UpdateInfoToName(Heads, name);
    DisplayToFile(Heads, fileout);
    fileout.close();
	gotoXY(40, 5);
	cout << "   DA CHINH SUA THANH CONG !";
	gotoXY(40, 6);
	cout << "NHAN PHIM << SPACE >> DE TRO VE !";
}

void EditNumber(Phonebook *Heads[])							//===========Hàm chỉnh sửa theo số điện thoại=========
{
	ofstream fileout;
    string number;
	rewind(stdin);
	gotoXY(40, 10);
	cout << "Nhap so dien thoai: ";
	getline(cin, number);
    fileout.open("ListPhone1.txt", ios_base::out);
    UpdateInfoToNumber(Heads, number);
    DisplayToFile(Heads, fileout);
    fileout.close();
	gotoXY(40, 5);
	cout << "   DA CHINH SUA THANH CONG !";
	gotoXY(40, 6);
	cout << "NHAN PHIM << SPACE >> DE TRO VE !";
}


//=============== // PHẦN TẠO MENU ĐỘNG CHO CHƯƠNG TRÌNH QUẢN LÍ DANH BẠ //======================//


int x = 40, y = 12;
int w = 30, h = 2, t_color = 11, b_color = 1, b_color_sang = 75;

void SetColor(WORD color)                                  //Hàm đặt màu cho chữ 
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;
	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void textcolor(int x)       //Hàm đặt màu cho chữ
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}

void ShowCur(bool CursorVisibility)           // Hàm làm ẩn con trỏ chuột 
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}

void thanh_sang(int xp,int yp, int w, int h, int b_color, string nd)    //Hàm để tạo thanh sáng cho menu
{
	textcolor(b_color);
	for (int iy = yp + 1; iy <= yp + h - 1; iy++)
	{
		for (int ix = xp + 1; ix <= xp + w - 1; ix++)
		{
			gotoXY(ix, iy); cout << " ";
		}
	}
	SetColor(7);
	gotoXY(xp + 1, yp + 1);
	cout << nd;
}

void box(int x, int y, int w, int h, int t_color, int b_color, string nd)    //Hàm tạo một ô của menu động 
{
	textcolor(b_color);
	for (int iy = y + 1; iy <= y + h - 1; iy++)
	{
		for (int ix = x + 1; ix <= x + w - 1; ix++)
		{
			gotoXY(ix, iy); cout << " ";
		}
	}
	SetColor(7);
	gotoXY(x + 1, y + 1);
	cout << nd;
	textcolor(1);                //Vẽ viền cho menu
	SetColor(t_color);
	if (h <= 1 || w <= 1)return;
	for (int ix = x; ix <= x + w; ix++)
	{
		gotoXY(ix, y);
		cout << char(151);
		gotoXY(ix, y + h);
		cout << char(151);
	}
	for (int iy = y; iy <= y + h; iy++)
	{
		gotoXY(x, iy);
		cout <<"|";
		gotoXY(x + w, iy);
		cout << "|";
	}
	gotoXY(x, y); cout <<  char(149);
	gotoXY(x + w, y); cout << char(149);
	gotoXY(x, y + h); cout << char(149);
	gotoXY(x + w, y + h); cout << char(149);

}

void n_box(int x, int y, int w, int h, int t_color, int b_color, string nd[], int sl)   //Hàm tạo nhiều ô của menu động 
{
	for (int i = 0; i < sl; i++)
	{
		box(x, y + (i * 2), w, h, t_color, b_color, nd[i]);
		if (i != 0)
		{
			gotoXY(x, y + (i * 2)); cout << "|";
			gotoXY(x + w, y + (i * 2)); cout << "|";
		}
	}
}

void DisableResizeWindow()
{
	HWND hWnd = GetConsoleWindow();
	SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}

void DisableCtrButton(bool Close, bool Min, bool Max)
{
	HWND hWnd = GetConsoleWindow();
	HMENU hMenu = GetSystemMenu(hWnd, false);

	if (Close == 1)
	{
		DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
	}
	if (Min == 1)
	{
		DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
	}
	if (Max == 1)
	{
		DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
	}
}

enum stase											// enum lua chon chuc nang cua menu chinh 
{
	MENU = 0, ADD, OUTPUT, SEARCH, EDIT, DEL, EXIT
}stase;


//====================================//CÁC MENU CỦA CHƯƠNG TRÌNH//============================================//


void Input(Phonebook *Heads[])
{
	SetColor(15);
	gotoXY(10,0);
	cout << "\n\n";
	cout << "\t \t _______      _____      ____     ___ ___   ___       ________       _____       " << endl;
	cout << "\t \t . ...  .    .     .     .   .    . . . .   . .       . .   . .     .      .     " << endl;
	cout << "\t \t . .  . .   .  ___  .    . .   .  . . .  ___  .       . .  . .     .  ___   .    " << endl;
	cout << "\t \t . .  . .  .  _____  .   . . .    . . .  ___  .       . .  . .    .  _____   .   " << endl;
	cout << "\t \t . .... . .  .     .  .  . .   .    . . .   . .       . .   . .  .  .     .   .  " << endl;
	cout << "\t \t _______ ____       ____ ___    _____ ___   ___       ________  ____        ____ " << endl;
	cout << endl;
	gotoXY(7,9);
	SetColor(15);
	cout << "Nhan phim di chuyen << LEN >> hoac << XUONG >> de tuy chinh va nhan phim di chuyen << SANG PHAI >> de chon";
	ShowCur(0);
	string nd[3] = { "Nhap du lieu", "Thoat"};
	int sl = 2, i, j;
	n_box(x, y, w, h, t_color, b_color, nd, sl);
	int xp = x, yp = y;
	int xcu = xp; int ycu = yp;									//toa do anh sang
	bool kt = true;
	while(stase == ADD)
	{
		if (kt == true)											//------ in ----
		{
			i = abs((y - ycu) / 2);
			gotoXY(xcu, ycu);									//----- back space ----
			thanh_sang(xcu, ycu, w, h, b_color, nd[i]);          //rs thanh sang cu
			xcu = xp; ycu = yp;
			j = abs((y - ycu) / 2);
			thanh_sang(xp, yp, w, h, b_color_sang, nd[j]);
			kt = false;
		}
		if (_kbhit())											// dieu khien bang phim di chuyen tren ban phim
		{
			rewind(stdin);
			char c = _getch();
			if (c == -32)
			{
				kt = true;										// khi đã bấm
				c = _getch();
				if (c == 72)									// di chuyển xuống
				{
					if (yp != y)
						yp -= 2;
					else
					{
						yp = y + h * (sl - 1);
					}
				}
				else if (c == 80)							   //di chuyển lên
				{
					if (yp != y + h * (sl - 1))
						yp += 2;
					else
					{
						yp = y;
					}
				}
				else if (c == 77)
				{
					
					textcolor(b_color);
					ClearScreen();
					switch (j)
					{
						case 0:
						{
							ClearScreen();
							SetColor(15);
							EnterList(Heads);
    						gotoXY(50, 10);
    						cout << "DA NHAP DANH BA THANH CONG!";
    						gotoXY(47, 12);
    						cout << "NHAN PHIM << SPACE >> DE TRO VE !";
    						rewind(stdin);
							char t = _getch();
							if (t == 32)
							{								
								stase = MENU;
								ClearScreen();
							}
							break;
						}
						case 1:
						{
							stase = MENU;
							break;
						}
					}
				}
			}
		}
	}
}

void Output(Phonebook *Heads[])
{
	SetColor(15);
	gotoXY(10,0);
	cout << "\n\n";
	cout << "\t \t _______      _____      ____     ___ ___   ___       ________       _____       " << endl;
	cout << "\t \t . ...  .    .     .     .   .    . . . .   . .       . .   . .     .      .     " << endl;
	cout << "\t \t . .  . .   .  ___  .    . .   .  . . .  ___  .       . .  . .     .  ___   .    " << endl;
	cout << "\t \t . .  . .  .  _____  .   . . .    . . .  ___  .       . .  . .    .  _____   .   " << endl;
	cout << "\t \t . .... . .  .     .  .  . .   .    . . .   . .       . .   . .  .  .     .   .  " << endl;
	cout << "\t \t _______ ____       ____ ___    _____ ___   ___       ________  ____        ____ " << endl;
	cout << endl;
	gotoXY(7,9);
	SetColor(15);
	cout << "Nhan phim di chuyen << LEN >> hoac << XUONG >> de tuy chinh va nhan phim di chuyen << SANG PHAI >> de chon";
	ShowCur(0);
	string nd[3] = { "Xuat danh ba", "Thoat"};
	int sl = 2, i, j;
	n_box(x, y, w, h, t_color, b_color, nd, sl);
	int xp = x, yp = y;
	int xcu = xp; int ycu = yp;									//toa do anh sang
	bool kt = true;
	while (stase == OUTPUT)
	{
		if (kt == true)											//------ in ----
		{
			i = abs((y - ycu) / 2);
			gotoXY(xcu, ycu);									//----- back space ----
			thanh_sang(xcu, ycu, w, h, b_color, nd[i]);          //rs thanh sang cu
			xcu = xp; ycu = yp;
			j = abs((y - ycu) / 2);
			thanh_sang(xp, yp, w, h, b_color_sang, nd[j]);
			kt = false;
		}
		if (_kbhit())											// dieu khien bang phim di chuyen tren ban phim
		{
			rewind(stdin);
			char c = _getch();
			if (c == -32)
			{
				kt = true;										// khi đã bấm
				c = _getch();
				if (c == 72)									// di chuyển xuống
				{
					if (yp != y)
						yp -= 2;
					else
					{
						yp = y + h * (sl - 1);
					}
				}
				else if (c == 80)							   //di chuyển lên
				{
					if (yp != y + h * (sl - 1))
						yp += 2;
					else
					{
						yp = y;
					}
				}
				else if (c == 77)
				{
					textcolor(b_color);
					ClearScreen();
					gotoXY(40, 10);
					switch (j)
					{
						case 0:
						{
							ClearScreen();
							SetColor(15);
							Exportlist(Heads);
    						cout << "\n\t\t\t\t\t  DA XUAT DANH BA THANH CONG!\n";
    						cout << "\n\t\t\t\t\tNHAN PHIM << SPACE >> DE TRO VE !";
    						rewind(stdin);
							char t = _getch();
							if (t == 32)
							{								
								stase = MENU;
								ClearScreen();
							}
							break;
						}
						case 1:
						{
							stase = MENU;
							break;
						}
					}
				}
			}
		}
	}
}

void Del(Phonebook *Heads[])							// Menu cua ham xoa
{
	SetColor(15);
	gotoXY(10,0);
	cout << "\n\n";
	cout << "\t \t _______      _____      ____     ___ ___   ___       ________       _____       " << endl;
	cout << "\t \t . ...  .    .     .     .   .    . . . .   . .       . .   . .     .      .     " << endl;
	cout << "\t \t . .  . .   .  ___  .    . .   .  . . .  ___  .       . .  . .     .  ___   .    " << endl;
	cout << "\t \t . .  . .  .  _____  .   . . .    . . .  ___  .       . .  . .    .  _____   .   " << endl;
	cout << "\t \t . .... . .  .     .  .  . .   .    . . .   . .       . .   . .  .  .     .   .  " << endl;
	cout << "\t \t _______ ____       ____ ___    _____ ___   ___       ________  ____        ____ " << endl;
	cout << endl;
	gotoXY(7,9);
	SetColor(15);
	cout << "Nhan phim di chuyen << LEN >> hoac << XUONG >> de tuy chinh va nhan phim di chuyen<< SANG PHAI >> de chon";
	ShowCur(0);
	string nd[4] = { "Xoa theo ten", "Xoa theo so dien thoai", "Thoat"};
	int sl = 3, i, j;
	n_box(x, y, w, h, t_color, b_color, nd, sl);
	int xp = x, yp = y;
	int xcu = xp; int ycu = yp;									//toa do anh sang
	bool kt = true;
	while (stase == DEL)
	{
		if (kt == true)											//------ in ----
		{
			i = abs((y - ycu) / 2);
			gotoXY(xcu, ycu);									//----- back space ----
			thanh_sang(xcu, ycu, w, h, b_color, nd[i]);          //rs thanh sang cu
			xcu = xp; ycu = yp;
			j = abs((y - ycu) / 2);
			thanh_sang(xp, yp, w, h, b_color_sang, nd[j]);
			kt = false;
		}
		if (_kbhit())											// dieu khien bang phim di chuyen tren ban phim
		{
			rewind(stdin);
			char c = _getch();
			if (c == -32)
			{
				kt = true;										// khi đã bấm
				c = _getch();
				if (c == 72)									// di chuyển xuống
				{
					if (yp != y)
						yp -= 2;
					else
					{
						yp = y + h * (sl - 1);
					}
				}
				else if (c == 80)							   //di chuyển lên
				{
					if (yp != y + h * (sl - 1))
						yp += 2;
					else
					{
						yp = y;
					}
				}
				else if (c == 77)
				{
					textcolor(b_color);
					ClearScreen();
					gotoXY(40, 10);
					switch (j)
					{
						case 0:
						{
							ClearScreen();
							SetColor(15);
							DelName(Heads);
							rewind(stdin);
							char t = _getch();
							if (t == 32)
							{								
								stase = MENU;
								ClearScreen();
							}
							break;
						}
						case 1:
						{
							ClearScreen();
							SetColor(15);
							DelNumber(Heads);
							rewind(stdin);
							char t = _getch();
							if (t == 32)
							{
								stase = MENU;
								ClearScreen();
							}
							break;
						}
						case 2:
						{
							ClearScreen();
							stase = MENU;
							break;
						}
					}
				}
			}
		}
	}
}

void Edit(Phonebook *Heads[])							//Menu cua ham chinh sua
{
	SetColor(15);
	gotoXY(10,0);
	cout << "\n\n";
	cout << "\t \t _______      _____      ____     ___ ___   ___       ________       _____       " << endl;
	cout << "\t \t . ...  .    .     .     .   .    . . . .   . .       . .   . .     .      .     " << endl;
	cout << "\t \t . .  . .   .  ___  .    . .   .  . . .  ___  .       . .  . .     .  ___   .    " << endl;
	cout << "\t \t . .  . .  .  _____  .   . . .    . . .  ___  .       . .  . .    .  _____   .   " << endl;
	cout << "\t \t . .... . .  .     .  .  . .   .    . . .   . .       . .   . .  .  .     .   .  " << endl;
	cout << "\t \t _______ ____       ____ ___    _____ ___   ___       ________  ____        ____ " << endl;
	cout << endl;
	gotoXY(7,9);
	SetColor(15);
	cout << "Nhan phim di chuyen << LEN >> hoac << XUONG >> de tuy chinh va nhan phim di chuyen << SANG PHAI >> de chon";
	ShowCur(0);
	string nd[4] = { "Sua ten", "Sua so dien thoai ", "Thoat"};
	int sl = 3, i, j;
	n_box(x, y, w, h, t_color, b_color, nd, sl);
	int xp = x, yp = y;
	int xcu = xp; int ycu = yp;									//toa do anh sang
	bool kt = true;
	while (stase == EDIT)
	{
		if (kt == true)											//------ in ----
		{
			i = abs((y - ycu) / 2);
			gotoXY(xcu, ycu);									//----- back space ----
			thanh_sang(xcu, ycu, w, h, b_color, nd[i]);          //rs thanh sang cu
			xcu = xp; ycu = yp;
			j = abs((y - ycu) / 2);
			thanh_sang(xp, yp, w, h, b_color_sang, nd[j]);
			kt = false;
		}
		if (_kbhit())											// dieu khien bang phim di chuyen tren ban phim
		{
			rewind(stdin);
			char c = _getch();
			if (c == -32)
			{
				kt = true;										// khi đã bấm
				c = _getch();
				if (c == 72)									// di chuyển xuống
				{
					if (yp != y)
						yp -= 2;
					else
					{
						yp = y + h * (sl - 1);
					}
				}
				else if (c == 80)							   //di chuyển lên
				{
					if (yp != y + h * (sl - 1))
						yp += 2;
					else
					{
						yp = y;
					}
				}
				else if (c == 77)
				{
					textcolor(b_color);
					ClearScreen();
					gotoXY(40, 10);
					switch (j)
					{
						case 0:
						{
							ClearScreen();
							SetColor(15);
							EditName(Heads);
							rewind(stdin);
							char t = _getch();
							if (t == 32)
							{
								stase = MENU;
								ClearScreen();
							}
							break;
						}
						case 1:
						{
							ClearScreen();
							SetColor(15);
							ofstream fileout;
							EditNumber(Heads);
							rewind(stdin);
							char t = _getch();
							if (t == 32)
							{
								stase = MENU;
								ClearScreen();
							}
							break;
						}
						case 2:
						{
							ClearScreen();
						 	stase = MENU;
							break;
						}
					}
				}
			}
		}
	}
}

void Search(Phonebook *Heads[])						//Menu cua ham tim kiem
{
	SetColor(15);
	gotoXY(10,0);
	cout << "\n\n";
	cout << "\t \t _______      _____      ____     ___ ___   ___       ________       _____       " << endl;
	cout << "\t \t . ...  .    .     .     .   .    . . . .   . .       . .   . .     .      .     " << endl;
	cout << "\t \t . .  . .   .  ___  .    . .   .  . . .  ___  .       . .  . .     .  ___   .    " << endl;
	cout << "\t \t . .  . .  .  _____  .   . . .    . . .  ___  .       . .  . .    .  _____   .   " << endl;
	cout << "\t \t . .... . .  .     .  .  . .   .    . . .   . .       . .   . .  .  .     .   .  " << endl;
	cout << "\t \t _______ ____       ____ ___    _____ ___   ___       ________  ____        ____ " << endl;
	cout << endl;
	gotoXY(7,9);
	SetColor(15);
	cout << "Nhan phim di chuyen << LEN >> hoac << XUONG >> de tuy chinh va nhan phim di chuyen << SANG PHAI >> de chon";
	ShowCur(0);
	string nd[5] = { "Tim kiem theo ten", "Tim kiem theo so dien thoai","Tim kiem theo dia chi", "Thoat"};
	int sl = 4, i, j;
	n_box(x, y, w, h, t_color, b_color, nd, sl);
	int xp = x, yp = y;
	int xcu = xp; int ycu = yp;									//toa do anh sang
	bool kt = true;
	while (stase == SEARCH )
	{
		if (kt == true)											//------ in ----
		{
			i = abs((y - ycu) / 2);
			gotoXY(xcu, ycu);									//----- back space ----
			thanh_sang(xcu, ycu, w, h, b_color, nd[i]);          //rs thanh sang cu
			xcu = xp; ycu = yp;
			j = abs((y - ycu) / 2);
			thanh_sang(xp, yp, w, h, b_color_sang, nd[j]);
			kt = false;
		}
		if (_kbhit())											// dieu khien bang phim di chuyen tren ban phim
		{
			rewind(stdin);
			char c = _getch();
			if (c == -32)
			{
				kt = true;										// khi đã bấm
				c = _getch();
				if (c == 72)									// di chuyển xuống
				{
					if (yp != y)
						yp -= 2;
					else
					{
						yp = y + h * (sl - 1);
					}
				}
				else if (c == 80)							   //di chuyển lên
				{
					if (yp != y + h * (sl - 1))
						yp += 2;
					else
					{
						yp = y;
					}
				}
				else if (c == 77)
				{
					textcolor(b_color);
					ClearScreen();
					switch (j)
					{
						case 0:
						{
							ClearScreen();
							SetColor(15);	
							FindName(Heads);
							rewind(stdin);
							char t = _getch();
							if (t == 32)
							{
								stase = MENU;
								ClearScreen();
							}
							break;
						}
						case 1:
						{
							ClearScreen();
							SetColor(15);
							FindNumber(Heads);
							rewind(stdin);
							char t = _getch();
							if (t == 32)
							{
								stase = MENU;
								ClearScreen();
							}
							break;
						}
						case 2:
						{
							ClearScreen();
							SetColor(15);
						 	FindAddress(Heads);
							rewind(stdin);
							char t = _getch();
							if (t == 32)
							{
								stase = MENU;
								ClearScreen();
							}
							break;
						}
						case 3:
						{
							ClearScreen();
							stase = MENU;
							break;
						}
					}
				}
			}
		}
	}
}

void Menu(Phonebook *Heads[])							//Menu chinh cua chuong trinh
{
	SetColor(15);
	gotoXY(28, 1);
	cout << " CHAO MUNG BAN DEN VOI CHUONG TRINH QUAN LI DANH BA ";
	gotoXY(10,0);
	cout << "\n\n";
	cout << "\t \t _______      _____      ____     ___ ___   ___       ________       _____       " << endl;
	cout << "\t \t . ...  .    .     .     .   .    . . . .   . .       . .   . .     .      .     " << endl;
	cout << "\t \t . .  . .   .  ___  .    . .   .  . . .  ___  .       . .  . .     .  ___   .    " << endl;
	cout << "\t \t . .  . .  .  _____  .   . . .    . . .  ___  .       . .  . .    .  _____   .   " << endl;
	cout << "\t \t . .... . .  .     .  .  . .   .    . . .   . .       . .   . .  .  .     .   .  " << endl;
	cout << "\t \t _______ ____       ____ ___    _____ ___   ___       ________  ____        ____ " << endl;
	cout << endl;
	gotoXY(7,9);
	SetColor(15);
	cout << "Nhan phim di chuyen << LEN >> hoac << XUONG >> de tuy chinh va nhan phim di chuyen << SANG PHAI >> de chon";
	ShowCur(0);
	string nd[7] = { "Nhap du lieu", "Xuat danh sach","Tim kiem","Chinh sua", "Xoa", "Thoat"};
	int sl = 6, i, j;
	n_box(x, y, w, h, t_color, b_color, nd, sl);
	int xp = x, yp = y;
	int xcu = xp; int ycu = yp;									//toa do anh sang
	bool kt = true;
	while (stase == MENU)
	{
		if (kt == true)											//------ in ----
		{
			i = abs((y - ycu) / 2);
			gotoXY(xcu, ycu);									//----- back space ----
			thanh_sang(xcu, ycu, w, h, b_color, nd[i]);          //rs thanh sang cu
			xcu = xp; ycu = yp;
			j = abs((y - ycu) / 2);
			thanh_sang(xp, yp, w, h, b_color_sang, nd[j]);
			kt = false;
		}
		if (_kbhit())											// dieu khien bang phim di chuyen tren ban phim
		{
			rewind(stdin);
			char c = _getch();
			if (c == -32)
			{
				kt = true;										// khi đã bấm
				c = _getch();
				if (c == 72)									// di chuyển xuống
				{
					if (yp != y)
						yp -= 2;
					else
					{
						yp = y + h * (sl - 1);
					}
				}
				else if (c == 80)							   //di chuyển lên
				{
					if (yp != y + h * (sl - 1))
						yp += 2;
					else
					{
						yp = y;
					}
				}
				else if (c == 77)
				{
					textcolor(b_color);
					ClearScreen();
					gotoXY(40, 10);
					switch (j)
					{
						case 0:
						{
							stase = ADD;
							break;
						}
						case 1:
						{
							stase = OUTPUT;
							break;
						}
						case 2:
						{
						 	stase = SEARCH;
							break;
						}
						case 3:
						{
							stase = EDIT;
							break;
						}
						case 4:
						{
							stase = DEL;
							break;
						}
						case 5:
						{
							//cout << "Thoat!";
							stase = EXIT;
							break;
						}
					}
				}
			}
		}
	}
}


//===================================// HÀM MAIN //===============================//


int main()
{
	//====== Phần chỉnh màn hình console của chương trình ================//

	DisableCtrButton(0, 1, 1);
	DisableResizeWindow();
	SetConsoleTitle(L"PHONE_BOOK");

	//=======================================================================//
	
	Phonebook *Heads[MAX];
    Init(Heads);
    ReadListPhone(Heads);
	SetColor(15);

	//=============== điều khiển menu động ========================//

	stase = MENU;
	Menu(Heads);
	while(true)
	{
		switch(stase)
		{
			case MENU:
			{
				Menu(Heads);
				break;
			}
			case ADD:
			{
				Input(Heads);
				break;
			}
			case OUTPUT:
			{
				Output(Heads);
				break;
			}
			case SEARCH:
			{
				Search(Heads);
				break;
			}
			case EDIT:
			{
				Edit(Heads);
				break;
			}
			case DEL:
			{
				Del(Heads);
				break;
			}
			case EXIT:
			{
				SetColor(15);
				return 0;
			}
		}
	}
}

//////////==========================//   KẾT THÚC //===============================//////////