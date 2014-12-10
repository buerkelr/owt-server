/*
 * Copyright 2014 Intel Corporation All Rights Reserved. 
 * 
 * The source code contained or described herein and all documents related to the 
 * source code ("Material") are owned by Intel Corporation or its suppliers or 
 * licensors. Title to the Material remains with Intel Corporation or its suppliers 
 * and licensors. The Material contains trade secrets and proprietary and 
 * confidential information of Intel or its suppliers and licensors. The Material 
 * is protected by worldwide copyright and trade secret laws and treaty provisions. 
 * No part of the Material may be used, copied, reproduced, modified, published, 
 * uploaded, posted, transmitted, distributed, or disclosed in any way without 
 * Intel's prior express written permission.
 * 
 * No license under any patent, copyright, trade secret or other intellectual 
 * property right is granted to or conferred upon you by disclosure or delivery of 
 * the Materials, either expressly, by implication, inducement, estoppel or 
 * otherwise. Any license under such intellectual property rights must be express 
 * and approved by Intel in writing.
 */

#ifndef FakedVideoFrameDecoder_h
#define FakedVideoFrameDecoder_h

#include "VideoFramePipeline.h"

#include <boost/shared_ptr.hpp>

namespace mcu {

// A FakedVideoFrameDecoder doesn't do real decoding stuffs.
// Or in other words, it "decodes" a frame into the same format frame.
class FakedVideoFrameDecoder : public VideoFrameDecoder {
public:
    FakedVideoFrameDecoder(int slot, boost::shared_ptr<EncodedVideoFrameCompositor>);
    ~FakedVideoFrameDecoder();

    bool setInput(FrameFormat, VideoFrameProvider*);
    void unsetInput();
    void onFrame(FrameFormat, unsigned char* payload, int len, unsigned int ts);

private:
    int m_slot;
    boost::shared_ptr<EncodedVideoFrameCompositor> m_compositor;
};

FakedVideoFrameDecoder::FakedVideoFrameDecoder(int slot, boost::shared_ptr<EncodedVideoFrameCompositor> compositor)
    : m_slot(slot)
    , m_compositor(compositor)
{
}

FakedVideoFrameDecoder::~FakedVideoFrameDecoder()
{
}

inline void FakedVideoFrameDecoder::onFrame(FrameFormat format, unsigned char* payload, int len, unsigned int ts)
{
    m_compositor->pushInput(m_slot, payload, len);
}

inline bool FakedVideoFrameDecoder::setInput(FrameFormat format, VideoFrameProvider* provider)
{
    m_compositor->activateInput(m_slot, format, provider);
    return true;
}

inline void FakedVideoFrameDecoder::unsetInput()
{
    m_compositor->deActivateInput(m_slot);
}

}
#endif