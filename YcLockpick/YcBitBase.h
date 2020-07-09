#pragma once

#include<iostream>
#include<string>

using namespace std;

class YcBiter
{
public:
	~YcBiter();
	YcBiter() : _classID(-1/*_Const_DefaultClassID_YcBiter*/) {}
	YcBiter(int length, int id = _Const_DefaultClassID_YcBiter);
	YcBiter(int length, bool * inData, int id = _Const_DefaultClassID_YcBiter);//���Կ�¡

	//----ConstValueDefinitionArea----
	static const int _Const_DefaultClassID_YcBiter = -1;

	//----UsefulArea
	bool Widen_EmptySide(int n, bool true2left_OR_false2right);//mode == trueʱ�ؿ����(ֵ����),mode == falseʱ�ؿ��ұ�(��λ���λ�ƶ�),�ɹ�ʱ����tre
	bool Flush_bData(int n);	//�ɹ�ʱ����true
	void CoverWrite(bool data[], int inLength);
	void CoverWrite_RoughString(string str);
//	void Debug_OutMsgShow_Bit(void) ��2020��7��8������
	int Length() { return _length; }
	
	//----DEBUG&ShowArea
	bool dumpTo8BitArray(int nBytes,unsigned char address[]);//�ɹ�ʱ����true
	int Debug_GetLen() { return _length; }
	string Debug_GetRoughDataString();//��������"10001010"���ַ���,������raw
	string Debug_Get_bData_Hex(bool format = true);
	
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
	}//��������,������"1000100100"�����stringתΪbool������ \n CWSָCoverWrite_S,�˺����ڷ����������Ӧ��ֻ��YcBiter_CoverWrite_RoughString���������ƺ������ʹ��,�����Ұ�������private��
};

class YcComputableBiter : YcBiter
{
public:
	YcComputableBiter(int length, int id = _Const_DefaultClassID_YcBiter) : YcBiter(length,id)
	{

	}
private:
};