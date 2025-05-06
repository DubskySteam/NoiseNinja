#pragma once

#include "PluginProcessor.h"

class AudioPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&);
    ~AudioPluginAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
	AudioPluginAudioProcessor &processorRef;

	juce::ComboBox presetSelector;
	juce::Slider knob1;
	juce::Slider knob2;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
};