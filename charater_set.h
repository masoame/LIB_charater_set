#pragma once

#define EXPORT
#ifndef EXPORT
#define API_charater_set __declspec(dllimport)
#else
#define API_charater_set __declspec(dllexport)
#endif 


#define localtion  0
#define shift_jis  932
#define gb2312     936
#define GB18030    54936
#define big5       950
#define utf_8      65001

class API_charater_set charater_set
{
public:
		char* in, * res;
		wchar_t* w_buf;
		int w_size;

		virtual char* file_to_char(const wchar_t* path, int& size);
		virtual bool  char_to_file(const wchar_t* path, char* buf, int size);
		virtual char* code_to_code(char* in, int in_size, int& res_size, int = 0, int = 0);
		charater_set();
		virtual ~charater_set();
};

extern "C" API_charater_set charater_set * Create_charater_set();
extern "C" API_charater_set void Free_charater_set(charater_set * data);
