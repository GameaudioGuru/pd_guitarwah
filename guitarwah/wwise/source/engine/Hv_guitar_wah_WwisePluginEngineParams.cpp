/**
 * Copyright (c) 2018 Enzien Audio, Ltd.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions, and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the phrase "powered by heavy",
 *    the heavy logo, and a hyperlink to https://enzienaudio.com, all in a visible
 *    form.
 * 
 *   2.1 If the Application is distributed in a store system (for example,
 *       the Apple "App Store" or "Google Play"), the phrase "powered by heavy"
 *       shall be included in the app description or the copyright text as well as
 *       the in the app itself. The heavy logo will shall be visible in the app
 *       itself as well.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#include "Hv_guitar_wah_WwisePluginEngineParams.h"
#include <AK/Tools/Common/AkBankReadHelpers.h>

Hv_guitar_wah_EngineParams::Hv_guitar_wah_EngineParams() {

}

Hv_guitar_wah_EngineParams::Hv_guitar_wah_EngineParams(const Hv_guitar_wah_EngineParams & in_rCopy) {
  m_Params = in_rCopy.m_Params;
}

Hv_guitar_wah_EngineParams::~Hv_guitar_wah_EngineParams() {

}

AK::IAkPluginParam * Hv_guitar_wah_EngineParams::Clone(AK::IAkPluginMemAlloc *in_pAllocator) {
  return AK_PLUGIN_NEW(in_pAllocator, Hv_guitar_wah_EngineParams(*this));
}

AKRESULT Hv_guitar_wah_EngineParams::Init(
    AK::IAkPluginMemAlloc *in_pAllocator, const void *in_pParamsBlock, AkUInt32 in_uBlockSize) {
  if (in_uBlockSize == 0) {
    // Init with default values if we got invalid parameter block.
    // Generated RTPCs
    m_Params.fHVParam_LFO_freq = 2.0f;
    m_Params.fHVParam_Q = 5.3f;
    m_Params.fHVParam_max_freq_range = 1500.0f;
    m_Params.fHVParam_min_freq_range = 200.0f;

    return AK_Success;
  }

  return SetParamsBlock(in_pParamsBlock, in_uBlockSize);
}

AKRESULT Hv_guitar_wah_EngineParams::Term(
    AK::IAkPluginMemAlloc *in_pAllocator) {
  AK_PLUGIN_DELETE(in_pAllocator, this);
  return AK_Success;
}

AKRESULT Hv_guitar_wah_EngineParams::SetParamsBlock(
    const void *in_pParamsBlock, AkUInt32 in_ulBlockSize) {

  AKRESULT eResult = AK_Success;
  AkUInt8 *pParamsBlock = (AkUInt8 *) in_pParamsBlock;

  // Retrieve generated Heavy parameters
  m_Params.fHVParam_LFO_freq = READBANKDATA(AkReal32, pParamsBlock, in_ulBlockSize);
  m_Params.fHVParam_Q = READBANKDATA(AkReal32, pParamsBlock, in_ulBlockSize);
  m_Params.fHVParam_max_freq_range = READBANKDATA(AkReal32, pParamsBlock, in_ulBlockSize);
  m_Params.fHVParam_min_freq_range = READBANKDATA(AkReal32, pParamsBlock, in_ulBlockSize);

  CHECKBANKDATASIZE(in_ulBlockSize, eResult);

  return eResult;
}

AKRESULT Hv_guitar_wah_EngineParams::SetParam(AkPluginParamID in_ParamID,
  const void *in_pValue, AkUInt32 in_uParamSize) {
  if (in_pValue == NULL) return AK_InvalidParameter; // Consistency check

  // Set parameter value.
  switch (in_ParamID) {
    case HV_GUITAR_WAH_PARAM_IN_LFO_FREQ_ID: {
      // This parameter is RTPCed
      m_Params.fHVParam_LFO_freq = *reinterpret_cast<const AkReal32*>(in_pValue);
      break;
    }
    case HV_GUITAR_WAH_PARAM_IN_Q_ID: {
      // This parameter is RTPCed
      m_Params.fHVParam_Q = *reinterpret_cast<const AkReal32*>(in_pValue);
      break;
    }
    case HV_GUITAR_WAH_PARAM_IN_MAX_FREQ_RANGE_ID: {
      // This parameter is RTPCed
      m_Params.fHVParam_max_freq_range = *reinterpret_cast<const AkReal32*>(in_pValue);
      break;
    }
    case HV_GUITAR_WAH_PARAM_IN_MIN_FREQ_RANGE_ID: {
      // This parameter is RTPCed
      m_Params.fHVParam_min_freq_range = *reinterpret_cast<const AkReal32*>(in_pValue);
      break;
    }
    default: AKASSERT(!"Unknown parameter"); break;
  }

  return AK_Success;
}
