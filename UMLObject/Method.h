#pragma once

#include <iostream>

class Method
{
private:
	CString isLookM;
	CString Mname;

public:
	Method(void);
	~Method(void);
	CString GetIsLookM();
	void SetIsLookM(CString &str);
	CString GetMname();
	void SetMname(CString &str);
};

