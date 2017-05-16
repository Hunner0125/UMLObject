#pragma once

#include "afx.h"

class ConnectPoint :public CObject
{
public:
	DECLARE_SERIAL(ConnectPoint)

public:
	ConnectPoint();
	~ConnectPoint();

public:
	void Draw(CDC *pdc);
	void SetPoint(CPoint &pt);
	CPoint GetPoint();
	bool IsOn(CPoint &pt);

	void SetType(bool type);

	void Serialize(CArchive& ar);

private:
	CPoint m_Point;
	bool m_type;//���ĵ㣬true���Σ�falseԲ��
};

