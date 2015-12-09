#include "stdafx.h"
#include "bmpext.h"

CDDBDrawEx::CDDBDrawEx(CDC* pDC, CBitmap* pbmSrc, CBitmap* pbmBack) :
  m_pDC(pDC), m_pbmSrc(pbmSrc), m_pbmBack(pbmBack)
{} 

CDDBDrawEx::~CDDBDrawEx()
{}

void CDDBDrawEx::Fill(CRect& rDest)
{
	CBrush	brPat;
	CBrush* pbrOld;
	CPoint  pntOld;
	
	brPat.CreatePatternBrush( m_pbmSrc );
	pntOld = m_pDC->SetBrushOrg( rDest.TopLeft() );
	pbrOld = m_pDC->SelectObject( &brPat );
	m_pDC->PatBlt( rDest.left, rDest.top,
		rDest.Width(), rDest.Height(),
		PATCOPY );
	m_pDC->SetBrushOrg( pntOld );
	m_pDC->SelectObject( pbrOld );
}



void CDDBDrawEx::Draw(CRect& rDest, CPoint& pntSrc )
{
	CDC dcImage;
	CBitmap* pbmOldImg;

	if( dcImage.CreateCompatibleDC( m_pDC ) )
	{
		pbmOldImg = dcImage.SelectObject( m_pbmSrc );
		
		m_pDC->BitBlt( rDest.left, rDest.top,
			rDest.Width(), rDest.Height(),
			&dcImage,
			pntSrc.x, pntSrc.y,
			SRCCOPY );

		dcImage.SelectObject( pbmOldImg );
	}
}

void CDDBDrawEx::DrawTransparent( CRect& rDest, CPoint& pntSrc, COLORREF crMask )
{
	CDC dcImage;
	CDC dcBack;
	CDC dcAnd;
	CDC dcXor;	
	CDC dcTemp;

	CBitmap* pbmOldImg;
	CBitmap* pbmOldBack = NULL;
	CBitmap	bmAnd;
	CBitmap* pbmOldAnd;
	CBitmap bmXor;
	CBitmap* pbmOldXor;
	CBitmap bmTemp;
	CBitmap* pbmOldTemp;
	
	int iWidth = rDest.Width();
	int iHeight = rDest.Height();
	
	if( dcImage.CreateCompatibleDC( m_pDC ) &&
		dcBack.CreateCompatibleDC( m_pDC ) &&
		dcAnd.CreateCompatibleDC( m_pDC ) &&
		dcXor.CreateCompatibleDC( m_pDC ) &&
		dcTemp.CreateCompatibleDC( m_pDC ) )
	{
		
		pbmOldImg = dcImage.SelectObject( m_pbmSrc );
		bmAnd.CreateBitmap( iWidth, iHeight, 1, 1, NULL );
		pbmOldAnd = dcAnd.SelectObject( &bmAnd ); 
		dcImage.SetBkColor( crMask );
		
		// create AND mask 
		dcAnd.BitBlt( 0, 0,
			iWidth, iHeight,
			&dcImage,
			pntSrc.x, pntSrc.y,
			SRCCOPY ); 
		
		bmXor.CreateCompatibleBitmap( &dcImage, iWidth, iHeight );
		pbmOldXor = dcXor.SelectObject( &bmXor ); 
		
		// create XOR mask
		dcXor.BitBlt( 0, 0,
			iWidth, iHeight,
			&dcImage,
			pntSrc.x, pntSrc.y,
			SRCCOPY ); 
		dcXor.BitBlt( 0, 0,
			iWidth, iHeight,
			&dcAnd,
			0, 0,
			0x220326 ); 

		if( m_pbmBack )
		{
			pbmOldBack = dcBack.SelectObject( m_pbmBack );
			bmTemp.CreateCompatibleBitmap( &dcBack, iWidth, iHeight );
			pbmOldTemp = dcTemp.SelectObject( &bmTemp );
			//copy snapshot to tmp
			dcTemp.BitBlt( 0, 0,
				iWidth, iHeight,
				&dcBack,
				rDest.left, rDest.top,
				SRCCOPY );
		}
		else
		{
			bmTemp.CreateCompatibleBitmap( m_pDC, iWidth, iHeight );
			pbmOldTemp = dcTemp.SelectObject( &bmTemp );
			//copy snapshot to tmp
			dcTemp.BitBlt( 0, 0,
				iWidth, iHeight,
				m_pDC,
				rDest.left, rDest.top,
				SRCCOPY );
		}
		
		// blend the AND and XOR masks into the temporary memory DC
		dcTemp.BitBlt( 0, 0,
			iWidth, iHeight,
			&dcAnd,
			0, 0,
			SRCAND); 
		dcTemp.BitBlt( 0, 0,
			iWidth, iHeight,
			&dcXor,
			0, 0,
			SRCINVERT); 
		
		// copy the resulting image to the screen
		m_pDC->BitBlt( rDest.left, rDest.top,
			iWidth, iHeight,
			&dcTemp,
			0, 0,
			SRCCOPY); 
		
		// restore the GUI default bitmaps
		dcTemp.SelectObject( pbmOldTemp ); 
		dcXor.SelectObject( pbmOldXor );
		dcAnd.SelectObject( pbmOldAnd ); 
		dcImage.SelectObject( pbmOldImg );
		dcBack.SelectObject( pbmOldBack );
	}
}

