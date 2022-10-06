/*
 *  tvheadend - Codec Profiles
 *
 *  Copyright (C) 2016 Tvheadend
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "transcoding/codec/internals.h"

/*
h263_v4l2m2m
hevc_v4l2m2m
mpeg4_v4l2m2m
vc1_v4l2m2m
vp8_v4l2m2m
vp9_v4l2m2m
*/

/* v4l2m2m ====================================================================== */

#define V4L2_ENC_LEVEL_AUTOSELECT                     0
#define V4L2_ENC_LEVEL_H264_1                         10
#define V4L2_ENC_LEVEL_H264_1b                        9
#define V4L2_ENC_LEVEL_H264_11                        11
#define V4L2_ENC_LEVEL_H264_12                        12
#define V4L2_ENC_LEVEL_H264_13                        13
#define V4L2_ENC_LEVEL_H264_2                         20
#define V4L2_ENC_LEVEL_H264_21                        21
#define V4L2_ENC_LEVEL_H264_22                        22
#define V4L2_ENC_LEVEL_H264_3                         30
#define V4L2_ENC_LEVEL_H264_31                        31
#define V4L2_ENC_LEVEL_H264_32                        32
#define V4L2_ENC_LEVEL_H264_4                         40
#define V4L2_ENC_LEVEL_H264_41                        41
#define V4L2_ENC_LEVEL_H264_42                        42
#define V4L2_ENC_LEVEL_H264_5                         50
#define V4L2_ENC_LEVEL_H264_51                        51
#define V4L2_ENC_LEVEL_H264_6                         60
#define V4L2_ENC_LEVEL_H264_61                        61
#define V4L2_ENC_LEVEL_H264_62                        62

typedef struct {
    TVHVideoCodecProfile;
    int level;
} tvh_codec_profile_v4l2m2m_t;

static const AVProfile v4l2m2m_h264_profiles[] = {
    { FF_PROFILE_H264_CONSTRAINED_BASELINE, "Constrained Baseline" },
    { FF_PROFILE_H264_MAIN,                 "Main" },
    { FF_PROFILE_H264_HIGH,                 "High" },
    { FF_PROFILE_UNKNOWN },
};

static int
tvh_codec_profile_v4l2m2m_open(tvh_codec_profile_v4l2m2m_t *self, AVDictionary **opts)
{
    static const struct strtab leveltab[] = {
        {"Auto",	      V4L2_ENC_LEVEL_AUTOSELECT},
        {"1.0",           V4L2_ENC_LEVEL_H264_1},
        {"1.0b",          V4L2_ENC_LEVEL_H264_1b},
        {"1.1",           V4L2_ENC_LEVEL_H264_11},
        {"1.2",           V4L2_ENC_LEVEL_H264_12},
        {"1.3",           V4L2_ENC_LEVEL_H264_13},
        {"2.0",           V4L2_ENC_LEVEL_H264_2},
        {"2.1",           V4L2_ENC_LEVEL_H264_21},
        {"2.2",           V4L2_ENC_LEVEL_H264_22},
        {"3.0",           V4L2_ENC_LEVEL_H264_3},
        {"3.1",           V4L2_ENC_LEVEL_H264_31},
        {"3.2",           V4L2_ENC_LEVEL_H264_32},
        {"4.0",           V4L2_ENC_LEVEL_H264_4},
        {"4.1",           V4L2_ENC_LEVEL_H264_41},
        {"4.2",           V4L2_ENC_LEVEL_H264_42},
        {"5.0",           V4L2_ENC_LEVEL_H264_5},
        {"5.1",           V4L2_ENC_LEVEL_H264_51},
        {"6.0",           V4L2_ENC_LEVEL_H264_6},
        {"6.1",           V4L2_ENC_LEVEL_H264_61},
        {"6.2",           V4L2_ENC_LEVEL_H264_62},
    };

    const char *s;

    if (self->level != V4L2_ENC_LEVEL_AUTOSELECT &&
        (s = val2str(self->level, leveltab)) != NULL) {
        AV_DICT_SET(opts, "level", s, 0);
    }

    AV_DICT_SET_FLAGS_GLOBAL_HEADER(opts);
    // bit_rate
    if (self->bit_rate) {
        AV_DICT_SET_BIT_RATE(opts, self->bit_rate);
    }

    // max_b_frames
    // XXX: remove when b-frames handling in vaapi_encode is fixed
    //AV_DICT_SET_INT(opts, "bf", 0, 0);

    return 0;
}

static htsmsg_t *
codec_profile_v4l2m2m_class_level_list_h264(void *obj, const char *lang)
{
    static const struct strtab tab[] = {
        {N_("Auto"),	      V4L2_ENC_LEVEL_AUTOSELECT},
        {N_("1.0"),           V4L2_ENC_LEVEL_H264_1},
        {N_("1.0b"),          V4L2_ENC_LEVEL_H264_1b},
        {N_("1.1"),           V4L2_ENC_LEVEL_H264_11},
        {N_("1.2"),           V4L2_ENC_LEVEL_H264_12},
        {N_("1.3"),           V4L2_ENC_LEVEL_H264_13},
        {N_("2.0"),           V4L2_ENC_LEVEL_H264_2},
        {N_("2.1"),           V4L2_ENC_LEVEL_H264_21},
        {N_("2.2"),           V4L2_ENC_LEVEL_H264_22},
        {N_("3.0"),           V4L2_ENC_LEVEL_H264_3},
        {N_("3.1"),           V4L2_ENC_LEVEL_H264_31},
        {N_("3.2"),           V4L2_ENC_LEVEL_H264_32},
        {N_("4.0"),           V4L2_ENC_LEVEL_H264_4},
        {N_("4.1"),           V4L2_ENC_LEVEL_H264_41},
        {N_("4.2"),           V4L2_ENC_LEVEL_H264_42},
        {N_("5.0"),           V4L2_ENC_LEVEL_H264_5},
        {N_("5.1"),           V4L2_ENC_LEVEL_H264_51},
        {N_("6.0"),           V4L2_ENC_LEVEL_H264_6},
        {N_("6.1"),           V4L2_ENC_LEVEL_H264_61},
        {N_("6.2"),           V4L2_ENC_LEVEL_H264_62},
    };
    return strtab2htsmsg(tab, 1, lang);
}

static const codec_profile_class_t codec_profile_v4l2m2m_class = {
    {
        .ic_super   = (idclass_t *)&codec_profile_video_class,
        .ic_class   = "codec_profile_v4l2m2m",
        .ic_caption = N_("v4l2m2m_h264"),
        .ic_properties = (const property_t[]){
            {}
        }
    },
    .open = (codec_profile_open_meth)tvh_codec_profile_v4l2m2m_open,
};

/* h264_v4l2m2m ================================================================= */

TVHVideoCodec tvh_codec_v4l2m2m_h264 = {
    .name    = "h264_v4l2m2m",
    .size    = sizeof(tvh_codec_profile_v4l2m2m_t),
    .idclass = &codec_profile_v4l2m2m_class,
    .profiles = v4l2m2m_h264_profiles,
    .profile_init = tvh_codec_profile_video_init,
    .profile_destroy = tvh_codec_profile_video_destroy,
};
