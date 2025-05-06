#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    addAndMakeVisible(presetSelector);
    presetSelector.addItem("Light", 1);
    presetSelector.addItem("Medium", 2);
    presetSelector.addItem("Aggressive", 3);
    presetSelector.setSelectedId(1);

    addAndMakeVisible(knob1);
    addAndMakeVisible(knob2);
    
    knob1.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knob2.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::darkred);
    getLookAndFeel().setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lightskyblue);
    getLookAndFeel().setColour(juce::ComboBox::backgroundColourId, juce::Colours::whitesmoke.withAlpha(0.8f));

    setSize (600, 400);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    juce::ColourGradient gradient(
        juce::Colours::skyblue.brighter(0.2f).withAlpha(0.8f), 
        getWidth()/2.f, getHeight()*0.7f,
        juce::Colours::pink.withAlpha(0.9f), 
        getWidth()/2.f, getHeight()/2.f,
        true
    );
    g.setGradientFill(gradient);
    g.fillAll();

    g.setColour(juce::Colours::white);
    g.setFont(juce::Font("Arial Rounded MT Bold", 36.0f, juce::Font::plain));
    g.drawText("NoiseNinja", getLocalBounds().removeFromTop(100), juce::Justification::centred);    
}

void AudioPluginAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(20);
    auto header = area.removeFromTop(100);
    area.removeFromTop(20);    

    presetSelector.setBounds(area.removeFromTop(30).reduced(100, 0));
    area.removeFromTop(40);
    
    auto knobArea = area.removeFromTop(150);
    knob1.setBounds(knobArea.removeFromLeft(150).reduced(20));
    knob2.setBounds(knobArea.removeFromRight(150).reduced(20));
}