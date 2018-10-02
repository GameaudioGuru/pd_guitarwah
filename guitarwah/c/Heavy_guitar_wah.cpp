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

#include "Heavy_guitar_wah.hpp"

#define Context(_c) reinterpret_cast<Heavy_guitar_wah *>(_c)



/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_guitar_wah_new(double sampleRate) {
    return new Heavy_guitar_wah(sampleRate);
  }

  HV_EXPORT HeavyContextInterface *hv_guitar_wah_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    return new Heavy_guitar_wah(sampleRate, poolKb, inQueueKb, outQueueKb);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_guitar_wah::Heavy_guitar_wah(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sPhasor_k_init(&sPhasor_cd618YKz, 2.0f, sampleRate);
  numBytes += sCPole_init(&sCPole_p4Nk471Y);
  numBytes += cVar_init_f(&cVar_2CPBNBmB, 0.0f);
  numBytes += cVar_init_f(&cVar_e4hGIjek, 0.0f);
  numBytes += cVar_init_f(&cVar_I9V5P995, 0.0f);
  numBytes += cVar_init_f(&cVar_oHxRiyAQ, 0.0f);
  numBytes += cVar_init_f(&cVar_6xo2fYox, 0.0f);
  numBytes += cVar_init_f(&cVar_fZAMdWsL, 0.0f);
  numBytes += cVar_init_f(&cVar_Wzg8wvfE, 0.0f);
  numBytes += sVarf_init(&sVarf_ka8yPoIW, 0.0f, 0.0f, false);
  numBytes += cIf_init(&cIf_un3FSksJ, false);
  numBytes += sVarf_init(&sVarf_xQc5lZEa, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_8WmemQVH, 0.0f);
  numBytes += sVarf_init(&sVarf_vkdO7h5k, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_4UtP56D2, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_vQISq2wQ, 200.0f, 0.0f, false);
  numBytes += cBinop_init(&cBinop_YVlqYutm, 0.0f); // __sub
  numBytes += sVarf_init(&sVarf_AGcf4SHR, 1500.0f, 0.0f, false);
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_guitar_wah::~Heavy_guitar_wah() {
  // nothing to free
}

HvTable *Heavy_guitar_wah::getTableForHash(hv_uint32_t tableHash) {
  return nullptr;
}

void Heavy_guitar_wah::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0x88333B78: { // LFO_freq
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_UVzForsD_sendMessage);
      break;
    }
    case 0xF3BA5CD4: { // Q
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_uuPTVOY4_sendMessage);
      break;
    }
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_D8sgubXi_sendMessage);
      break;
    }
    case 0x19D82182: { // max_freq_range
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_NXcTjDbK_sendMessage);
      break;
    }
    case 0xF5BA36CE: { // min_freq_range
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_6cEL1NXt_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_guitar_wah::getParameterInfo(int index, HvParameterInfo *info) {
  if (info != nullptr) {
    switch (index) {
      case 0: {
        info->name = "Q";
        info->hash = 0xF3BA5CD4;
        info->type = HvParameterType::HV_PARAM_TYPE_PARAMETER_IN;
        info->minVal = 0.1f;
        info->maxVal = 20.0f;
        info->defaultVal = 5.3f;
        break;
      }
      case 1: {
        info->name = "LFO_freq";
        info->hash = 0x88333B78;
        info->type = HvParameterType::HV_PARAM_TYPE_PARAMETER_IN;
        info->minVal = 0.0f;
        info->maxVal = 20.0f;
        info->defaultVal = 2.0f;
        break;
      }
      case 2: {
        info->name = "min_freq_range";
        info->hash = 0xF5BA36CE;
        info->type = HvParameterType::HV_PARAM_TYPE_PARAMETER_IN;
        info->minVal = 0.0f;
        info->maxVal = 700.0f;
        info->defaultVal = 200.0f;
        break;
      }
      case 3: {
        info->name = "max_freq_range";
        info->hash = 0x19D82182;
        info->type = HvParameterType::HV_PARAM_TYPE_PARAMETER_IN;
        info->minVal = 700.0f;
        info->maxVal = 6000.0f;
        info->defaultVal = 1500.0f;
        break;
      }
      default: {
        info->name = "invalid parameter index";
        info->hash = 0;
        info->type = HvParameterType::HV_PARAM_TYPE_PARAMETER_IN;
        info->minVal = 0.0f;
        info->maxVal = 0.0f;
        info->defaultVal = 0.0f;
        break;
      }
    }
  }
  return 4;
}



/*
 * Send Function Implementations
 */


void Heavy_guitar_wah::cVar_2CPBNBmB_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sPhasor_k_onMessage(_c, &Context(_c)->sPhasor_cd618YKz, 0, m);
}

