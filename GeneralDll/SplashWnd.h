//////////////////////////////////////////////////////////////////////////////
//���������࣬�̳�CWnd������
class CSplashWnd : public CWnd
{
public:
	CBitmap bitmap;									//����λͼʵ��
	BITMAP mapInfo;									//����λͼ��Ϣʵ��
	CSplashWnd();
	~CSplashWnd();
	void QuitSplashWnd();
protected:
	afx_msg BOOL OnCreate(LPCREATESTRUCT lpcs);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	afx_msg void OnPaint();
};