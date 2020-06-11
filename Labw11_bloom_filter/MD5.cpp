#include "MD5.hpp"
#include <iostream>
#include <bitset>
#include <math.h>
using namespace std;

int GGindex[64] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15, 1, 6,11, 0, 5,10,15, 4, 9, 14, 3, 8,13, 2, 
7,12,5, 8,11,14, 1, 4, 7,10,13, 0, 3, 6, 9,12,15, 2,0, 7,14, 5,12, 3,10, 1, 8,15, 6,13, 4,11, 2, 9 };
int s[64] = { 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20 , 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23 , 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 };
unsigned int T[64] = { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
						0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
						0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
						0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
						0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
						0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
						0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
						0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };



MD5::MD5()
{
	A = 0x67452301;
	B = 0xEFCDAB89;
	C = 0x98BADCFE;
	D = 0x10325476;
}

MD5::~MD5()
{
	
}

unsigned int output(int a)//С�˹���
{
	unsigned int res = 0;
	for (int i = 0; i < 4; i++)
	{
		int temp = a & 0xff;
		res = (res << 8) | temp;
		a = a >> 8;
	}
	return res;
}

void MD5::read(string str)
{
	unsigned int big_temp[1000] = {0};
	unsigned int sub_GGindex = 0;
	unsigned int temp;
	big_temp[sub_GGindex] = 0;
	int i;
	long long int   count = str.length() * 8;
	for (i = 0; i < str.length(); i++)//transfer message
	{
		temp = str[i];
		big_temp[sub_GGindex] += temp << ((i % 4) * 8);
		if (i % 4 == 3)
			sub_GGindex++;
	}

	temp = 0x80;//padding
	big_temp[sub_GGindex] += temp << ((i % 4) * 8);
	if (i % 4 == 3)
		sub_GGindex++;
	i++;
	temp = 0x00;
	while ((i * 8) % 512 != 448)
	{
		big_temp[sub_GGindex] += temp << ((i % 4) * 8);
		if (i % 4 == 3)
			sub_GGindex++;
		i++;
	}
	big_temp[sub_GGindex++] = (count << 32) >> 32;
	big_temp[sub_GGindex] = count >> 32;
	unsigned int * M;
	for (int i = 0; i <= sub_GGindex; i++)//add message block to MessageFlow
	{
		if (i % 16 == 0)
		{
			M = new unsigned int[16];
		}
		else if (i % 16 == 15)
		{
			MessageFlow.push_back(M);
		}
		M[i % 16] = big_temp[i];
	}
	/*
	�˴����ڽ��������Ϣprint��������Ҫ��֤��С�˴洢�������Ƿ���ִ���
	for (int i = 0; i < MessageFlow.size(); i++)
	{
		for (int j = 0; j < 16; j++)
		{
			printf("%x ", MessageFlow[i][j]);
		}
		cout << endl;
	}
	*/

}

unsigned int g2(int i, unsigned int b, unsigned int c, unsigned int d) {
	switch (i)
	{
	case 0:return (b & c) | (~b & d);
	case 1:return (b & d) | (c & ~d);
	case 2:return b ^ c ^ d;
	default:return c ^ (b | ~d);
	}
}

void MD5::HMD5(int q)
{
	unsigned int a, b, c, d;
	a = A;
	b = B;
	c = C;
	d = D;
	unsigned int temp;
	unsigned int X, sub_GGindex;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			sub_GGindex = i * 16 + j;
			X = MessageFlow[q][GGindex[sub_GGindex]];
			temp = a + g2(i, b, c, d) + X + T[sub_GGindex];
			/*
				�˴�������ǹٷ��������ݵ��������֤�����Ƿ������ע:T��Ȼ������ʱ���㣬���ҿ��ܶ�����
				�͹ٷ����붼��ʹ���ֳɵ�Tֵ�����ҳ��Թ�ֱ���㣬һ��ʼ������ǶԵģ���������˺ܶ࣬��˽���
				��T�������飬ֱ��ʹ�þͺá�
				cout << GGindex[sub_GGindex] << " " << T[sub_GGindex] << " " << s[sub_GGindex] << endl;
			*/
			temp = (temp << s[sub_GGindex]) | (temp >> (32 - s[sub_GGindex]));
			a = b + temp;
			/*
				�˴��������a����a�����ȷ��˵�����ϲ��趼����ȷ�ġ�
				printf("%x\n",a);
			*/
			temp = d;
			d = c;
			c = b;
			b = a;
			a = temp;
		}
	}
	A = A + a;
	B = B + b;
	C = C + c;
	D = D + d;
}

unsigned int MD5::Encryption()
{
	D = 0x10325476;
	for (int i = 0; i < MessageFlow.size(); i++)
		HMD5(i);
	return output(D);
}




