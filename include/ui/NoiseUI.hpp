#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class NoiseUI : public juce::AudioProcessorEditor
{
public:
    NoiseUI(NoiseNinjaProcessor& p);
    ~NoiseUI() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    NoiseNinjaProcessor& processor;
    juce::Slider gainSlider;
    juce::Label  gainLabel;
    juce::ComboBox suppressBox;

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ChoiceAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;

    std::unique_ptr<Attachment> gainAttachment;
    std::unique_ptr<ChoiceAttachment> suppressAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NoiseUI)
};