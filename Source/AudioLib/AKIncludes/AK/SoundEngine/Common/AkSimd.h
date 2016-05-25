//////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006 Audiokinetic Inc. / All Rights Reserved
//
//////////////////////////////////////////////////////////////////////

// AkSimd.h

/// \file 
/// Simd definitions.

#ifndef _AK_SIMD_H_
#define _AK_SIMD_H_

#include <AK/SoundEngine/Common/AkTypes.h>

// Platform-specific section.
//----------------------------------------------------------------------------------------------------

#if defined( AK_WIN )
	
	#include <AK/SoundEngine/Platforms/Windows/AkSimd.h>

#elif defined( AK_APPLE )

	#include <TargetConditionals.h>
	#if TARGET_OS_IPHONE
		#include <AK/SoundEngine/Platforms/iOS/AkSimd.h>
	#else
	#include <AK/SoundEngine/Platforms/Mac/AkSimd.h>
	#endif

#elif defined( AK_XBOX360 )

	#include <AK/SoundEngine/Platforms/XBox360/AkSimd.h>

#elif defined (AK_PS3)

	#include <AK/SoundEngine/Platforms/PS3/AkSimd.h>
#elif defined( AK_WII )

	#include <AK/SoundEngine/Platforms/Generic/AkSimd.h>
	
#elif defined( AK_NGP )

	#include <AK/SoundEngine/Platforms/NGP/AkSimd.h>

#elif defined( AK_3DS )

	#include <AK/SoundEngine/Platforms/3DS/AkSimd.h>

#elif defined( AK_ANDROID )

	#include <AK/SoundEngine/Platforms/Android/AkSimd.h>

#elif defined( AK_NACL )

	#include <AK/SoundEngine/Platforms/nacl/AkSimd.h>
	
#elif defined( AK_WIIU )

	#include <AK/SoundEngine/Platforms/WiiFamily/AkSimd.h>
	
#else
	#error Unsupported platform, or platform-specific SIMD not defined
#endif

#endif  //_AK_DATA_TYPES_H_
