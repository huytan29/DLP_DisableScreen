#include <WinSDKVer.h>

//
// _WIN32_WINNT version constants
//
#define _WIN32_WINNT _WIN32_WINNT_NT4                    
#define _WIN32_WINNT _WIN32_WINNT_WIN2K               
#define _WIN32_WINNT _WIN32_WINNT_WINXP                 
#define _WIN32_WINNT _WIN32_WINNT_WS03                   
#define _WIN32_WINNT _WIN32_WINNT_WIN6                  
#define _WIN32_WINNT _WIN32_WINNT_VISTA                 
#define _WIN32_WINNT _WIN32_WINNT_WS08                   
#define _WIN32_WINNT _WIN32_WINNT_LONGHORN             
#define _WIN32_WINNT _WIN32_WINNT_WIN7                  
#define _WIN32_WINNT _WIN32_WINNT_WIN8                  
#define _WIN32_WINNT _WIN32_WINNT_WINBLUE             
#define _WIN32_WINNT _WIN32_WINNT_WINTHRESHOLD          
#define _WIN32_WINNT _WIN32_WINNT_WIN10                  
// . . .

#define WDK_NTDDI_VERSION                   NTDDI_WIN10_19H1 /* ABRACADABRA_WIN10_19H1 */
#define WDK_NTDDI_VERSION                   NTDDI_WIN10_20H2

#define OSVERSION_MASK	0xFFFF0000
#define SPVERSION_MASK	0x0000FF00
#define SUBVERSION_MASK	0x000000FF  

#define OSVER(Version)  ((Version) & OSVERSION_MASK)
#define SPVER(Version)  (((Version) & SPVERSION_MASK) >> 8)
#define SUBVER(Version) (((Version) & SUBVERSION_MASK))
 
#include <sdkddkver.h>

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef _WIN64
#define TARGET_BIT 64
#define my_strtoul strtoull
#else
#define TARGET_BIT 32
#define my_strtoul strtoul
#endif

#define _STR(s) #s
#define STR(s) _STR(s)

#include "../core/core.hpp"

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		fputs("Usage: NoScreenCap" STR(TARGET_BIT) ".com <window handle> [disable capture(0/1)]", stderr);
	}
	else
	{
		HWND hWnd = reinterpret_cast<HWND>(my_strtoul(argv[1], nullptr, 0));
	if (argc == 2)
		{
			DWORD affinity;  
			if (GetWindowDisplayAffinity(hWnd, &affinity))
			{
				printf("%d", affinity);
				return 0;
			}

			else
			{
				fprintf(stderr, "GetWindowDisplayAffinity failed. (%u)", GetLastError());
			}
		}
		else
		{
			AdjustDebugPrivs();

			DWORD affinity = strtoul(argv[2], nullptr, 10);
			if (SetWindowDisplayAffinityForExternelProcess(hWnd, !affinity))
				return 0;
		}
	}
	return 1;
}
