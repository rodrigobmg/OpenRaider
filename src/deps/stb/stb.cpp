/*!
 * \file src/deps/stb/stb.cpp
 * \brief stb implementation
 *
 * \author xythobuz
 */

#include "global.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT(x) assert(x)
#include "stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#define STB_RECT_PACK_IMPLEMENTATION
#define STBRP_ASSERT assert
#include "stb/stb_rect_pack.h"

#define STB_TRUETYPE_IMPLEMENTATION
#define STBTT_assert(x) assert(x)
#include "stb/stb_truetype.h"

