#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>
#include "Game.h"

#pragma warning
GSound* Game::gameSound = NULL;

Game::Game(HINSTANCE hInstance, LPCSTR Name, int IsFullscreen, int FrameRate)
{
	d3d = NULL; 
	d3ddevice = NULL;
	backbuffer = NULL;

	directinput = NULL;
	keyboard = NULL;

	_FrameRate = FrameRate;
	_IsFullScreen = IsFullscreen;
	_hInstance = hInstance;
	_Name = Name;

	_ScreenWidth = 512;
	_ScreenHeight = 448;
	_BackBufferFormat = D3DFMT_X8R8G8B8;

	Game::gameSound = new GSound();
	surface = NULL;
}

void Game::_InitWindow()
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = _hInstance;

	wc.lpfnWndProc = (WNDPROC)Game::_WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = _Name;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	DWORD style;
	if (_IsFullScreen)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else
		style = WS_OVERLAPPEDWINDOW;

	_hWnd =
		CreateWindow(
			_Name,
			_Name,
			style,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			_ScreenWidth,
			_ScreenHeight,
			NULL,
			NULL,
			_hInstance,
			NULL);

	if (!_hWnd)
	{
		DWORD ErrCode = GetLastError();
	}

	ShowWindow(_hWnd, SW_SHOWNORMAL);
	UpdateWindow(_hWnd);
}
void Game::_InitDirectX()
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = _IsFullScreen ? FALSE : TRUE;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	d3dpp.BackBufferFormat = _BackBufferFormat;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = _ScreenHeight;
	d3dpp.BackBufferWidth = _ScreenWidth;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		_hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddevice);

	d3ddevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
}
void Game::_InitKeyboard()
{
	HRESULT
		hr = DirectInput8Create
		(
			_hInstance,
			DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&directinput, NULL
			);
	if (hr != DI_OK) return;

	hr = directinput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	if (hr != DI_OK) return;

	keyboard->SetDataFormat(&c_dfDIKeyboard);
	keyboard->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = 1024; // Arbitary buffer size

	hr = keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (hr != DI_OK) return;

	hr = keyboard->Acquire();
	if (hr != DI_OK) return;

	
}
void Game::_InitFont()
{
	D3DXCreateFont(d3ddevice, 14, 0, FW_NORMAL, 1, false,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE,
		"Verdana Bold", &smallFont);
	D3DXCreateFont(d3ddevice, 20, 0, FW_NORMAL, 1, false,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE,
		"Verdana Bold", &largeFont);

	SetRect(&recZone1, 0, 0, 900, 700);
	SetRect(&recZone2, 320, 38, 600, 600);
}




void Game::Init()
{
	_InitWindow();
	_InitDirectX();
	_InitKeyboard();
	_InitFont();
	Game::gameSound->LoadSound(_hWnd);
	LoadResources(d3ddevice);
	
}

void Game::_ProcessKeyBoard()
{
	// Collect all key states first
	keyboard->GetDeviceState(sizeof(keystate), keystate); //Xem phim nao dang nhan

	if (IsKeyDown(DIK_ESCAPE))
	{
		PostMessage(_hWnd, WM_QUIT, 0, 0);
	}

	// Collect all buffered events
	DWORD dwElements = 1024;
	HRESULT hr = keyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _KeyEvents, &dwElements, 0);

	// Scan through all data, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = _KeyEvents[i].dwOfs;
		int KeyState = _KeyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			OnKeyDown(KeyCode);		//Xu ly luc an xuong
		else
			OnKeyUp(KeyCode);		//Xu ly lusc nha ra
	}
}

// Main game message loop
void Game::Run()
{
	//Game::gameSound->playSoundLoop(LVL1_VAMKILL);
	MSG msg;
	int done = 0;
	DWORD tick_per_frame = 1000 / _FrameRate;
	DWORD tick_start;

	// ===== MAIN GAME LOOP =====
	_DeltaTime = 0;
	tick_start = GetTickCount();
	//UpdateFrame(0);
	Update(0);
	while (!done)
	{
		while (1)
		{
			_DeltaTime = GetTickCount() - tick_start;
			if (_DeltaTime >= (tick_per_frame - 1))	// -1 made game smooth
			{
				tick_start = GetTickCount();
				break;
			}
			Sleep(1);
		}

		if (1)//_DeltaTime >= tick_per_frame)
		{
			// -- Render GPU ---
			if (d3ddevice->BeginScene())
			{
				d3ddevice->ColorFill(backbuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));

				//RenderFrame(d3ddevice);
				Render(d3ddevice);
				//Viết chữ lên màn hình
				smallFont->DrawTextA(NULL, statusZone1.c_str(), -1, &recZone1, DT_LEFT,
						D3DCOLOR_XRGB(255, 255, 255));
				largeFont->DrawTextA(NULL, statusZone2.c_str(), -1, &recZone2, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
				
				d3ddevice->EndScene();
			}
			d3ddevice->Present(NULL, NULL, NULL, NULL);
			
			// --- Catch Message ---
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT) done = 1;

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			// --- Keyboard Input ---
			_ProcessKeyBoard();
			ProcessInput(d3ddevice, ((float)_DeltaTime)/1000);

			// --- Update Frame ---
			//UpdateFrame(((float)_DeltaTime) / 1000);
			Update(((float)_DeltaTime) / 1000);
		}
	}
}

//----Ham ao cai dat rieng trong class cua doi tuong
void Game::LoadResources(LPDIRECT3DDEVICE9 d3ddv) { }
// -----------------------------
void Game::Update(float _DeltaTime) {}
void Game::UpdateFrame(float _DeltaTime) {}

void Game::Render(LPDIRECT3DDEVICE9 d3ddv)
{
	d3ddv->ColorFill(backbuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
}
void Game::RenderFrame(LPDIRECT3DDEVICE9 d3ddv)// , int Delta)
{
	d3ddv->ColorFill(backbuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
}

void Game::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float _DeltaTime) { }
void Game::OnKeyUp(int KeyCode) { }
void Game::OnKeyDown(int KeyCode) { }

Game::~Game()
{
	if (d3ddevice != NULL) d3ddevice->Release();
	if (d3d != NULL) d3d->Release();

	if (keyboard)
	{
		keyboard->Unacquire();
		keyboard->Release();
	}
	if (directinput) directinput->Release();
	Game::gameSound->shutdownDirectSound();
}

int Game::IsKeyDown(int KeyCode)
{
	return (keystate[KeyCode] & 0x80) > 0;
}

LRESULT CALLBACK Game::_WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}


