#include "stdafx.h"
#include "Method.h"


Method::Method(void)
{
}


Method::~Method(void)
{
}

CString Method::GetIsLookM()
{
	return isLookM;
}

void Method::SetIsLookM(CString &str)
{
	isLookM = str;
}
CString Method::GetMname()
{
	return Mname;
}

void Method::SetMname(CString &str)
{
	Mname = str;
}