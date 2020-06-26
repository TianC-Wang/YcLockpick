#include "pch.h"
#include "YcBitBase.h"

inline YcBiter::~YcBiter()
{
	delete[] _bData; _bData = NULL;//Ϊ�˲��ڴ�й¶����дһ�°�
#ifdef DEBUG
	outMsg(0, "Biter of ID:%d killed", _classID);
#endif // DEBUG
}

inline YcBiter::YcBiter(int length,int id) :  _length(length), _classID(id)
{
#ifdef DEBUG
		outMsg(0, "Biter %d created (Normal)",_classID);
#endif // DEBUG
		delete[] _bData;
		_bData = new bool[_length];
		memset(_bData, 0, _length * sizeof(bool));
#ifdef DEBUG
		outMsg(0, "length: %d",Debug_GetLen());
		outMsg(0, "_bData's Address: 0x%x", _bData);
#endif // DEBUG
}

inline YcBiter::YcBiter(int length,bool * inData , int id) : _length(length), _classID(id)
{
#ifdef DEBUG
	outMsg(0, "Biter %d created (Way: Clone ,\" bData \" involved)", _classID);
#endif // DEBUG
	_bData = new bool[_length];
	memset(_bData, 0, _length * sizeof(bool));//ʹ��֮ǰ��������һ�°�
	for (int i = 0; i < _length; i++)
	{
		_bData[i] = inData[i];
	}
#ifdef DEBUG
	outMsg(0, "length: %d", _length);
	OutMsgShow();
	outMsg(0, "_bData's Address: 0x%x", _bData);
#endif // DEBUG
}

inline bool YcBiter::Widen_EmptySide(int n,bool mode)
{
	if (n <= 0)	return false;

	bool* ptemp = new bool[_length + n];
	for (int i = 0; i < n; i++)
		ptemp[i] = false;
	if(mode == true)
		for (int i = 0; i < _length; i++)
			ptemp[i+n] = _bData[i];
	else
		for (int i = 0; i < _length; i++)
			ptemp[i] = _bData[i];
	delete [] _bData;
	_bData = ptemp;
	ptemp = NULL;
	_length+=n;
	_current = 0;
#ifdef DEBUG
	outMsg(0, "_bData WidenLed %d. New _bData address at 0x%x", n, _bData);
#endif //DEBUG
	return true;
}

inline bool YcBiter::Flush_bData(int n)
{
	if (n <= 0)
	{
#ifdef DEBUG
		outMsg(2, "input wrong: \"size n<=0\" while running YcBiter::Flush(int n)");
#endif //DEBUG
		return false;
	}
	else
	{
		_current = 0;
		_length = n;//����_lenghth , _current��ֵ
		delete[] _bData;
		_bData = new bool[n];
		for (int i = 0; i <	_length; i++)
			_bData[i] = false;
#ifdef DEBUG
		outMsg(0, "YcBiter with class ID \"%d\"'s_bData flushed. New _bData created, address at 0x%x, length of %d",_classID, _bData, _length);
#endif //DEBUG
		return true;
	}
}

inline string YcBiter::GetRoughDataString()
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
//��������"10001010"���ַ���,��Դ����

inline void YcBiter::CoverWrite(bool data[], int inLength)
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

inline void YcBiter::CoverWrite_S(string str)
{
	CoverWrite(strToBool_CWS(str), str.length());
}
