/******************************************************
 *  graphics.h
 *
 *	�� VC ��ģ�� Borland BGI ��ͼ�⣬ʵ�ּ򵥵Ļ�ͼ
 *
 *	2009-11-23 by yw80@msn.com
 *	http://hi.baidu.com/yangw80
 ******************************************************/

#pragma once

#ifndef WINVER                          // Specifies that the minimum required platform is Windows Vista.
#define WINVER 0x0400           // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
#define _WIN32_WINNT 0x0400     // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINDOWS          // Specifies that the minimum required platform is Windows 98.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#if defined(_UNICODE) && (_MSC_VER > 1200)
	#pragma comment(lib,"graphics9u.lib")
#elif !defined(_UNICODE) && (_MSC_VER > 1200)
	#pragma comment(lib,"graphics9.lib")
#elif defined(_UNICODE)
	#pragma comment(lib,"graphics6u.lib")
#elif !defined(_UNICODE)
	#pragma comment(lib,"graphics6.lib")
#endif

#if _MSC_VER > 1200
	#ifdef _DEBUG
		#pragma comment(linker, "/NODEFAULTLIB:libcmtd.lib")
	#else
		#pragma comment(linker, "/NODEFAULTLIB:libcmt.lib")
	#endif
#else
	#ifdef _DEBUG
		#pragma comment(linker, "/NODEFAULTLIB:libc.lib")
	#endif
#endif



#include "windows.h"
#include "tchar.h"

#define PI 3.1415926535

// Ϊ�˼��� Borland C++ 3.1 �����������嶨��
#define DETECT 0
#define VGA	0
#define VGAHI 0

// ��ͼ������ʼ������
#define SHOWCONSOLE		1		// ����ͼ��ģʽʱ����������̨����ʾ

// ��ɫ
#define	BLACK			0
#define	BLUE			0xA80000
#define	GREEN			0x00A800
#define	CYAN			0xA8A800
#define	RED				0x0000A8
#define	MAGENTA			0xA800A8
#define	BROWN			0x0054A8
#define	LIGHTGRAY		0xA8A8A8
#define	DARKGRAY		0x545454
#define	LIGHTBLUE		0xFC5454
#define	LIGHTGREEN		0x54FC54
#define	LIGHTCYAN		0xFCFC54
#define	LIGHTRED		0x5454FC
#define	LIGHTMAGENTA	0xFC54FC
#define	YELLOW			0x54FCFC
#define	WHITE			0xFCFCFC

// ���ģʽ
#define	NULL_FILL			1		// �����
#define	SOLID_FILL			2		// ��ָ����ɫ��ȫ���
#define	BDIAGONAL_FILL		3		// /// ��� (��ͨһ��)
#define	CROSS_FILL			4		// +++ ���
#define	DIAGCROSS_FILL		5		// xxx ���
#define	DOT_FILL			6		// ... ���
#define	FDIAGONAL_FILL		7		// \\\ ���
#define	HORIZONTAL_FILL		8		// --- ���
#define	VERTICAL_FILL		9		// ||| ���
#define	BDIAGONAL2_FILL		10		// /// ��� (�ܼ�һ��)
#define	CROSS2_FILL			11		// +++ ���
#define	DIAGCROSS2_FILL		12		// xxx ���
#define	DOT2_FILL			13		// ... ���
#define	FDIAGONAL2_FILL		14		// \\\ ���
#define	HORIZONTAL2_FILL	15		// --- ���
#define	VERTICAL2_FILL		16		// ||| ���
#define	BDIAGONAL3_FILL		17		// /// ��� (����һ��)
#define	CROSS3_FILL			18		// +++ ���
#define	DIAGCROSS3_FILL		19		// xxx ���
#define	DOT3_FILL			20		// ... ���
#define	FDIAGONAL3_FILL		21		// \\\ ���
#define	HORIZONTAL3_FILL	22		// --- ���
#define	VERTICAL3_FILL		23		// ||| ���
#define	INTERLEAVE_FILL		24		// xxx ��� (ʮ����)
#define	PATTERN_FILL		25		// ��ָ��ͼ�����



// ��ͼģʽ��غ���

void initgraph(int Width, int Height, int Flag = NULL);	// ��ʼ��ͼ�λ���
void initgraph(int* gdriver, int* gmode, char* path);	// ���� Borland C++ 3.1 �����أ�Ĭ�� 640x480@24bit
void closegraph();										// �ر�ͼ�λ���



// ��ͼ��������

void cleardevice();					// ����

COLORREF getcolor();				// ��ȡ��ǰ��ͼǰ��ɫ
void setcolor(COLORREF color);		// ���õ�ǰ��ͼǰ��ɫ
COLORREF getbkcolor();				// ��ȡ��ǰ��ͼ����ɫ
void setbkcolor(COLORREF color);	// ���õ�ǰ��ͼ����ɫ
void setbkmode(int iBkMode);		// ���ñ������ģʽ

