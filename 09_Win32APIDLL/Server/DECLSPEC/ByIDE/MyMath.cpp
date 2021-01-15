#include<windows.h>
#include"MyMath.h"

//Entry Point Function
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved)
{
	//Code DLL Injection , Antiviruse code, DLL API hooking
	// It is covention to write this four cases take convetion as complusion

	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		//DLL Engection cha code
		break;

	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		break;

	default:
		break;
	}

	return(TRUE);
}

//Exported Function Defination
 __declspec(dllexport) int MakeSquare(int iNum)
{
	//Code
	return (iNum * iNum);
}

