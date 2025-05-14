#pragma once

#include "PluginProcessor.h"
#include "ui/NoiseUI.hpp"

class NoiseCancellerAudioProcessorEditor : public NoiseUI
{
public:
    explicit NoiseCancellerAudioProcessorEditor(NoiseNinjaProcessor&);
    ~NoiseCancellerAudioProcessorEditor() override;
};
