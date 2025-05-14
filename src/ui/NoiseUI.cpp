#include "ui/NoiseUI.hpp"

NoiseUI::NoiseUI(NoiseNinjaProcessor& p)
    : AudioProcessorEditor(&p), processor(p)
{
    gainSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    gainLabel.setText("Gain (dB)", juce::dontSendNotification);
    addAndMakeVisible(gainLabel);
    addAndMakeVisible(gainSlider);
    gainAttachment = std::make_unique<Attachment>(processor.parameters, "gain", gainSlider);

    suppressBox.addItem("Soft", 1);
    suppressBox.addItem("Medium", 2);
    suppressBox.addItem("Strict", 3);
    addAndMakeVisible(suppressBox);
    suppressAttachment = std::make_unique<ChoiceAttachment>(processor.parameters, "suppressLevel", suppressBox);

    setSize(400, 200);
}

NoiseUI::~NoiseUI() {}

void NoiseUI::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
}

void NoiseUI::resized()
{
    auto area = getLocalBounds().reduced(20);
    auto row  = area.removeFromTop(100);

    gainLabel.setBounds(row.removeFromLeft(100));
    gainSlider.setBounds(row.removeFromLeft(150));

    suppressBox.setBounds(area.removeFromTop(40));
}