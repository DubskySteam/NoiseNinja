#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ui/NoiseUI.hpp"

NoiseCancellerAudioProcessorEditor::NoiseCancellerAudioProcessorEditor(NoiseNinjaProcessor& p)
    : NoiseUI(p) {}

NoiseCancellerAudioProcessorEditor::~NoiseCancellerAudioProcessorEditor() = default;
