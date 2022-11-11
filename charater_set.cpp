#include<windows.h>
#include<iostream>
#include<fstream>
#include"charater_set.h"
using namespace std;


char* charater_set::file_to_char(const wchar_t* path, int& size)
{
	ifstream file_in(path, ios::in | ios::ate | ios::binary);
	if (!file_in) { cout << "open the file failed" << endl; return nullptr; }
	size = file_in.tellg();

	if (in == nullptr)
		in = new char[size + 1];
	else
	{
		delete[] in;
		in = new char[size + 1];
	}

	file_in.seekg(SEEK_SET);
	file_in.read(in, size);
	in[size] = 0;
	file_in.close();
	return in;
}

bool charater_set::char_to_file(const wchar_t* path, char* res, int size)
{
	ofstream file_out(path, ios::out | ios::binary);
	if (!file_out) { cout << "open the file failed" << endl; return false; }

	file_out.write(res, size);

	file_out.close();
	return true;
}

char* charater_set::code_to_code(char* in, int in_size, int& res_size, int oringal, int result)
{
	w_size = MultiByteToWideChar(oringal, 0, in, -1, NULL, 0);					//orinal���룬��ȡwchar_tԤ������
	if (w_buf == nullptr)														//�����ڴ��С
		w_buf = new wchar_t[w_size];
	else
	{
		delete[] w_buf;
		w_buf = new wchar_t[w_size];
	}
	w_buf[w_size - 1] = 0;														//�ַ���������
	MultiByteToWideChar(oringal, 0, in, -1, w_buf, w_size);						//ת��Ϊwchar_t

	res_size = WideCharToMultiByte(result, 0, w_buf, -1, NULL, 0, NULL, NULL);	//CP_ACPΪ���ر��룬��ȡcharԤ������
	if (res == nullptr)															//�����ڴ��С
		res = new char[res_size];
	else
	{
		delete[] res;
		res = new char[res_size];
	}
	res[res_size - 1] = 0;														//�ַ���������
	WideCharToMultiByte(result, 0, w_buf, -1, res, res_size, NULL, NULL);		//ת��Ϊ���ر���

	return res;
}

charater_set::charater_set()
{
	in = nullptr;
	res = nullptr;
	w_buf = nullptr;
	w_size = 0;
}

charater_set::~charater_set()
{
	if (in != nullptr)
		delete[] in;
	if (res != nullptr)
		delete[] res;
	if (w_buf != nullptr)
		delete[] w_buf;
}

charater_set* Create_charater_set()
{
	return new charater_set;
}

void Free_charater_set(charater_set* data)
{
	delete data;
}
