#pragma once

#include<iostream>
#include<string>

using namespace std;

//Tip
//VS��ʾ "�ҵ�һ���������ض���ķ���" ����취:
//��ʱ����calss�ں�������Ϊstatic����(��֤������Ϊ���߽���ִ��һ��)
//�������к���

//static void outMsg(int mode, _In_z_ _Printf_format_string_ char const* const _Format, ... )
//{
//	switch (mode)
//	{
//		case 0:
//			cout << "-Message: ";
//			break;
//		case 1:
//			cout << "-Warn: ";
//			break;
//		case 2:
//			cout << "-Error: ";
//			break;
//		default:
//			return;
//			break;
//	}
//	
//	va_list _ArgList;
//	__crt_va_start(_ArgList, _Format);
//	_vfprintf_l(stdout, _Format, NULL, _ArgList);
//	__crt_va_end(_ArgList);
//
//	cout << endl;
//}
//�ɱ����,���printf����Դ��-�˺����ڽ������Զ���ӻس�
//������bug,ĳЩ�����������ʾ�������,δ�Ų�
//��2020��7��8������

class YcBiter
{
public:
	~YcBiter();
	YcBiter(int id = _Const_DefaultClassID_YcBiter) : _classID(id) {}
	YcBiter(int length,int id = _Const_DefaultClassID_YcBiter);
	YcBiter(int length,bool * inData, int id = _Const_DefaultClassID_YcBiter);//���Կ�¡
	
	bool Widen_EmptySide(int n, bool true2left_OR_false2right);////mode == trueʱ�ؿ����(ֵ����),mode == falseʱ�ؿ��ұ�(��λ���λ�ƶ�)
	//�ɹ�ʱ����tre
	bool Flush_bData(int n);
	//�ɹ�ʱ����true
	
	void CoverWrite(bool data[], int inLength);
	void CoverWrite_RoughString(string str)
	{
		string str2 = "";
		for (int i = 0; i < (int)str.length(); i++)
		{
			if (str[i] == ' '||str[i]=='	')
				continue;
			str2 += str[i];
		}

		CoverWrite(strToBool_RS(str2), str2.length());
	}

	//void Debug_OutMsgShow_Bit(void)
	//{
	//	outMsg(0, GetRoughDataString().c_str()); 
	//}
	//��2020��7��8������

	string Debug_Get_bData_Hex(bool format = true)
	{
		string str;
		if (!format)
			str += "0x";
		int tlen;
		for (tlen = _length; tlen % 8 != 0; tlen++) {} //���䵽8λ
		int l_distance = tlen - _length;

		int rev = 0;
		for (int i = 0; i <= tlen; i++)//�� if (i == tlen) ������
		{
			if (i < l_distance)
			{
				continue;
			}
			if (i % 4 == 0 && i != 0)
			{
				if (rev < 10)
				{
					str += (char)('0' + rev);
				}
				else 
				{
					str += (char)('A' + rev - 10);
				}
				if (i == tlen)	int b = 0;
				if (format && i%8 == 0)
					str += ' ';
				rev = 0;
			}

			if (i == tlen)
			{
				break;
				//i��Ҫ����tlen(Ҳ���ǳ���Ϊtlen+1)���ڽ������һλ
				//��Ϊ�˷�ֹ������������Ҫ��break
			}

			if (_bData[i-l_distance])
			{
				rev += (int)pow(2, 3 - (i% 4));
			}
		}
		return str;
	}
	int Debug_GetLen()
	{
		return _length;
	}

	static const int _Const_DefaultClassID_YcBiter = -1;
private:
	const int _classID;
	int _length;
	bool * _bData = NULL;
	bool * strToBool_RS(string str2)
	{
		bool * pOut = new bool[str2.length()];
		for (int i = 0; i < (int)str2.length(); i++)
		{
			if (str2[i] == '0')
				pOut[i] = false;
			else
				pOut[i] = true;
		}
		return pOut;
	}
	//��������,������"1000100100"�����stringתΪbool������
	//-->CWS<-- ָCoverWrite_S,�˺����ڷ����������Ӧ��ֻ��
	//YcBiter_CoverWrite_RoughString���������ƺ������ʹ��,�����Ұ�������private��
	string GetRoughDataString()
	{
		string dstr;
		for (int i = 0; i < _length; i++)
		{
			if (_bData[i])
				dstr += "1";
			else
				dstr += "0";
		}
		return dstr;
	}
	//��������"10001010"���ַ���,������raw
};
