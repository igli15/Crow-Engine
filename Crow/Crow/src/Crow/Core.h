#pragma once

//Sets up some defines to automate the dllexport and import for windows only(for now at least)

#ifdef CR_PLATFORM_WINDOWS

	#ifdef CR_BUILD_DLL
		#define CROW_API __declspec(dllexport)
	#else
		#define CROW_API  __declspec(dllimport)
	#endif
#else
	#error Currently Crow only works on Windows Platform!
#endif