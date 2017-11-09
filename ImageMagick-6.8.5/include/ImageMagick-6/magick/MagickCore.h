/*
  Copyright 1999-2013 ImageMagick Studio LLC, a non-profit organization
  dedicated to making software imaging solutions freely available.
  
  You may not use this file except in compliance with the License.
  obtain a copy of the License at
  
    http://www.imagemagick.org/script/license.php
  
  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  MagickCore Application Programming Interface declarations.
*/

#ifndef _MAGICKCORE_CORE_H
#define _MAGICKCORE_CORE_H

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#if !defined(_MAGICKCORE_CONFIG_H)
# define _MAGICKCORE_CONFIG_H
# if !defined(vms) && !defined(macintosh)
#  include "ImageMagick-6/magick/magick-config.h"
# else
#  include "magick-config.h"
# endif
#if defined(_magickcore_const) && !defined(const)
# define const _magickcore_const
#endif
#if defined(_magickcore_inline) && !defined(inline)
# define inline _magickcore_inline
#endif
#if defined(_magickcore_restrict) && !defined(restrict)
# define restrict  _magickcore_restrict
#endif
# if defined(__cplusplus) || defined(c_plusplus)
#  undef inline
# endif
#endif

#define MAGICKCORE_CHECK_VERSION(major,minor,micro) \
  ((MAGICKCORE_MAJOR_VERSION > (major)) || \
    ((MAGICKCORE_MAJOR_VERSION == (major)) && \
     (MAGICKCORE_MINOR_VERSION > (minor))) || \
    ((MAGICKCORE_MAJOR_VERSION == (major)) && \
     (MAGICKCORE_MINOR_VERSION == (minor)) && \
     (MAGICKCORE_MICRO_VERSION >= (micro))))

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/types.h>

#if defined(WIN32) || defined(WIN64)
#  define MAGICKCORE_WINDOWS_SUPPORT
#else
#  define MAGICKCORE_POSIX_SUPPORT
#endif 

#include "ImageMagick-6/magick/method-attribute.h"

#if defined(MAGICKCORE_NAMESPACE_PREFIX)
# include "magick/methods.h"
#endif
#include "ImageMagick-6/magick/magick-type.h"
#include "ImageMagick-6/magick/accelerate.h"
#include "ImageMagick-6/magick/animate.h"
#include "ImageMagick-6/magick/annotate.h"
#include "ImageMagick-6/magick/artifact.h"
#include "ImageMagick-6/magick/attribute.h"
#include "ImageMagick-6/magick/blob.h"
#include "ImageMagick-6/magick/cache.h"
#include "ImageMagick-6/magick/cache-view.h"
#include "ImageMagick-6/magick/channel.h"
#include "ImageMagick-6/magick/cipher.h"
#include "ImageMagick-6/magick/client.h"
#include "ImageMagick-6/magick/coder.h"
#include "ImageMagick-6/magick/color.h"
#include "ImageMagick-6/magick/colorspace.h"
#include "ImageMagick-6/magick/colormap.h"
#include "ImageMagick-6/magick/compare.h"
#include "ImageMagick-6/magick/composite.h"
#include "ImageMagick-6/magick/compress.h"
#include "ImageMagick-6/magick/configure.h"
#include "ImageMagick-6/magick/constitute.h"
#include "ImageMagick-6/magick/decorate.h"
#include "ImageMagick-6/magick/delegate.h"
#include "ImageMagick-6/magick/deprecate.h"
#include "ImageMagick-6/magick/display.h"
#include "ImageMagick-6/magick/distort.h"
#include "ImageMagick-6/magick/distribute-cache.h"
#include "ImageMagick-6/magick/draw.h"
#include "ImageMagick-6/magick/effect.h"
#include "ImageMagick-6/magick/enhance.h"
#include "ImageMagick-6/magick/exception.h"
#include "ImageMagick-6/magick/feature.h"
#include "ImageMagick-6/magick/fourier.h"
#include "ImageMagick-6/magick/fx.h"
#include "ImageMagick-6/magick/gem.h"
#include "ImageMagick-6/magick/geometry.h"
#include "ImageMagick-6/magick/hashmap.h"
#include "ImageMagick-6/magick/histogram.h"
#include "ImageMagick-6/magick/identify.h"
#include "ImageMagick-6/magick/image.h"
#include "ImageMagick-6/magick/image-view.h"
#include "ImageMagick-6/magick/layer.h"
#include "ImageMagick-6/magick/list.h"
#include "ImageMagick-6/magick/locale_.h"
#include "ImageMagick-6/magick/log.h"
#include "ImageMagick-6/magick/magic.h"
#include "ImageMagick-6/magick/magick.h"
#include "ImageMagick-6/magick/matrix.h"
#include "ImageMagick-6/magick/memory_.h"
#include "ImageMagick-6/magick/module.h"
#include "ImageMagick-6/magick/mime.h"
#include "ImageMagick-6/magick/monitor.h"
#include "ImageMagick-6/magick/montage.h"
#include "ImageMagick-6/magick/morphology.h"
#include "ImageMagick-6/magick/option.h"
#include "ImageMagick-6/magick/paint.h"
#include "ImageMagick-6/magick/pixel.h"
#include "ImageMagick-6/magick/pixel-accessor.h"
#include "ImageMagick-6/magick/policy.h"
#include "ImageMagick-6/magick/prepress.h"
#include "ImageMagick-6/magick/profile.h"
#include "ImageMagick-6/magick/property.h"
#include "ImageMagick-6/magick/quantize.h"
#include "ImageMagick-6/magick/quantum.h"
#include "ImageMagick-6/magick/registry.h"
#include "ImageMagick-6/magick/random_.h"
#include "ImageMagick-6/magick/resample.h"
#include "ImageMagick-6/magick/resize.h"
#include "ImageMagick-6/magick/resource_.h"
#include "ImageMagick-6/magick/segment.h"
#include "ImageMagick-6/magick/shear.h"
#include "ImageMagick-6/magick/signature.h"
#include "ImageMagick-6/magick/splay-tree.h"
#include "ImageMagick-6/magick/stream.h"
#include "ImageMagick-6/magick/statistic.h"
#include "ImageMagick-6/magick/string_.h"
#include "ImageMagick-6/magick/timer.h"
#include "ImageMagick-6/magick/token.h"
#include "ImageMagick-6/magick/transform.h"
#include "ImageMagick-6/magick/threshold.h"
#include "ImageMagick-6/magick/type.h"
#include "ImageMagick-6/magick/utility.h"
#include "ImageMagick-6/magick/version.h"
#include "ImageMagick-6/magick/xml-tree.h"
#include "ImageMagick-6/magick/xwindow.h"

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
