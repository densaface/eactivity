// Dib.h: interface for the CDibExt class.
//
//	Creator : El Barto (ef00@luc.ac.be)
//	Location : http://www.luc.ac.be/~ef00/ebgfx
//	Date : 09-04-98
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIB_H__4AC8F494_CB24_11D1_91CA_0020AFF82585__INCLUDED_)
#define AFX_DIB_H__4AC8F494_CB24_11D1_91CA_0020AFF82585__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDibExt  
{
public:
	COLORREF *m_Bits;
	BITMAPINFO m_Info;
	HBITMAP m_Bitmap;
	CSize m_Size;

	BOOL Create ( int Width, int Height );
	BOOL Destroy ();

	void Render ( CDC *pDC, int Width, int Height );
	void SetBitmap ( CDC *pDC, CBitmap *pBitmap );
	
	void Fill ( int R, int G, int B );
	void FillGlass ( int R, int G, int B, int A );
	void FillStippledGlass ( int R, int G, int B );

	void Copy ( CDibExt *Dib );
	void Paste ( CDibExt *Dib );

	void Blend ( CDibExt *Dib, int A );
	void Darken ( CDibExt *Dib );
	void Difference ( CDibExt *Dib );
	void Lighten ( CDibExt *Dib );
	void Multiply ( CDibExt *Dib );
	void Screen ( CDibExt *Dib );

	void CopyRect ( CDibExt *Dib, int x, int y );
	void PasteRect ( CDibExt *Dib, int x, int y );

	void FillRect ( int x, int y, int w, int h, int R, int G, int B );
	void FillGlassRect ( int x, int y, int w, int h, int R, int G, int B, int A );
	void FillStippledGlassRect ( int x, int y, int w, int h, int R, int G, int B );
	
	void BlendRect ( CDibExt *Dib, int x, int y, int A );
	void DarkenRect ( CDibExt *Dib, int x, int y );
	void DifferenceRect ( CDibExt *Dib, int x, int y );
	void LightenRect ( CDibExt *Dib, int x, int y );
	void MultiplyRect ( CDibExt *Dib, int x, int y );
	void ScreenRect ( CDibExt *Dib, int x, int y );

	void Line ( int x1, int y1, int x2, int y2, int R, int G, int B );
	void LineGlass ( int x1, int y1, int x2, int y2, int R, int G, int B, int A );

	CDibExt ();
	virtual ~CDibExt ();
};

#endif // !defined(AFX_DIB_H__4AC8F494_CB24_11D1_91CA_0020AFF82585__INCLUDED_)
