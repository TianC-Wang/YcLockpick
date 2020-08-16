#pragma once

#include<iostream>
#include<string>

using namespace std;

class YcBiter
{
public:
	~YcBiter()
	{
		deleteBuffer_bData();
	}

	//----Constructions----
	YcBiter(void)
	{
		_length = 1;
		_bData = new bool[1];
		*_bData = false;
	}
	//Default Length for 1
	YcBiter(int length);
	YcBiter(int length, bool * inData);//���Կ�¡
	YcBiter(string str) {
		CoverWrite_RoughString(str);
	}

	//----UseageArea
	bool Widen_EmptySide(int n, bool true2left_OR_false2right);//mode == trueʱ�ؿ����(ֵ����),mode == falseʱ�ؿ��ұ�(��λ���λ�ƶ�),�ɹ�ʱ����tre
	bool Flush_bData(int n);	//�ɹ�ʱ����true
	void CoverWrite(bool * data, int inLength);
	void CoverWrite_RoughString(string str);
	int Length() { return _length; }
	
	//----DEBUG&ShowArea
	bool dump8BitArray(int nBytes,unsigned char address[]);//�ɹ�ʱ����true, address��delete��Ҫ�ֶ�����
	bool * GetBoolArray(int nbitslength);
	int Debug_GetLen() { return _length; }
	string Debug_GetRoughDataString();//��������"10001010"���ַ���,������raw
	string Debug_Get_bData_Hex(bool format = true);
	
protected:
	bool * deleteBuffer_bData(void);
	bool * strToBool_RS(string str2);
	
	bool * _bData = NULL;
	int _length = 0;

};

class YcBiterComputable : public YcBiter
{
public:
	~YcBiterComputable() {}

	//----Construction----
	YcBiterComputable(YcBiterComputable & yb) 
		: YcBiter(yb.Length(), yb.GetBoolArray(yb.Length())) 
	{}
	YcBiterComputable(YcBiter & yb) 
		: YcBiter(yb.Length(), yb.GetBoolArray(yb.Length()) ) 
	{}

	YcBiterComputable(void) : YcBiter() {}

	YcBiterComputable(int length) : YcBiter(length){}
	YcBiterComputable(int length,bool * inData) : YcBiter(length,inData) {}

	YcBiterComputable operator^ (const YcBiterComputable & target);
	void operator= (const YcBiterComputable & target);
	//��������زο�https://www.cnblogs.com/linuxAndMcu/p/10395383.html
	//������const��ϸ���https://blog.csdn.net/weixin_43734095/article/details/104465307

private:
	
};