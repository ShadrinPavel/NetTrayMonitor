/*
 * ============================================================================
 * ПРОГРАММА: NetTrayMonitor (Монитор интернет-трафика в трее)
 * ВЕРСИЯ: 1.0.0
 * АВТОР: Павел Шадрин (pavel.shadrin@gmail.com)
 * ДАТА СОЗДАНИЯ: 09.08.2026 г.
 *
 * ОПИСАНИЕ:
 * Легковесная портабельная (Portable) утилита для мониторинга реальной скорости
 * интернет-соединения с минимальной нагрузкой на операционную систему.
 * Не требует установки, не использует реестр для записи данных.
 *
 * СОВМЕСТИМОСТЬ: Windows 7, 8, 10, 11 (Все разрядности).
 * ЛИЦЕНЗИЯ: Распространяется бесплатно. Предоставляется на правах "AS IS" (как есть).
 *
 * ВНИМАНИЕ: СТРУКТУРА ИСХОДНОГО КОДА НАМЕРЕННО ОБФУСЦИРОВАНА И СЖАТА ДЛЯ
 * ПРЕДОТВРАЩЕНИЯ НЕСАНКЦИОНИРОВАННОГО АНАЛИЗА И ИЗМЕНЕНИЯ ЛОГИКИ РАБОТЫ.
 * ============================================================================
 */
