#pragma once

#include<iostream>
#include<string>

using namespace std;

//Tip
//VS��ʾ "�ҵ�һ���������ض���ķ���" ����취:
//��ʱ����calss�ں�������Ϊstatic����(��֤������Ϊ���߽���ִ��һ��)
//�������к���

static void outMsg(int mode, _In_z_ _Printf_format_string_ char const* const _Format, ... )
{
	switch (mode)
	{
		case 0:
			cout << "-Message: ";
			break;
		case 1:
			cout << "-Warn: ";
			break;
		case 2:
			cout << "-Error: ";
			break;
		default:
			return;
			break;
	}
	
	va_list _ArgList;
	__crt_va_start(_ArgList, _Format);
	_vfprintf_l(stdout, _Format, NULL, _ArgList);
	__crt_va_end(_ArgList);

	cout << endl;
}
//�ɱ����,���printf����Դ��
//�˺����ڽ������Զ���ӻس�

class YcBiter
{
#define DEFAULT_CLASS_ID -1
public:
	~YcBiter();
	YcBiter(int length,int id = DEFAULT_CLASS_ID);
	YcBiter(int length,bool * inData, int id = DEFAULT_CLASS_ID);//���Կ�¡
	
	bool Widen_EmptySide(int n, bool true2left_OR_false2right);////mode == trueʱ�ؿ����(ֵ����),mode == falseʱ�ؿ��ұ�(��λ���λ�ƶ�)
	//�ɹ�ʱ����tre
	bool Flush_bData(int n);
	//�ɹ�ʱ����true
	
	void CoverWrite(bool data[], int inLength);
	void CoverWrite_RoughString(string str)
	{
		CoverWrite(strToBool_CWS(str), str.length());
	}
	void ForceWriteCurrent(bool v)
	{
		_bData[_current] = v;
	}
	bool Safe_SetCurrent(int n) 
	{ 
		if (_current < 0)	return false;
		_current = n;
		return true;
	}
	//�������޸�_currentΪС��0��ֵ

	void Debug_OutMsgShow_Bit(void)
	{
		outMsg(0, GetRoughDataString().c_str()); 
	}
	void Debug_OutMsgShow_Hex(bool format = true)
	{
		int tlen,l_distance;
		for (tlen = _length; tlen % 8 != 0; tlen++) {} //���䵽�ܱ�8λ2����������
		l_distance = _length - tlen;

		string str;
		int rev = 0;
		for (int i = 0; i <= tlen; i++)
		{
			if (i < l_distance)
			{
				continue;
			}
			else
			{
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
					//i��Ҫ����tlen���ڽ���,��Ϊ�˷�ֹ������������Ҫ��break
				}
				if(_bData[i])
					rev += pow(2, 3 - (i % 4));
				else
				{
					//do nothing
				}
			}
		}
		outMsg(0, str.c_str());
	}
	int Debug_GetLen()
	{
		return _length;
	}
private:
	const int _classID;
	int _length;
	int _current = 0;
	bool * _bData = NULL;
	bool * strToBool_CWS(string str)
	{
		bool * pOut = new bool[str.length()];
		for (int i = 0; i < (int)str.length(); i++)
		{
			if (str[i] == '0')
				pOut[i] = false;
			else
				pOut[i] = true;
		}
		return pOut;
	}
	//��������,������"1000100100"�����stringתΪbool������
	//-->CWS<-- ָCoverWrite_S,�˺����ڷ����������Ӧ��ֻ��
	//YcBiter_CoverWrite_S���������ƺ������ʹ��,�����Ұ�������private��
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
