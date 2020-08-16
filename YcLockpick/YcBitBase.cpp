#pragma once

#include "pch.h"
#include "YcBitBase.h"

inline YcBiter::YcBiter(int length)
{
	_length = length;
	_bData = new bool[_length];
	memset(_bData, 0, _length * sizeof(bool));
}

inline YcBiter::YcBiter(int length, bool * inData) 
{
	_length = length;
	//Way of Clone
	_bData = new bool[_length];
	memset(_bData, 0, _length * sizeof(bool));
	for (int i = 0; i < _length; i++)
	{
		_bData[i] = inData[i];
	}
}

inline bool YcBiter::Widen_EmptySide(int n, bool true2left_OR_false2right)
{
	if (n <= 0)	return false;

	bool* ptemp = new bool[_length + n];
	for (int i = 0; i < n; i++)
		ptemp[i] = false;
	if (true2left_OR_false2right == true)
		for (int i = 0; i < _length; i++)
			ptemp[i + n] = _bData[i];
	else
		for (int i = 0; i < _length; i++)
			ptemp[i] = _bData[i];
	n += _length;
	deleteBuffer_bData();
	_bData = ptemp;
	ptemp = NULL;
	_length = n;
	//_length += n;
	//bug, �ڵ���deleteBuffer_bData()֮��_length������0,���´˴�_length�������n

	return true;
}

inline bool YcBiter::Flush_bData(int n)
{
	if (n <= 0)
	{
		return false;
	}
	else
	{
		_length = n;//����_lenghth��ֵ
		delete[] _bData;
		_bData = new bool[n];
		for (int i = 0; i < _length; i++)
			_bData[i] = false;
		return true;
	}
}

inline void YcBiter::CoverWrite(bool * data, int inLength)
{
	int difference = 0;
	if (inLength <= _length)
		difference = _length - inLength;//difference����ֵΪ���ֵ
	else
		Flush_bData(inLength);
	for (int i = 0; i < _length; i++)//_length �Ѿ���Flush()������ֵ
		_bData[i + difference] = data[i];//data�϶�ʱ,������_bData�ĸ�λ
	delete[] data;
}

inline void YcBiter::CoverWrite_RoughString(string str)
{
	deleteBuffer_bData();
	string str2 = "";
	for (int i = 0; i < (int)str.length(); i++)
	{
		if (str[i] == ' ' || str[i] == '	')//eat spaces and tabs
			continue;
		str2 += str[i];
	}
	CoverWrite(strToBool_RS(str2), str2.length());
}

inline string YcBiter::Debug_Get_bData_Hex(bool format)
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
			if (i == tlen) {}
			if (format && i % 8 == 0)
				str += ' ';
			rev = 0;
		}

		if (i == tlen)
		{
			break;
			//i��Ҫ����tlen(Ҳ���ǳ���Ϊtlen+1)���ڽ������һλ
			//��Ϊ�˷�ֹ������������Ҫ��break
		}

		if (_bData[i - l_distance])
		{
			rev += (int)pow(2, 3 - (i % 4));
		}
	}
	return str;
}

inline bool YcBiter::dump8BitArray(int nBytes, unsigned char address[])
{
	if (nBytes * 8 < _length)	return  false;
	int tlen;
	int current = 0;
	for (tlen = _length; tlen % 8 != 0; tlen++) {} //���䵽8λ
	int l_distance = tlen - _length;

	for (int i = 0; i <= tlen; i++)//�� if (i == tlen) ������
	{
		if (i < l_distance)		continue;
		if (i % 8 == 0 && i != 0)	current++;
		if (i == tlen)	break;
		//i��Ҫ����tlen(Ҳ���ǳ���Ϊtlen+1)���ڽ������һλ
		//��Ϊ�˷�ֹ������������Ҫ��break
		if (_bData[i - l_distance])
			address[current] += (int)pow(2, 7 - (i % 8));
	}
	return true;
}

inline bool * YcBiter::GetBoolArray(int nbitslength)//��ɾ��new����������
{
	if (nbitslength < _length)	return nullptr;
	else
	{
		bool * address = new bool[nbitslength];
		//issue 2020-07-12
		nbitslength--;
		while (nbitslength >= 0)
		{
			address[nbitslength] = _bData[nbitslength];
			nbitslength--;
		}
		return address;
	}
}

inline string YcBiter::Debug_GetRoughDataString()
{
	string dstr;
	for (int i = 0; i < _length; i++)
	{
		if (_bData[i])
			dstr.push_back('1');
		else
			dstr.push_back('0');
	}
	return dstr;
}

inline YcBiterComputable YcBiterComputable::operator^(const YcBiterComputable & target)
{
	bool * tboolArr = NULL;

	int difference = _length - target._length;

	if (difference<0)
	{
		bool * tboolArr = new bool[_length - difference];

		for (int i = 0; i < _length - difference; i++)
		{
			if (i >= -difference)
				tboolArr[i] = _bData[i+difference] ^ target._bData[i];
			else
				tboolArr[i] = false;
		}
		YcBiterComputable * ybaRe = new YcBiterComputable(_length - difference, tboolArr);

		tboolArr = NULL; 
		return *ybaRe;
	}
	else
	{
		tboolArr = new bool[_length];

		for (int i = 0; i < _length; i++)
		{
			if (i >= difference)
				tboolArr[i] = _bData[i] ^ target._bData[i-difference];
			else
				tboolArr[i] = false;
		}
		YcBiterComputable * ybaRe = new YcBiterComputable(_length, tboolArr);

		tboolArr = NULL; 
		return *ybaRe;
	}
}

inline void YcBiterComputable::operator=(const YcBiterComputable & target)
{
	this->_length = target._length;
	for (int i = 0; i < _length; i++)
	{
		this->_bData[i] = target._bData[i];
	}
}

inline bool * YcBiter :: deleteBuffer_bData(void)
{
	if (_bData != nullptr)
	{
		delete[] _bData;
		_bData = NULL;
	}//���ִ��delete(��delete[])���ᵼ���������
	else
	{
		_bData = NULL;
	}
	_length = 0;
	return _bData;
}
//�����µ�_bData��ָ��ĵ�ַ(����Ӧ����NULL)

inline bool * YcBiter :: strToBool_RS(string str2)
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
