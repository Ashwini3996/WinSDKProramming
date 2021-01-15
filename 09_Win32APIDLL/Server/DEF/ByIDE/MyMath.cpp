#include<windows.h>
#include"MyMath.h"

/*
// For Export data but it is not relible it is rlible only in COM
//compiler la order kartoy mazasathi data segmaent tayar kr 
#pragma data_seg("temp")
int num = 420;
#pragma data_seg
#pragma comment(linker,"/SECTION:temp,RWS")//section la readable writable banav
*/

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
 extern "C" int MakeSquare(int iNum)
{
	//Code
	return (iNum * iNum);
}