void Heavy_guitar_wah::cMsg_7q7DHqpz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 5.3f);
  cVar_onMessage(_c, &Context(_c)->cVar_I9V5P995, 0, m, &cVar_I9V5P995_sendMessage);
}

void Heavy_guitar_wah::cReceive_D8sgubXi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_oDLP9kEz_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_8WmemQVH, 0, m, &cVar_8WmemQVH_sendMessage);
  cMsg_7q7DHqpz_sendMessage(_c, 0, m);
}

void Heavy_guitar_wah::cReceive_UVzForsD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sPhasor_k_onMessage(_c, &Context(_c)->sPhasor_cd618YKz, 0, m);
}

void Heavy_guitar_wah::cVar_e4hGIjek_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_Wzg8wvfE, 0, m, &cVar_Wzg8wvfE_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_YVlqYutm, HV_BINOP_SUBTRACT, 1, m, &cBinop_YVlqYutm_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_hQAh4z4J_sendMessage);
  sVarf_onMessage(_c, &Context(_c)->sVarf_vQISq2wQ, m);
}

void Heavy_guitar_wah::cVar_I9V5P995_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_6xo2fYox, 0, m, &cVar_6xo2fYox_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_8WmemQVH, 0, m, &cVar_8WmemQVH_sendMessage);
}

void Heavy_guitar_wah::cReceive_NXcTjDbK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_YVlqYutm, HV_BINOP_SUBTRACT, 0, m, &cBinop_YVlqYutm_sendMessage);
}

void Heavy_guitar_wah::cVar_oHxRiyAQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_guitar_wah::cReceive_uuPTVOY4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_I9V5P995, 0, m, &cVar_I9V5P995_sendMessage);
}

void Heavy_guitar_wah::cVar_6xo2fYox_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_guitar_wah::cCast_hQAh4z4J_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_YVlqYutm, HV_BINOP_SUBTRACT, 0, m, &cBinop_YVlqYutm_sendMessage);
}

void Heavy_guitar_wah::cVar_fZAMdWsL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_YVlqYutm, HV_BINOP_SUBTRACT, 0, m, &cBinop_YVlqYutm_sendMessage);
}

void Heavy_guitar_wah::cVar_Wzg8wvfE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_guitar_wah::cMsg_nMMA4Oea_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 2.0f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 0.0f, 0, m, &cBinop_YEYowrwZ_sendMessage);
}

void Heavy_guitar_wah::cBinop_zEXIJ3z2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_vkdO7h5k, m);
}

void Heavy_guitar_wah::cMsg_mouEMmqG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 6.28319f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 0.0f, 0, m, &cBinop_IIw8mTNu_sendMessage);
}

void Heavy_guitar_wah::cMsg_1M6wvoMX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 2.0f, 0, m, &cBinop_Z9BGJHQu_sendMessage);
}

void Heavy_guitar_wah::cBinop_9HDcgU9N_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_ka8yPoIW, m);
}

void Heavy_guitar_wah::cBinop_Z9BGJHQu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_nMMA4Oea_sendMessage(_c, 0, m);
}

void Heavy_guitar_wah::cIf_un3FSksJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cMsg_1M6wvoMX_sendMessage(_c, 0, m);
      cMsg_xo7IkE5S_sendMessage(_c, 0, m);
      break;
    }
    case 1: {
      cMsg_AquGw69A_sendMessage(_c, 0, m);
      cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 2.0f, 0, m, &cBinop_Z9BGJHQu_sendMessage);
      sVarf_onMessage(_c, &Context(_c)->sVarf_4UtP56D2, m);
      break;
    }
    default: return;
  }
}