//DDB2Rgn helper function
LPRGNDATA CDDBDrawEx::RectList2RGNDATA( RECTLIST& rl, RECT& rBound, int& iByteCount )
{
	//allocate memory for structure
	int iRectCnt = rl.GetCount();
	int iRectSize = sizeof(RECT);
	iByteCount = sizeof(RGNDATAHEADER) + iRectSize * iRectCnt;
	LPRGNDATA lpResult = (LPRGNDATA) new BYTE[ iByteCount ];
	
	if( lpResult )
	{					
		lpResult->rdh.dwSize = sizeof(RGNDATAHEADER);
		lpResult->rdh.iType = RDH_RECTANGLES;
		lpResult->rdh.nCount = iRectCnt;
		lpResult->rdh.nRgnSize = iByteCount;
		memcpy( &lpResult->rdh.rcBound, &rBound, iRectSize );
		
		//copy rects to the RGNDATA and remove rect list
		LPBYTE lpBuffer = (LPBYTE)lpResult->Buffer;
		while( rl.GetHeadPosition() )
		{
			LPRECT lpRect = rl.RemoveHead();
			memcpy( lpBuffer, lpRect, iRectSize );
			delete lpRect;
			
			lpBuffer += iRectSize;
		}
	}

	return lpResult;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	BitmapToRegion :	Create a region from the "non-transparent" pixels of a bitmap
//	Author :			Jean-Edouard Lachand-Robert (http://www.geocities.com/Paris/LeftBank/1160/resume.htm), June 1998.
//	Modified:			Vsevolod Gromov (ambap.narod.ru)
//
//	cTransparentColor :	Color base for the "transparent" pixels
//	cTolerance :		Color tolerance for the "transparent" pixels.
//
//	A pixel is assumed to be transparent if the value of each of its 3 components (blue, green and red) is 
//	greater or equal to the corresponding value in cTransparentColor and is lower or equal to the 
//	corresponding value in cTransparentColor + cTolerance.
//
HRGN CDDBDrawEx::MakeRgn( COLORREF cTransparentColor, COLORREF cTolerance )
{
	CRgn rgnResult;
	CRgn rgnTemp;
	int iRgnDataSize;
	LPRGNDATA lprgnData;

	if( (HBITMAP)(*m_pbmSrc) )
	{
		// Create a memory DC inside which we will scan the bitmap content
		CDC dcMem;
		if( dcMem.CreateCompatibleDC( NULL ) )
		{
			BITMAP infoSrc;
			// Get bitmap size
			m_pbmSrc->GetBitmap( &infoSrc );

			// Create a 32 bits depth bitmap and select it into the memory DC 
			BITMAPINFOHEADER RGB32BITSBITMAPINFO =
			{	
					sizeof(BITMAPINFOHEADER),	// biSize 
					infoSrc.bmWidth,			// biWidth; 
					infoSrc.bmHeight,			// biHeight; 
					1,							// biPlanes; 
					32,							// biBitCount 
					BI_RGB,						// biCompression; 
					0,							// biSizeImage; 
					0,							// biXPelsPerMeter; 
					0,							// biYPelsPerMeter; 
					0,							// biClrUsed; 
					0							// biClrImportant; 
			};
			
			LPBYTE pbits32; 
			HBITMAP h32DIB =			
				CreateDIBSection( dcMem.GetSafeHdc(), (LPBITMAPINFO)&RGB32BITSBITMAPINFO, DIB_RGB_COLORS, (LPVOID*)&pbits32, NULL, 0);
			
			if( h32DIB )
			{
				CBitmap* pbm32DDB = CBitmap::FromHandle( h32DIB );
				CBitmap* pbmOld = dcMem.SelectObject( pbm32DDB );
				
				// Create a DC just to copy the bitmap into the memory DC
				CDC dcMemCpy;
				if(	dcMemCpy.CreateCompatibleDC( &dcMem ) )
				{
					BITMAP infoDDB32;
					
					// Get how many bytes per row we have for the bitmap bits (rounded up to 32 bits)
					pbm32DDB->GetBitmap( &infoDDB32 );
					while( infoDDB32.bmWidthBytes % 4 )
						infoDDB32.bmWidthBytes++;
					
					// Copy the bitmap into the memory DC
					CBitmap* pbmOldCpy = dcMemCpy.SelectObject( m_pbmSrc );
					
					dcMem.BitBlt( 0, 0,
						infoSrc.bmWidth, infoSrc.bmHeight,
						&dcMemCpy,
						0, 0,
						SRCCOPY );
					
					RECT	rBound;
					RECTLIST rlRgnParts;

					SetRect( &rBound, MAXLONG, MAXLONG, 0, 0);
		
					// Keep on hand highest and lowest values for the "transparent" pixels
					BYTE lr = GetRValue(cTransparentColor);
					BYTE lg = GetGValue(cTransparentColor);
					BYTE lb = GetBValue(cTransparentColor);
					BYTE hr = min(0xff, lr + GetRValue(cTolerance));
					BYTE hg = min(0xff, lg + GetGValue(cTolerance));
					BYTE hb = min(0xff, lb + GetBValue(cTolerance));
					
					// Scan each bitmap row from bottom to top (the bitmap is inverted vertically)
					pbits32 = (LPBYTE)infoDDB32.bmBits +
						(infoDDB32.bmHeight - 1) * infoDDB32.bmWidthBytes;
					
					for(int y = 0; y < infoDDB32.bmHeight; y++)
					{
						// Scan each bitmap pixel from left to right
						for (int x = 0; x < infoDDB32.bmWidth; x++)
						{
							// Search for a continuous range of "non transparent pixels"
							int x0 = x;
							LPLONG p = (LPLONG) pbits32 + x;
							while(x < infoDDB32.bmWidth)
							{
								BYTE b = LPRGBQUAD( p )->rgbRed;
								if (b >= lr && b <= hr)
								{
									b = LPRGBQUAD( p )->rgbGreen;
									if (b >= lg && b <= hg)
									{
										b = LPRGBQUAD( p )->rgbBlue;
										if (b >= lb && b <= hb)
											// This pixel is "transparent"
											break;
									}
								}
								p++;
								x++;
							}
							
							if (x > x0)
							{
								// Add the pixels (x0, y) to (x, y+1) as a new rectangle in the region
								LPRECT lpr = new RECT;
								if( lpr )
								{
									SetRect( lpr, x0, y, x, y+1);
									//accumulate rect in list
									rlRgnParts.AddTail( lpr );
								}
								
								if (x0 < rBound.left)
									rBound.left = x0;
								if (y < rBound.top)
									rBound.top = y;
								if (x > rBound.right)
									rBound.right = x;
								if (y+1 > rBound.bottom)
									rBound.bottom = y+1;
								
								// On Windows98, ExtCreateRegion() may fail if the number of rectangles is too
								// large (ie: > 4000). Therefore, we have to create the region by multiple steps.
								if( rlRgnParts.GetCount() == 2000 )
								{
									lprgnData = 
										RectList2RGNDATA( rlRgnParts, rBound, iRgnDataSize );
									
									if( lprgnData )
									{
										rgnTemp.DeleteObject();
										rgnTemp.CreateFromData( NULL, iRgnDataSize, lprgnData );

										if( (HRGN)rgnResult )
											rgnResult.CombineRgn( &rgnResult, &rgnTemp, RGN_OR);
										else
											rgnResult.Attach( rgnTemp.Detach() );
										
										delete[] lprgnData;
									}
									
									SetRect( &rBound, MAXLONG, MAXLONG, 0, 0);
								}
							}
						}
						
						// Go to next row (remember, the bitmap is inverted vertically)
						pbits32 -= infoDDB32.bmWidthBytes;
					}
					
					// Create or extend the region with the remaining rectangles
					lprgnData = 
						RectList2RGNDATA( rlRgnParts, rBound, iRgnDataSize );
					
					if( lprgnData )
					{
						rgnTemp.DeleteObject();
						rgnTemp.CreateFromData( NULL, iRgnDataSize, lprgnData );
						if( (HRGN)rgnResult )
							rgnResult.CombineRgn( &rgnResult, &rgnTemp, RGN_OR );
						else
							rgnResult.Attach( rgnTemp.Detach() );
						
						delete[] lprgnData;
					}
					
					// Clean up
					dcMemCpy.SelectObject( pbmOldCpy );
				}

				dcMem.SelectObject( pbmOld );				
				DeleteObject( h32DIB );
			}
		}	
	}
	
	return (HRGN)rgnResult.Detach();
}