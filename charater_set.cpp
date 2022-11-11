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
	w_size = MultiByteToWideChar(oringal, 0, in, -1, NULL, 0);					//orinal编码，获取wchar_t预估长度
	if (w_buf == nullptr)														//申请内存大小
		w_buf = new wchar_t[w_size];
	else
	{
		delete[] w_buf;
		w_buf = new wchar_t[w_size];
	}
	w_buf[w_size - 1] = 0;														//字符串结束符
	MultiByteToWideChar(oringal, 0, in, -1, w_buf, w_size);						//转码为wchar_t

	res_size = WideCharToMultiByte(result, 0, w_buf, -1, NULL, 0, NULL, NULL);	//CP_ACP为本地编码，获取char预估长度
	if (res == nullptr)															//申请内存大小
		res = new char[res_size];
	else
	{
		delete[] res;
		res = new char[res_size];
	}
	res[res_size - 1] = 0;														//字符串结束符
	WideCharToMultiByte(result, 0, w_buf, -1, res, res_size, NULL, NULL);		//转码为本地编码

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
