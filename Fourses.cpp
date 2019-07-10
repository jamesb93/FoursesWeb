#include "Fourses.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"

Fourses::Fourses(IPlugInstanceInfo instanceInfo)
: IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo)
{
  InitParamRange(0, kNumParams-1, 0, "p", 0., 0., 1., 0.001);
  
#if IPLUG_DSP
  mGenDSPState = (CommonState*) gen_dsp::create(DEFAULT_SAMPLE_RATE, DEFAULT_BLOCK_SIZE);
  gen_dsp::reset(mGenDSPState);
#endif
  
#if IPLUG_EDITOR // All UI methods and member variables should be within an IPLUG_EDITOR guard, should you want distributed UI
  mMakeGraphicsFunc = [&]() {
    return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, 1.);
  };
  
  mLayoutFunc = [&](IGraphics* pGraphics) {
    pGraphics->AttachCornerResizer(EUIResizerMode::Scale, false);
    pGraphics->AttachPanelBackground(COLOR_GRAY);
    pGraphics->LoadFont("Roboto-Regular", ROBOTO_FN);
    const IRECT b = pGraphics->GetBounds();
    //  IVMultiSliderControl(const IRECT& bounds, const char* label, const IVStyle& style, int loParamIdx, EDirection dir, float minTrackValue, float maxTrackValue, const char* trackNames = 0, ...)

    pGraphics->AttachControl(new IVMultiSliderControl<kNumParams>(b.GetPadded(-20.f), "Fourses", DEFAULT_STYLE, 0, EDirection::Vertical, 0., 1.));
  };
#endif
}

Fourses::~Fourses()
{
#if IPLUG_DSP
  gen_dsp::destroy(mGenDSPState);
#endif
}

#if IPLUG_DSP
void Fourses::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
  gen_dsp::perform(mGenDSPState, inputs, 2, outputs, 2 /*num_outputs*/, nFrames);
}

void Fourses::OnReset()
{
  mGenDSPState->sr = GetSampleRate();
  mGenDSPState->vs = GetBlockSize();
  
  gen_dsp::reset(mGenDSPState);
}

void Fourses::OnParamChange(int paramIdx, EParamSource source, int offset)
{
  gen_dsp::setparameter(mGenDSPState, paramIdx, GetParam(paramIdx)->Value(), nullptr);
}
#endif