void Heavy_guitar_wah::cBinop_klo1Y6Li_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_un3FSksJ, 1, m, &cIf_un3FSksJ_sendMessage);
}

void Heavy_guitar_wah::cMsg_oDLP9kEz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_WN3EmOj0_sendMessage);
}

void Heavy_guitar_wah::cSystem_WN3EmOj0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_mouEMmqG_sendMessage(_c, 0, m);
}

void Heavy_guitar_wah::cMsg_zv4pNIHm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 2.0f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 0.0f, 0, m, &cBinop_zEXIJ3z2_sendMessage);
}

void Heavy_guitar_wah::cVar_8WmemQVH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_GREATER_THAN_EQL, 1e-05f, 0, m, &cBinop_klo1Y6Li_sendMessage);
  cIf_onMessage(_c, &Context(_c)->cIf_un3FSksJ, 0, m, &cIf_un3FSksJ_sendMessage);
}

void Heavy_guitar_wah::cBinop_IIw8mTNu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_xQc5lZEa, m);
}

void Heavy_guitar_wah::cBinop_YEYowrwZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_zv4pNIHm_sendMessage(_c, 0, m);
}

void Heavy_guitar_wah::cMsg_AquGw69A_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 0.0f, 0, m, &cBinop_9HDcgU9N_sendMessage);
}

void Heavy_guitar_wah::cMsg_xo7IkE5S_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, -1.0f);
  sVarf_onMessage(_c, &Context(_c)->sVarf_ka8yPoIW, m);
  sVarf_onMessage(_c, &Context(_c)->sVarf_4UtP56D2, m);
}

void Heavy_guitar_wah::cBinop_YVlqYutm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_oHxRiyAQ, 0, m, &cVar_oHxRiyAQ_sendMessage);
  sVarf_onMessage(_c, &Context(_c)->sVarf_AGcf4SHR, m);
}

void Heavy_guitar_wah::cReceive_6cEL1NXt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_e4hGIjek, 0, m, &cVar_e4hGIjek_sendMessage);
}




/*
 * Context Process Implementation
 */