void getviewport(int *pleft, int *ptop, int *pright, int *pbottom, bool *pclip = NULL);	// ��ȡ��ͼ��Ϣ
void setviewport(int left, int top, int right, int bottom, bool clip = true);			// ������ͼ
void clearviewport();															// �����ͼ

void getlinestyle(int *plinestyle, WORD *pupattern = NULL, int *pthickness = NULL);	// ��ȡ��ǰ����
void setlinestyle(int linestyle, WORD upattern = NULL, int thickness = 1);			// ���õ�ǰ����
void getfillstyle(COLORREF *pcolor, int *ppattern = NULL, char *pupattern = NULL);			// ��ȡ�������
void setfillstyle(COLORREF color, int pattern = SOLID_FILL, const char *pupattern = NULL);	// �����������

void getaspectratio(float *pxasp, float *pyasp);		// ��ȡ��ǰ��������
void setaspectratio(float xasp = 1, float yasp = 1);	// ���õ�ǰ��������

void setwritemode(int mode);				// ���û�ͼλ����ģʽ

void graphdefaults();						// �������л�ͼ����ΪĬ��ֵ



// ��ͼ����

COLORREF getpixel(int x, int y);				// ��ȡ�����ɫ
void putpixel(int x, int y, COLORREF color);	// ����

void moveto(int x, int y);						// �ƶ���ǰ��(��������)
void moverel(int dx, int dy);					// �ƶ���ǰ��(�������)

void line(int x1, int y1, int x2, int y2);		// ����
void linerel(int dx, int dy);					// ����(���������)
void lineto(int x, int y);						// ����(����������)

void rectangle(int left, int top, int right, int bottom);	// ������

void getarccoords(int *px, int *py, int *pxstart, int *pystart, int *pxend, int *pyend);	// ��ȡԲ��������Ϣ
void arc(int x, int y, int stangle, int endangle, int radius);					// ��Բ��
void circle(int x, int y, int radius);											// ��Բ
void pieslice(int x, int y, int stangle, int endangle, int radius);				// �����Բ����
void ellipse(int x, int y, int stangle, int endangle, int xradius, int yradius);// ����Բ����
void fillellipse(int x, int y, int xradius, int yradius);						// �������Բ
void sector(int x, int y, int stangle, int endangle, int xradius, int yradius);	// �������Բ����

void bar(int left, int top, int right, int bottom);								// ���ޱ߿�������
void bar3d(int left, int top, int right, int bottom, int depth, bool topflag);	// ���б߿���ά������

void drawpoly(int numpoints, const int *polypoints);	// �������
void fillpoly(int numpoints, const int *polypoints);	// �����Ķ����
void floodfill(int x, int y, int border);				// �������



// ������غ���

void outtext(LPCTSTR textstring);					// �ڵ�ǰλ���������
void outtextxy(int x, int y, LPCTSTR textstring);	// ��ָ��λ���������
int textwidth(LPCTSTR textstring);					// ��ȡ�ַ���ռ�õ����ؿ�
int textheight(LPCTSTR textstring);					// ��ȡ�ַ���ռ�õ����ظ�

// ���õ�ǰ������ʽ
//		nHeight: �ַ���ƽ���߶ȣ�Ĭ��Ϊ 16��
//		nWidth: �ַ���ƽ����ȣ�Ĭ��Ϊ 0����ʾ����Ӧ��
//		lpszFace: �������ƣ�Ĭ��Ϊ��System����
//		nEscapement: �ַ�������д�Ƕȣ���λ 0.1 �ȣ�Ĭ��Ϊ 0��
//		nOrientation: ÿ���ַ�����д�Ƕȣ���λ 0.1 �ȣ�Ĭ��Ϊ 0��
//		fnWeight: �ַ��ıʻ���ϸ�����õ��� 400��0 ��ʾĬ�ϴ�ϸ��Ĭ��Ϊ 0��
//		fdwItalic: �Ƿ�б�壬true / false��Ĭ��Ϊ false��
//		fdwUnderline: �Ƿ��»��ߣ�true / false��Ĭ��Ϊ false��
//		fdwStrikeOut: �Ƿ�ɾ���ߣ�true / false��Ĭ��Ϊ false��
void setfont(int nHeight = 16, int nWidth = 0, LPCTSTR lpszFace = NULL, int nEscapement = 0, int nOrientation = 0, int fnWeight = 0, bool fdwItalic = 0, bool fdwUnderline= 0, bool fdwStrikeOut = 0);
void setfont(const LOGFONT *font);	// ���õ�ǰ������ʽ
void getfont(LOGFONT *font);		// ��ȡ��ǰ������ʽ



// ͼ������

