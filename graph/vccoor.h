#if !defined(AFX_VCCOOR_H__822EE341_2EBF_4423_8512_EF5CE0745F29__INCLUDED_)
#define AFX_VCCOOR_H__822EE341_2EBF_4423_8512_EF5CE0745F29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CVcCoor wrapper class

class CVcCoor : public COleDispatchDriver
{
public:
	CVcCoor() {}		// Calls COleDispatchDriver default constructor
	CVcCoor(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVcCoor(const CVcCoor& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	float GetX();
	void SetX(float newValue);
	float GetY();
	void SetY(float newValue);
	void Set(float X, float Y);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCCOOR_H__822EE341_2EBF_4423_8512_EF5CE0745F29__INCLUDED_)