#define _WIN32_WINNT 0x0601
#define WIN32_LEAN_AND_MEAN
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"iphlpapi.lib")
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"advapi32.lib")
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <iphlpapi.h>
#include <stdio.h>
HWND _h = 0; ULONGLONG _li = 0, _lo = 0; double _si = 0, _so = 0; int _cw = 85;
bool _L() { DWORD d = 0, s = 4; HKEY k; if (!RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", 0, 0x20019, &k)) { RegQueryValueEx(k, L"SystemUsesLightTheme", 0, 0, (LPBYTE)&d, &s); RegCloseKey(k); return d != 0; }return 0; }
void _U() { DWORD d = 0x08080808, b = -1; GetBestInterface(d, &b); PMIB_IF_TABLE2 t; if (!GetIfTable2(&t)) { ULONGLONG ci = 0, co = 0; for (ULONG i = 0; i < t->NumEntries; i++) { MIB_IF_ROW2* r = &t->Table[i]; if (b != -1 && r->InterfaceIndex != b)continue; if (r->OperStatus == IfOperStatusUp && r->Type != IF_TYPE_SOFTWARE_LOOPBACK) { ci += r->InOctets; co += r->OutOctets; } }if (_li != 0) { _si = (ci - _li) * 8.0; _so = (co - _lo) * 8.0; }_li = ci; _lo = co; FreeMibTable(t); } }
void _F(double s, wchar_t* b) { if (s >= 1000000.0)swprintf(b, 64, L"%.1f Mb/s", s / 1000000.0); else if (s >= 1000.0)swprintf(b, 64, L"%.0f Kb/s", s / 1000.0); else swprintf(b, 64, L"%.0f b/s", s); }
void _W(HWND h, int a) { wchar_t bi[64], bo[64]; _F(_si, bi); _F(_so, bo); int f = (a - 10) / 2; if (f <= 0)return; HDC c = GetDC(h); HFONT h1 = CreateFont(f, 0, 0, 0, 700, 0, 0, 0, 1, 0, 0, 4, 0, L"Segoe UI Variable"); HFONT h2 = CreateFont(f, 0, 0, 0, 400, 0, 0, 0, 1, 0, 0, 4, 0, L"Segoe UI"); SIZE a1, a2, s1, s2; HGDIOBJ o = SelectObject(c, h1); GetTextExtentPoint32(c, L"\x2193 ", 2, &a1); GetTextExtentPoint32(c, L"\x2191 ", 2, &a2); SelectObject(c, h2); GetTextExtentPoint32(c, bi, lstrlen(bi), &s1); GetTextExtentPoint32(c, bo, lstrlen(bo), &s2); SelectObject(c, o); DeleteObject(h1); DeleteObject(h2); ReleaseDC(h, c); _cw = max(8 + a1.cx + s1.cx, 8 + a2.cx + s2.cx); }
void _P() { HWND t = FindWindow(L"Shell_TrayWnd", 0); if (!t)return; HWND n = FindWindowEx(t, 0, L"TrayNotifyWnd", 0); if (!n)return; RECT r; GetWindowRect(n, &r); POINT p = { r.left,r.top }; ScreenToClient(t, &p); HDC c = GetDC(0); int d = GetDeviceCaps(c, 90); ReleaseDC(0, c); int s = MulDiv(40, d, 96); int a = min((int)(r.bottom - r.top), s); _W(_h, a); if (GetParent(_h) != t) { SetParent(_h, t); SetWindowLong(_h, -16, (GetWindowLong(_h, -16) & ~0x80000000) | 0x40000000); }SetWindowPos(_h, HWND_TOP, p.x - _cw - 6, p.y, _cw, a, 0x0010 | 0x0040); }
LRESULT CALLBACK _WND(HWND h, UINT m, WPARAM w, LPARAM l) { switch (m) { case 1:SetTimer(h, 1, 1000, 0); _U(); break; case 275:if (!FindWindow(L"Shell_TrayWnd", 0))PostQuitMessage(0); _U(); _P(); SetLayeredWindowAttributes(h, _L() ? RGB(255, 255, 255) : 0, 0, 1); InvalidateRect(h, 0, 0); break; case 20:return 1; case 15: { PAINTSTRUCT p; HDC c = BeginPaint(h, &p); RECT r; GetClientRect(h, &r); HDC m = CreateCompatibleDC(c); HBITMAP b = CreateCompatibleBitmap(c, r.right, r.bottom); HGDIOBJ o = SelectObject(m, b); bool l_ = _L(); COLORREF k = l_ ? RGB(255, 255, 255) : 0; HBRUSH r_ = CreateSolidBrush(k); FillRect(m, &r, r_); DeleteObject(r_); COLORREF c1 = l_ ? 0 : RGB(255, 255, 255); COLORREF c2 = l_ ? RGB(100, 100, 100) : RGB(160, 160, 160); int f = (r.bottom - 10) / 2; HFONT h1 = CreateFont(f, 0, 0, 0, 700, 0, 0, 0, 1, 0, 0, 4, 0, L"Segoe UI Variable"); HFONT h2 = CreateFont(f, 0, 0, 0, 400, 0, 0, 0, 1, 0, 0, 4, 0, L"Segoe UI"); SetBkMode(m, 1); wchar_t bi[64], bo[64]; _F(_si, bi); _F(_so, bo); int y1 = 4, y2 = 6 + f; SIZE a; SetTextColor(m, c1); SelectObject(m, h1); TextOut(m, 4, y1, L"\x2193 ", 2); GetTextExtentPoint32(m, L"\x2193 ", 2, &a); SelectObject(m, h2); TextOut(m, 4 + a.cx, y1, bi, lstrlen(bi)); SetTextColor(m, c2); SelectObject(m, h1); TextOut(m, 4, y2, L"\x2191 ", 2); GetTextExtentPoint32(m, L"\x2191 ", 2, &a); SelectObject(m, h2); TextOut(m, 4 + a.cx, y2, bo, lstrlen(bo)); BitBlt(c, 0, 0, r.right, r.bottom, m, 0, 0, 13369376); SelectObject(m, o); DeleteObject(b); DeleteDC(m); DeleteObject(h1); DeleteObject(h2); EndPaint(h, &p); break; }case 2:PostQuitMessage(0); break; default:return DefWindowProc(h, m, w, l); }return 0; }
																			   int APIENTRY wWinMain(HINSTANCE I, HINSTANCE, LPWSTR, int) { HANDLE m = CreateMutex(0, 1, L"NTM_M"); if (!m || GetLastError() == 183)return 0; WNDCLASS w = { 0 }; w.lpfnWndProc = _WND; w.hInstance = I; w.lpszClassName = L"NTM_C"; w.hCursor = LoadCursor(0, IDC_ARROW); RegisterClass(&w); _h = CreateWindowEx(0x00000080 | 0x00080000 | 0x00000020, L"NTM_C", L"", 0x80000000 | 0x10000000, 0, 0, _cw, 40, 0, 0, I, 0); if (!_h)return 0; SetLayeredWindowAttributes(_h, _L() ? RGB(255, 255, 255) : 0, 0, 1); _P(); MSG g; while (GetMessage(&g, 0, 0, 0)) { TranslateMessage(&g); DispatchMessage(&g); }if (m) { ReleaseMutex(m); CloseHandle(m); }return g.wParam; }