// ����ͼ�����
class IMAGE
{
private:
	HBITMAP m_hBmp;
	HDC m_hDC;
	int m_width, m_height;
	SIZE LoadImageFromFile(LPCTSTR pFile, HDC dc, int nDstWidth = 0, int nDstHeight = 0);
public:
	IMAGE();
	IMAGE(IMAGE &img);				// �������캯��
	IMAGE& operator = (IMAGE &img);	// ��ֵ��������غ���
	~IMAGE();
	void getimage(int srcX, int srcY, int srcWidth, int srcHeight);
	void getimage(LPCTSTR pImgFile, int zoomWidth = 0, int zoomHeight = 0);
	void getimage(const IMAGE *pSrcImg, int srcX, int srcY, int srcWidth, int srcHeight);
	void putimage(int dstX, int dstY, DWORD dwRop = SRCCOPY) const;
	void putimage(int dstX, int dstY, int dstWidth, int dstHeight, int srcX, int srcY, DWORD dwRop = SRCCOPY) const;
	void putimage(IMAGE *pDstImg, int dstX, int dstY, DWORD dwRop = SRCCOPY) const;
	void putimage(IMAGE *pDstImg, int dstX, int dstY, int dstWidth, int dstHeight, int srcX, int srcY, DWORD dwRop = SRCCOPY) const;
};

void getimage(IMAGE *pDstImg, int srcX, int srcY, int srcWidth, int srcHeight);				// ����Ļ��ȡͼ��
void getimage(IMAGE *pDstImg, LPCTSTR pImgFile, int zoomWidth = 0, int zoomHeight = 0);		// ��ͼƬ�ļ�(bmp/jpg/gif/emf/wmf)��ȡͼ��
void getimage(IMAGE *pDstImg, const IMAGE *pSrcImg, int srcX, int srcY, int srcWidth, int srcHeight);	// ����һ�� IMAGE �����л�ȡͼ��
void putimage(int dstX, int dstY, const IMAGE *pSrcImg, DWORD dwRop = SRCCOPY);							// ����ͼ����Ļ
void putimage(int dstX, int dstY, int dstWidth, int dstHeight, const IMAGE *pSrcImg, int srcX, int srcY, DWORD dwRop = SRCCOPY);	// ����ͼ����Ļ(ָ�����)
void putimage(IMAGE *pDstImg, int dstX, int dstY, const IMAGE *pSrcImg, DWORD dwRop = SRCCOPY);			// ����ͼ����һͼ����
void putimage(IMAGE *pDstImg, int dstX, int dstY, int dstWidth, int dstHeight, const IMAGE *pSrcImg, int srcX, int srcY, DWORD dwRop = SRCCOPY);	// ����ͼ����һͼ����(ָ�����)



// ��������

int	getmaxx();		// ��ȡ��� x ����
int	getmaxy();		// ��ȡ��� y ����
int	getx();			// ��ȡ��ǰ x ����
int	gety();			// ��ȡ��ǰ y ����

void BeginBatchDraw();	// ��ʼ��������
void FlushBatchDraw();	// ִ��δ��ɵĻ�������
void FlushBatchDraw(int left, int top, int right, int bottom);	// ִ��ָ��������δ��ɵĻ�������
void EndBatchDraw();	// �����������ƣ���ִ��δ��ɵĻ�������
void EndBatchDraw(int left, int top, int right, int bottom);	// �����������ƣ���ִ��ָ��������δ��ɵĻ�������

int GetGraphicsVer();			// ��ȡ��ǰ�汾
LPCTSTR GetGraphicsAuthor();



// �����Ϣ
// ֧��������Ϣ��
//		WM_MOUSEMOVE		����ƶ�
//		WM_MOUSEWHEEL		�����ֲ���
//		WM_LBUTTONDOWN		�������
//		WM_LBUTTONUP		�������
//		WM_LBUTTONDBLCLK	���˫��
//		WM_MBUTTONDOWN		�м�����
//		WM_MBUTTONUP		�м�����
//		WM_MBUTTONDBLCLK	�м�˫��
//		WM_RBUTTONDOWN		�Ҽ�����
//		WM_RBUTTONUP		�Ҽ�����
//		WM_RBUTTONDBLCLK	�Ҽ�˫��
struct MOUSEMSG
{
	UINT uMsg;			// ��ǰ�����Ϣ
	bool mkCtrl;		// Ctrl ���Ƿ���
	bool mkShift;		// Shift ���Ƿ���
	bool mkLButton;		// �������Ƿ���
	bool mkMButton;		// ����м��Ƿ���
	bool mkRButton;		// ����Ҽ��Ƿ���
	int x;				// ��ǰ��� x ����
	int y;				// ��ǰ��� y ����
	int wheel;			// �����ֹ���ֵ(120�ı���)
};

bool MouseHit();				// ����Ƿ���������Ϣ
MOUSEMSG GetMouseMsg();			// ��ȡһ�������Ϣ�����û�У��͵ȴ�
void FlushMouseMsgBuffer();		// ��������Ϣ������
