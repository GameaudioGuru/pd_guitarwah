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

#ifndef _HEAVY_CONTEXT_GUITAR_WAH_HPP_
#define _HEAVY_CONTEXT_GUITAR_WAH_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvControlIf.h"
#include "HvControlBinop.h"
#include "HvControlVar.h"
#include "HvControlSystem.h"
#include "HvSignalVar.h"
#include "HvSignalPhasor.h"
#include "HvSignalCPole.h"
#include "HvMath.h"
#include "HvControlCast.h"
#include "HvSignalDel1.h"

class Heavy_guitar_wah : public HeavyContext {

 public:
  Heavy_guitar_wah(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_guitar_wah();

  const char *getName() override { return "guitar_wah"; }
  int getNumInputChannels() override { return 2; }
  int getNumOutputChannels() override { return 2; }

  int process(float **inputBuffers, float **outputBuffer, int n) override;
  int processInline(float *inputBuffers, float *outputBuffer, int n) override;
  int processInlineInterleaved(float *inputBuffers, float *outputBuffer, int n) override;

  int getParameterInfo(int index, HvParameterInfo *info) override;
  struct Parameter {
    struct In {
      enum ParameterIn : hv_uint32_t {
        LFO_FREQ = 0x88333B78, // LFO_freq
        Q = 0xF3BA5CD4, // Q
        MAX_FREQ_RANGE = 0x19D82182, // max_freq_range
        MIN_FREQ_RANGE = 0xF5BA36CE, // min_freq_range
      };
    };
  };

 private:
  HvTable *getTableForHash(hv_uint32_t tableHash) override;
  void scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) override;

  // static sendMessage functions
  static void cVar_2CPBNBmB_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_7q7DHqpz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_D8sgubXi_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_UVzForsD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_e4hGIjek_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_I9V5P995_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_NXcTjDbK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_oHxRiyAQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_uuPTVOY4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_6xo2fYox_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_hQAh4z4J_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_fZAMdWsL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_Wzg8wvfE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_nMMA4Oea_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_zEXIJ3z2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_mouEMmqG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_1M6wvoMX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_9HDcgU9N_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Z9BGJHQu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_un3FSksJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_klo1Y6Li_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_oDLP9kEz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_WN3EmOj0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_zv4pNIHm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_8WmemQVH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_IIw8mTNu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_YEYowrwZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_AquGw69A_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_xo7IkE5S_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_YVlqYutm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_6cEL1NXt_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalPhasor sPhasor_cd618YKz;
  SignalCPole sCPole_p4Nk471Y;
  ControlVar cVar_2CPBNBmB;
  ControlVar cVar_e4hGIjek;
  ControlVar cVar_I9V5P995;
  ControlVar cVar_oHxRiyAQ;
  ControlVar cVar_6xo2fYox;
  ControlVar cVar_fZAMdWsL;
  ControlVar cVar_Wzg8wvfE;
  ControlBinop cBinop_zEXIJ3z2;
  ControlBinop cBinop_9HDcgU9N;
  SignalVarf sVarf_ka8yPoIW;
  ControlBinop cBinop_Z9BGJHQu;
  ControlIf cIf_un3FSksJ;
  ControlBinop cBinop_klo1Y6Li;
  SignalVarf sVarf_xQc5lZEa;
  ControlVar cVar_8WmemQVH;
  ControlBinop cBinop_IIw8mTNu;
  SignalVarf sVarf_vkdO7h5k;
  ControlBinop cBinop_YEYowrwZ;
  SignalVarf sVarf_4UtP56D2;
  SignalVarf sVarf_vQISq2wQ;
  ControlBinop cBinop_YVlqYutm;
  SignalVarf sVarf_AGcf4SHR;
};

#endif // _HEAVY_CONTEXT_GUITAR_WAH_HPP_