int Heavy_guitar_wah::process(float **inputBuffers, float **outputBuffers, int n) {
  while (hLp_hasData(&inQueue)) {
    hv_uint32_t numBytes = 0;
    ReceiverMessagePair *p = reinterpret_cast<ReceiverMessagePair *>(hLp_getReadBuffer(&inQueue, &numBytes));
    hv_assert(numBytes >= sizeof(ReceiverMessagePair));
    scheduleMessageForReceiver(p->receiverHash, &p->msg);
    hLp_consume(&inQueue);
  }
  const int n4 = n & ~HV_N_SIMD_MASK; // ensure that the block size is a multiple of HV_N_SIMD

  // temporary signal vars
  hv_bufferf_t Bf0, Bf1, Bf2, Bf3, Bf4;

  // input and output vars
  hv_bufferf_t O0, O1;
  hv_bufferf_t I0, I1;

  // declare and init the zero buffer
  hv_bufferf_t ZERO; __hv_zero_f(VOf(ZERO));

  hv_uint32_t nextBlock = blockStartTimestamp;
  for (int n = 0; n < n4; n += HV_N_SIMD) {

    // process all of the messages for this block
    nextBlock += HV_N_SIMD;
    while (mq_hasMessageBefore(&mq, nextBlock)) {
      MessageNode *const node = mq_peek(&mq);
      node->sendMessage(this, node->let, node->m);
      mq_pop(&mq);
    }

    // load input buffers
    __hv_load_f(inputBuffers[0]+n, VOf(I0));
    __hv_load_f(inputBuffers[1]+n, VOf(I1));

    // zero output buffers
    __hv_zero_f(VOf(O0));
    __hv_zero_f(VOf(O1));

    // process all signal functions
    __hv_phasor_k_f(&sPhasor_cd618YKz, VOf(Bf0));
    __hv_var_k_f(VOf(Bf1), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_abs_f(VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf0), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf1), 6.28318530718f, 6.28318530718f, 6.28318530718f, 6.28318530718f, 6.28318530718f, 6.28318530718f, 6.28318530718f, 6.28318530718f);
    __hv_mul_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_mul_f(VIf(Bf1), VIf(Bf1), VOf(Bf0));
    __hv_mul_f(VIf(Bf1), VIf(Bf0), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf3), 0.00783333333333f, 0.00783333333333f, 0.00783333333333f, 0.00783333333333f, 0.00783333333333f, 0.00783333333333f, 0.00783333333333f, 0.00783333333333f);
    __hv_var_k_f(VOf(Bf4), -0.166666666667f, -0.166666666667f, -0.166666666667f, -0.166666666667f, -0.166666666667f, -0.166666666667f, -0.166666666667f, -0.166666666667f);
    __hv_fma_f(VIf(Bf2), VIf(Bf4), VIf(Bf1), VOf(Bf1));
    __hv_fma_f(VIf(Bf0), VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf3), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_add_f(VIf(Bf1), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf1), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_mul_f(VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_varread_f(&sVarf_AGcf4SHR, VOf(Bf3));
    __hv_varread_f(&sVarf_vQISq2wQ, VOf(Bf0));
    __hv_fma_f(VIf(Bf1), VIf(Bf3), VIf(Bf0), VOf(Bf0));
    __hv_varread_f(&sVarf_xQc5lZEa, VOf(Bf3));
    __hv_mul_f(VIf(Bf0), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf0), 1e-05f, 1e-05f, 1e-05f, 1e-05f, 1e-05f, 1e-05f, 1e-05f, 1e-05f);
    __hv_max_f(VIf(Bf3), VIf(Bf0), VOf(Bf0));
    __hv_varread_f(&sVarf_4UtP56D2, VOf(Bf3));
    __hv_min_f(VIf(Bf0), VIf(Bf3), VOf(Bf3));
    __hv_varread_f(&sVarf_ka8yPoIW, VOf(Bf1));
    __hv_mul_f(VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_mul_f(VIf(I0), VIf(Bf1), VOf(Bf3));
    __hv_varread_f(&sVarf_vkdO7h5k, VOf(Bf4));
    __hv_mul_f(VIf(Bf3), VIf(Bf4), VOf(Bf4));
    __hv_var_k_f(VOf(Bf3), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_sub_f(VIf(Bf1), VIf(Bf3), VOf(Bf1));
    __hv_cos_f(VIf(Bf0), VOf(Bf0));
    __hv_mul_f(VIf(Bf1), VIf(Bf0), VOf(Bf2));
    __hv_mul_f(VIf(Bf0), VIf(Bf0), VOf(Bf0));
    __hv_sub_f(VIf(Bf3), VIf(Bf0), VOf(Bf0));
    __hv_zero_f(VOf(Bf3));
    __hv_gt_f(VIf(Bf0), VIf(Bf3), VOf(Bf3));
    __hv_sqrt_f(VIf(Bf0), VOf(Bf0));
    __hv_and_f(VIf(Bf3), VIf(Bf0), VOf(Bf0));
    __hv_mul_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_cpole_f(&sCPole_p4Nk471Y, VIf(Bf4), VIf(ZERO), VIf(Bf2), VIf(Bf0), VOf(Bf0), VOf(Bf2));
    __hv_add_f(VIf(Bf0), VIf(O0), VOf(O0));
    __hv_add_f(VIf(Bf0), VIf(O1), VOf(O1));

    // save output vars to output buffer
    __hv_store_f(outputBuffers[0]+n, VIf(O0));
    __hv_store_f(outputBuffers[1]+n, VIf(O1));
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed
}

int Heavy_guitar_wah::processInline(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(!(n4 & HV_N_SIMD_MASK)); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 2 channel(s)
  float **const bIn = reinterpret_cast<float **>(hv_alloca(2*sizeof(float *)));
  bIn[0] = inputBuffers+(0*n4);
  bIn[1] = inputBuffers+(1*n4);

  // define the heavy output buffer for 2 channel(s)
  float **const bOut = reinterpret_cast<float **>(hv_alloca(2*sizeof(float *)));
  bOut[0] = outputBuffers+(0*n4);
  bOut[1] = outputBuffers+(1*n4);

  int n = process(bIn, bOut, n4);
  return n;
}

int Heavy_guitar_wah::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(n4 & ~HV_N_SIMD_MASK); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 2 channel(s), uninterleave
  float *const bIn = reinterpret_cast<float *>(hv_alloca(2*n4*sizeof(float)));
  #if HV_SIMD_SSE || HV_SIMD_AVX
  for (int i = 0, j = 0; j < n4; j += 4, i += 8) {
    __m128 a = _mm_load_ps(inputBuffers+i);                // LRLR
    __m128 b = _mm_load_ps(inputBuffers+4+i);              // LRLR
    __m128 x = _mm_shuffle_ps(a, b, _MM_SHUFFLE(2,0,2,0)); // LLLL
    __m128 y = _mm_shuffle_ps(a, b, _MM_SHUFFLE(3,1,3,1)); // RRRR
    _mm_store_ps(bIn+j, x);
    _mm_store_ps(bIn+n4+j, y);
  }
  #elif HV_SIMD_NEON
  for (int i = 0, j = 0; j < n4; j += 4, i += 8) {
    float32x4x2_t a = vld2q_f32(inputBuffers+i); // load and uninterleave
    vst1q_f32(bIn+j, a.val[0]);
    vst1q_f32(bIn+n4+j, a.val[1]);
  }
  #else // HV_SIMD_NONE
  for (int j = 0; j < n4; ++j) {
    bIn[0*n4+j] = inputBuffers[0+2*j];
    bIn[1*n4+j] = inputBuffers[1+2*j];
  }
  #endif

  // define the heavy output buffer for 2 channel(s)
  float *const bOut = reinterpret_cast<float *>(hv_alloca(2*n4*sizeof(float)));

  int n = processInline(bIn, bOut, n4);

  // interleave the heavy output into the output buffer
  #if HV_SIMD_AVX
  for (int i = 0, j = 0; j < n4; j += 8, i += 16) {
    __m256 x = _mm256_load_ps(bOut+j);    // LLLLLLLL
    __m256 y = _mm256_load_ps(bOut+n4+j); // RRRRRRRR
    __m256 a = _mm256_unpacklo_ps(x, y);  // LRLRLRLR
    __m256 b = _mm256_unpackhi_ps(x, y);  // LRLRLRLR
    _mm256_store_ps(outputBuffers+i, a);
    _mm256_store_ps(outputBuffers+8+i, b);
  }
  #elif HV_SIMD_SSE
  for (int i = 0, j = 0; j < n4; j += 4, i += 8) {
    __m128 x = _mm_load_ps(bOut+j);    // LLLL
    __m128 y = _mm_load_ps(bOut+n4+j); // RRRR
    __m128 a = _mm_unpacklo_ps(x, y);  // LRLR
    __m128 b = _mm_unpackhi_ps(x, y);  // LRLR
    _mm_store_ps(outputBuffers+i, a);
    _mm_store_ps(outputBuffers+4+i, b);
  }
  #elif HV_SIMD_NEON
  // https://community.arm.com/groups/processors/blog/2012/03/13/coding-for-neon--part-5-rearranging-vectors
  for (int i = 0, j = 0; j < n4; j += 4, i += 8) {
    float32x4_t x = vld1q_f32(bOut+j);
    float32x4_t y = vld1q_f32(bOut+n4+j);
    float32x4x2_t z = {x, y};
    vst2q_f32(outputBuffers+i, z); // interleave and store
  }
  #else // HV_SIMD_NONE
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < n4; ++j) {
      outputBuffers[i+2*j] = bOut[i*n4+j];
    }
  }
  #endif

  return n;
}
