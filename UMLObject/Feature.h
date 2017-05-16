#pragma once

#include <iostream>
#include "afx.h"

class Feature :public CObject
{
public:
	DECLARE_SERIAL(Feature)

private:
	CString isLook;
	CString Fname;

public:
	Feature(void);
	~Feature(void);
	Feature(const Feature& f);

public:
	CString GetIsLook();
	void SetIsLook(CString &str);
	CString GetFname();
	void SetFname(CString &str);

	void Serialize(CArchive& ar);
};

