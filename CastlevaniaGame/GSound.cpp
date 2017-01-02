#include "GSound.h"

GSound::GSound()
{
	g_pDS = NULL;
}

GSound::~GSound()
{
}

void GSound::LoadSound(HWND _hWnd)
{
	if (!InitDirectSound(_hWnd))
	{
		MessageBox(NULL, "Unable to init DirectSound", "ERROR", MB_OK);
	}
	DSBuffer[INTRODUCE1] = LoadWaveToSoundBuffer("Resources\\Sounds\\background\\Introduce1.wav");
	DSBuffer[INTRODUCE2] = LoadWaveToSoundBuffer("Resources\\Sounds\\background\\Introduce2.wav");
	DSBuffer[LVL1_VAMKILL] 
		= LoadWaveToSoundBuffer("Resources\\Sounds\\background\\Level1_VampireKiller.wav");
	DSBuffer[LVL2_STALKER] 
		= LoadWaveToSoundBuffer("Resources\\Sounds\\background\\Level2_Stalker.wav");
	DSBuffer[BOOMERANG] = LoadWaveToSoundBuffer("Resources\\Sounds\\sfx\\BOOMERANG.wav");
	DSBuffer[BRICKBREAK] = LoadWaveToSoundBuffer("Resources\\Sounds\\sfx\\BRICKBREAK.wav");
	DSBuffer[DOWNWATER] = LoadWaveToSoundBuffer("Resources\\Sounds\\sfx\\DOWNWATER.wav");
	DSBuffer[EATCROSS] = LoadWaveToSoundBuffer("Resources\\Sounds\\sfx\\EATCROSS.wav");
	DSBuffer[EATCRYSTAL] = LoadWaveToSoundBuffer("Resources\\Sounds\\sfx\\EATCRYSTAL.wav");
	DSBuffer[EATHEART] = LoadWaveToSoundBuffer("Resources\\Sounds\\sfx\\EATHEART.wav");
	DSBuffer[EATMONEY] = LoadWaveToSoundBuffer("Resources\\Sounds\\sfx\\EATMONEY.wav");
	DSBuffer[EATPOTION] = LoadWaveToSoundBuffer("Resources\\Sounds\\sfx\\EATPOTION.wav");
	DSBuffer[EATWEAPON_CHICKEN] 
		= LoadWaveToSoundBuffer("Resources\\Sounds\\sfx\\EATWEAPON_CHICKEN_MULTIPLY.wav");
	DSBuffer[HITSOFT] = LoadWaveToSoundBuffer("Resources\\Sounds\\sfx\\HITSOFT.wav");
	DSBuffer[HITSTEEL] = LoadWaveToSoundBuffer("Resources\\Sounds\\sfx\\HITSTEEL.wav");
	DSBuffer[HOLYWATERBREAK] = LoadWaveToSoundBuffer("Resources\\Sounds\\sfx\\HOLYWATERBREAK.wav");
	DSBuffer[INJURED] = LoadWaveToSoundBuffer("Resources\\Sounds\\sfx\\INJURED.wav");
	DSBuffer[SOUNDKNIFE] = LoadWaveToSoundBuffer("Resources\\Sounds\\sfx\\KNIFE.wav");
	DSBuffer[MAINGATE] = LoadWaveToSoundBuffer("Resources\\Sounds\\sfx\\MAINGATE.wav");
	DSBuffer[PAUSE] = LoadWaveToSoundBuffer("Resources\\Sounds\\sfx\\PAUSE.wav");
	DSBuffer[POTIONIMMORTAL] = LoadWaveToSoundBuffer("Resources\\Sounds\\sfx\\POTIONIMMORTAL.wav");
	DSBuffer[SHOWSECRETITEM] = LoadWaveToSoundBuffer("Resources\\Sounds\\sfx\\SHOWSECRETITEM.wav");
	DSBuffer[TETRENCAOXUONG] = LoadWaveToSoundBuffer("Resources\\Sounds\\sfx\\TETRENCAOXUONG.wav");
	DSBuffer[TICKTICKTICK] = LoadWaveToSoundBuffer("Resources\\Sounds\\sfx\\TICKTICKTICK.wav");
	DSBuffer[TIMENEAREND] = LoadWaveToSoundBuffer("Resources\\Sounds\\sfx\\TIMENEAREND.wav");
	DSBuffer[UPWATER] = LoadWaveToSoundBuffer("Resources\\Sounds\\sfx\\UPWATER.wav");
	DSBuffer[WHIPATTACK_AXE] = LoadWaveToSoundBuffer("Resources\\Sounds\\sfx\\WHIPATTACK_AXE.wav");

	if (!DSBuffer)
	{
		MessageBox(NULL, "Unable to load sound", "ERROR", MB_OK);
	}
}

