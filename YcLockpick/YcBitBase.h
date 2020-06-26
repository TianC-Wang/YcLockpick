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
	YcBiter(int length,bool * inData, int id);//����YcBiter::Clone();
	
	bool Widen_EmptySide(int n, bool mode);
	//mode == trueʱ�ؿ����(ֵ����),mode == falseʱ�ؿ��ұ�(��λ���λ�ƶ�)
	//�ɹ�ʱ����tre
	bool Flush_bData(int n);
	//�ɹ�ʱ����true
	string GetRoughDataString();
	void CoverWrite(bool data[], int inLength);
	void CoverWrite_S(string str);

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

	void Debug_OutMsgShow(void)
	{
		outMsg(0, GetRoughDataString().c_str()); 
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

};
