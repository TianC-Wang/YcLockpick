#pragma once

#include<iostream>
#include<string>

using namespace std;

class YcBiter
{
public:

	~YcBiter()
	{
		cout << "Exiting!!" << endl;
		deleteBuffer_bData();
	}

	//----ConstValueDefinitionArea----
	static const int _Const_DefaultClassID_YcBiter = -1;

	//----Construction----
	
	YcBiter(void) : _classID(_Const_DefaultClassID_YcBiter) 
	{
		_length = 1;
		_bData = new bool[1];
	}
	YcBiter(int length, int id = _Const_DefaultClassID_YcBiter);
	YcBiter(int length, bool * inData, int id = _Const_DefaultClassID_YcBiter);//���Կ�¡


	//----UseageArea
	bool Widen_EmptySide(int n, bool true2left_OR_false2right);//mode == trueʱ�ؿ����(ֵ����),mode == falseʱ�ؿ��ұ�(��λ���λ�ƶ�),�ɹ�ʱ����tre
	bool Flush_bData(int n);	//�ɹ�ʱ����true
	void CoverWrite(bool * data, int inLength);
	void CoverWrite_RoughString(string str);
//	void Debug_OutMsgShow_Bit(void) ��2020��7��8������
	int Length() { return _length; }
	
	//----DEBUG&ShowArea
	bool dump8BitArray(int nBytes,unsigned char address[]);//�ɹ�ʱ����true, address��delete��Ҫ�ֶ�����
	bool * GetBoolArray(int nbitslength);
	int Debug_GetLen() { return _length; }
	string Debug_GetRoughDataString();//��������"10001010"���ַ���,������raw
	string Debug_Get_bData_Hex(bool format = true);
	
private:
	
	bool * deleteBuffer_bData(void)
	{
		delete[] _bData;	 _bData = NULL;
		_length = 0;
		return _bData;
	}
	//�����µ�_bData��ָ��ĵ�ַ(����Ӧ����NULL)

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
protected:

	bool * _bData = NULL;
	int _length = 0;
	const int _classID;

private:
	//friend class YcBiterComputable;
};

class YcBiterComputable : public YcBiter
{
public:
	~YcBiterComputable()
	{
		
	}
	//----Construction----
	YcBiterComputable(void): YcBiter()
	{
		
	}
	YcBiterComputable(int length, int id = _Const_DefaultClassID_YcBiter) : YcBiter(length,id){}

	//bool XOR_sameWidth(YcBiter & a, YcBiter & b);
	bool XOR_sameWidth(bool * a, bool * b);
private:
	
};