bool GSound::InitDirectSound(HWND hwnd)
{
	HRESULT hr;

	hr = DirectSoundCreate8(NULL, &g_pDS, NULL);
	if FAILED(hr)
		return false;

	// Set DirectSound cooperative level 
	hr = g_pDS->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
	if FAILED(hr)
		return false;

	return true;
}

void GSound::shutdownDirectSound()
{
	if (DSBuffer)
	{
		
		for (int i = 0; i < 30; i++)
		{
			if (DSBuffer[i] != NULL)
			{
				DSBuffer[i]->Release();
				DSBuffer[i] = NULL;
			}
		}
		//delete DSBuffer;
	}
	if (g_pDS)
	{
		g_pDS->Release();
		g_pDS = NULL;
	}
}

LPDIRECTSOUNDBUFFER GSound::LoadWaveToSoundBuffer(char* filename)
{
	LPDIRECTSOUNDBUFFER apDSBuffer = NULL;
	CWaveFile *wavFile;
	HRESULT hr;

	wavFile = new CWaveFile();
	wavFile->Open(filename, NULL, WAVEFILE_READ);


	DSBUFFERDESC dsbd;
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = 0;
	dsbd.dwBufferBytes = wavFile->GetSize();
	dsbd.guid3DAlgorithm = GUID_NULL;
	dsbd.lpwfxFormat = wavFile->m_pwfx;

	hr = g_pDS->CreateSoundBuffer(&dsbd, &apDSBuffer, NULL);
	if FAILED(hr)
	{
		MessageBox(NULL, "unable to create sound buffer", "ERROR", MB_OK);
		return NULL;
	}

	VOID*   pDSLockedBuffer = NULL; // Pointer to locked buffer memory
	DWORD   dwDSLockedBufferSize = 0;    // Size of the locked DirectSound buffer
	DWORD   dwWavDataRead = 0;    // Amount of data read from the wav file 

	hr = apDSBuffer->Lock(0, wavFile->GetSize(),
		&pDSLockedBuffer, &dwDSLockedBufferSize,
		NULL, NULL, 0L);
	if FAILED(hr)
		return NULL;

	// Reset the wave file to the beginning 
	wavFile->ResetFile();

	// Read the wave file
	hr = wavFile->Read((BYTE*)pDSLockedBuffer,
		dwDSLockedBufferSize,
		&dwWavDataRead);
	// Check to make sure that this was successful
	if FAILED(hr)
		return NULL;

	// Check to make sure the wav file is not empty
	if (dwWavDataRead == 0)
	{
		// Wav is blank, so just fill with silence
		FillMemory((BYTE*)pDSLockedBuffer,
			dwDSLockedBufferSize,
			(BYTE)(wavFile->m_pwfx->wBitsPerSample == 8 ? 128 : 0));
	}
	else if (dwWavDataRead < dwDSLockedBufferSize)
	{
		// Don't repeat the wav file, just fill in silence 
		FillMemory((BYTE*)pDSLockedBuffer + dwWavDataRead,
			dwDSLockedBufferSize - dwWavDataRead,
			(BYTE)(wavFile->m_pwfx->wBitsPerSample == 8 ? 128 : 0));
	}

	// Unlock the buffer, we don't need it anymore.
	apDSBuffer->Unlock(pDSLockedBuffer, dwDSLockedBufferSize, NULL, 0);

	// Clean up
	delete wavFile;

	return apDSBuffer;
}

void GSound::playSound(int ID)
{
	DSBuffer[ID]->Play(0, 0, 0);
}

void GSound::playSoundLoop(int ID)
{
	DSBuffer[ID]->Play(0, 0, DSBPLAY_LOOPING);
}

void GSound::stopSound(int ID )
{
	DSBuffer[ID]->Stop();
}
