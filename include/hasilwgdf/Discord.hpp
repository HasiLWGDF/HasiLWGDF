/*
	HasiLWGDF (Hasibix's Lightweight Game Development Framework)

	A simple, cross-platform game engine made with C++.
	Supports multiple graphics APIs and built on top of open-source
	resources.

	Copyright (c) 2024 Hasibix Hasib. All Rights Reserved.

	Thank you so much for using HasiLWGDF. Feel free to contribute our project.
	For more information, please visit https://github.com/HasiLWGDF/HasiLWGDF.

	This library is licensed under GNU Lesser General Public License version 3 (LGPLv3).
	You can find copy of the license from https://www.gnu.org/licenses.

	It is recommended NOT to modify this file. As doing such may result in compatibility
	issues or even PERMANENT damage to your project.
	DO NOT MODIFY THIS FILE UNLESS IT IS NECESSARY TO DO SO.
*/

#pragma once

#include <memory>
#include <stdint.h>
#include "Game.hpp"
#include "utils/Export.hpp"

#ifdef __cplusplus
extern "C"
{
#endif
	namespace Hasibix::HasiLWGDF::Core
	{
		class Discord final
		{
		public:
			struct Timestamps
			{
				int64_t start;
				int64_t end;
			};

			struct Secrets
			{
				const char *match;	  /* max 128 bytes */
				const char *join;	  /* max 128 bytes */
				const char *spectate; /* max 128 bytes */
			};

			struct PartySize
			{
				int current;
				int max;
			};

			typedef struct Party
			{
				const char *id; /* max 128 bytes */
				PartySize size;
				int privacy;
			} Party;

			struct Assets
			{
				const char *largeImage; /* max 128 bytes */
				const char *largeText;	/* max 128 bytes */
				const char *smallImage; /* max 128 bytes */
				const char *smallText;	/* max 128 bytes */
			};

			struct Activity
			{
				const char *state;	 /* max 128 bytes */
				const char *details; /* max 128 bytes */
				Timestamps timestamps;
				Assets assets;
				Party party;
				Secrets secrets;
				bool instance;
			};

		private:
			friend class Hasibix::HasiLWGDF::Core::Game;
			static std::unique_ptr<Activity> &currentActivity;

			Discord() = delete;

		public:
			/*
			 Sets the rich presence activity if an instance of Discord is running.
			 @warning If activity is not nullptr, it copies the object to an std::unique_ptr and DELETE the regular pointer passed to it.
			 @returns void
			 @param Activity *activity
			 */
			HASILWGDF_EXPORT static void setActivity(Activity *activity);
		};
	}
#ifdef __cplusplus
}
#endif
