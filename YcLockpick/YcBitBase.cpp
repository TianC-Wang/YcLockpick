#pragma once

#include "pch.h"
#include "YcBitBase.h"

inline YcBiter::~YcBiter()
{
	delete[] _bData; _bData = NULL;//Ϊ�˲��ڴ�й¶����дһ�°�
#ifdef DEBUG
	//if(_classID != _Const_DefaultClassID_YcBiter)
	//	outMsg(0, "Yciter with ID: %d killed", _classID);
	//else
	//	outMsg(0, "Yciter with ID: DEFAULT killed", _classID);
#endif // DEBUG
}

inline YcBiter::YcBiter(int length,int id) :  _length(length), _classID(id)
{
		delete[] _bData;
		_bData = new bool[_length];
		memset(_bData, 0, _length * sizeof(bool));
#ifdef DEBUG
		//if(_classID != _Const_DefaultClassID_YcBiter)
		//	outMsg(0, "YcBiter with ID: %d created (Way : Normal), length %d ,_bData's Address: 0x%x",_classID,Debug_GetLen(),_bData);
		//else
		//	outMsg(0, "YcBiter with ID: DEFAULT created (Way : Normal), length %d, _bData's Address: 0x%x", _classID, Debug_GetLen(), _bData);
#endif // DEBUG
}

inline YcBiter::YcBiter(int length,bool * inData , int id) : _length(length), _classID(id)
{
	//Way of Clone
	delete[] _bData; _bData = NULL;
	_bData = new bool[_length];
	memset(_bData, 0, _length * sizeof(bool));//ʹ��֮ǰ��������һ�°�
	for (int i = 0; i < _length; i++)
	{
		_bData[i] = inData[i];
	}
#ifdef DEBUG
	//if(_classID != _Const_DefaultClassID_YcBiter)
	//	outMsg(0, "YcBiter with ID: %d created (Way: Clone), length: %d, _bData's Address: 0x%x", _classID, _length, _bData);
	//else
	//	outMsg(0, "YcBiter with ID: DEFAULT created (Way: Clone), length: %d, _bData's Address: 0x%x", _classID, _length, _bData);
	//Debug_OutMsgShow_Bit();
#endif // DEBUG
}

inline bool YcBiter::Widen_EmptySide(int n,bool true2left_OR_false2right)
{
	if (n <= 0)	return false;

	bool* ptemp = new bool[_length + n];
	for (int i = 0; i < n; i++)
		ptemp[i] = false;
	if(true2left_OR_false2right == true)
		for (int i = 0; i < _length; i++)
			ptemp[i+n] = _bData[i];
	else
		for (int i = 0; i < _length; i++)
			ptemp[i] = _bData[i];
	delete [] _bData;
	_bData = ptemp;
	ptemp = NULL;
	_length+=n;
#ifdef DEBUG
	//if(_classID !=_Const_DefaultClassID_YcBiter)
	//	outMsg(0, "YcBiter with ID: %d's _bData WidenLed %d. New _bData address at 0x%x", _classID, n, _bData);
	//else
	//	outMsg(0, "YcBiter with ID: DEFAULT's _bData WidenLed %d. New _bData address at 0x%x", _classID, n, _bData);
#endif //DEBUG
	return true;
}

inline bool YcBiter::Flush_bData(int n)
{
	if (n <= 0)
	{
#ifdef DEBUG
		//if(_classID !=_Const_DefaultClassID_YcBiter)
		//	outMsg(2, "input wrong: \"size n<=0\" while running YcBiter::Flush(int n), classID = %d", _classID);
		//else
		//	outMsg(2, "input wrong: \"size n<=0\" while running YcBiter::Flush(int n), classID = DEFAULT",_classID);
#endif //DEBUG
		return false;
	}
	else
	{
		_length = n;//����_lenghth��ֵ
		delete[] _bData;
		_bData = new bool[n];
		for (int i = 0; i <	_length; i++)
			_bData[i] = false;
#ifdef DEBUG
		//if(_classID !=_Const_DefaultClassID_YcBiter)
		//	outMsg(0, "YcBiter with ID : %d's_bData flushed. New _bData created, address at 0x%x, length of %d", _classID, _bData, _length);
		//else
		//	outMsg(0, "YcBiter with ID : DEFAULT's_	bData flushed. New _bData created, address at 0x%x, length of %d",_classID, _bData, _length);
#endif //DEBUG
		return true;
	}
}

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
