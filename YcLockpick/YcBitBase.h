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
	YcBiter(int length, int id = _Const_DefaultClassID_YcBiter);
	YcBiter(int length, bool * inData, int id = _Const_DefaultClassID_YcBiter);//���Կ�¡

	bool Widen_EmptySide(int n, bool true2left_OR_false2right);//mode == trueʱ�ؿ����(ֵ����),mode == falseʱ�ؿ��ұ�(��λ���λ�ƶ�),�ɹ�ʱ����tre
	bool Flush_bData(int n);	//�ɹ�ʱ����true
	void CoverWrite(bool data[], int inLength);
	void CoverWrite_RoughString(string str);
	//	void Debug_OutMsgShow_Bit(void) ��2020��7��8������
	string Debug_Get_bData_Hex(bool format = true);
	int Debug_GetLen() { return _length; }
	int Length() { return _length; }
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
