#pragma once


// CPicButton

class CPicButton : public CButton
{
	DECLARE_DYNAMIC(CPicButton)

public:
	CPicButton();
	virtual ~CPicButton();
	
	void SetBit(CString strBitPath);
protected:
	DECLARE_MESSAGE_MAP()      

	HBITMAP m_hBitmap;
	CBitmap m_bitmap;
	BITMAP m_sbitmap;

	BOOL m_bIsMouse;
	BOOL m_bIsPressed;
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


