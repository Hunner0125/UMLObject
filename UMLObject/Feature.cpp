#include "stdafx.h"
#include "Feature.h"

IMPLEMENT_SERIAL(Feature, CObject, 1)

Feature::Feature(void)
{
}

Feature::~Feature(void)
{
}

Feature::Feature(const Feature& f)
{
	isLook = f.isLook;
	Fname = f.Fname;
}

CString Feature::GetIsLook()
{
	return isLook;
}

void Feature::SetIsLook(CString &str)
{
	isLook = str;
}
CString Feature::GetFname()
{
	return Fname;
}

void Feature::SetFname(CString &str)
{
	Fname = str;
}

void Feature::Serialize(CArchive& ar)
{
	//CObject::Serialize( ar );
	if(ar.IsStoring())
	{
		ar<<isLook<<Fname;
	}
	else
	{
		ar>>isLook>>Fname;
	}

	//m_Points.Serialize(ar);
}