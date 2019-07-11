#include "Fourses.h"
#include "IPlug_include_in_plug_src.h"

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
    const IRECT b = pGraphics->GetBounds();

    pGraphics->AttachCornerResizer(EUIResizerMode::Scale, false);
    pGraphics->AttachPanelBackground(IPattern::CreateLinearGradient(b, EDirection::Horizontal, {{COLOR_RED, 0.}, {COLOR_ORANGE, 1.}}));
    pGraphics->LoadFont("Amatic-Bold", FONT_FN);
    
    IVStyle style {
      true, // Show label
      true, // Show value
      {
        COLOR_TRANSPARENT, // Background
        COLOR_WHITE, // Foreground
        DEFAULT_PRCOLOR, // Pressed
        COLOR_BLACK, // Frame
      }, // Colors
      IText(100, "Amatic-Bold"),
    };
    
    auto area = b.GetReducedFromTop(100.);

    pGraphics->AttachControl(new IVLabelControl(b.GetFromTRHC(200, 100), "Fourses", style));
    pGraphics->AttachControl(new IVButtonControl(b.GetFromTLHC(200, 100).GetPadded(-20), [](IControl* pCaller){ SplashClickActionFunc(pCaller); pCaller->GetDelegate()->SendArbitraryMsgFromUI(kMsgTagRandomise); }, "Randomise", style.WithLabelText(IText(50, "Amatic-Bold"))));
    pGraphics->AttachControl(new IVMultiSliderControl<kNumParams>(area.GetFromLeft(400.).GetPadded(-10.f), "", style, 0, EDirection::Vertical, 0., 1.));
    pGraphics->AttachControl(new IVScopeControl<2>(area.GetFromRight(210.).GetPadded(-10.f), "", style.WithColor(kFG, COLOR_BLACK)), kCtrTagScope);
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
bool Fourses::OnMessage(int messageTag, int controlTag, int dataSize, const void* pData)
{
  if(messageTag == kMsgTagRandomise) {
    RandomiseParamValues();
    OnParamReset(EParamSource::kUnknown);
    SendCurrentParamValuesFromDelegate();
    return true;
  }
  
  return false;
}

void Fourses::OnIdle()
{
  mScopeSender.TransmitData(*this);
}

void Fourses::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
  gen_dsp::perform(mGenDSPState, inputs, 2, outputs, 2 /*num_outputs*/, nFrames);
  mScopeSender.ProcessBlock(outputs, nFrames);
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
