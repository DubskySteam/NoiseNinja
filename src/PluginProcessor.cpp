#include "PluginProcessor.h"
#include "PluginEditor.h"

////==============================================================================
//NoiseNinjaProcessor::NoiseNinjaProcessor()
//     : AudioProcessor (BusesProperties()
//                     #if ! JucePlugin_IsMidiEffect
//                      #if ! JucePlugin_IsSynth
//                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
//                      #endif
//                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
//                     #endif
//                       )
//{
//}

static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // Gain: -60 dB to +12 dB
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "gain", "Gain", juce::NormalisableRange<float>(-60.0f, 12.0f, 0.1f), 0.0f));

    // Noise suppression level
    params.push_back(std::make_unique<juce::AudioParameterChoice>(
        "suppressLevel", "Suppression Level",
        juce::StringArray{"Soft", "Medium", "Strict"}, 0));

    return { params.begin(), params.end() };
}

NoiseNinjaProcessor::NoiseNinjaProcessor()
    : AudioProcessor(BusesProperties()
          .withInput("Input", juce::AudioChannelSet::stereo())
          .withOutput("Output", juce::AudioChannelSet::stereo())),
      parameters(*this, nullptr, "Parameters", createParameterLayout())
{
}

NoiseNinjaProcessor::~NoiseNinjaProcessor()
{
}

//==============================================================================
const juce::String NoiseNinjaProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NoiseNinjaProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NoiseNinjaProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NoiseNinjaProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NoiseNinjaProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NoiseNinjaProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NoiseNinjaProcessor::getCurrentProgram()
{
    return 0;
}

void NoiseNinjaProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String NoiseNinjaProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void NoiseNinjaProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

//==============================================================================
void NoiseNinjaProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused (sampleRate, samplesPerBlock);
}

void NoiseNinjaProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool NoiseNinjaProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}

void NoiseNinjaProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                              juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        juce::ignoreUnused (channelData);
        // ..do something to the data...
    }
}

//==============================================================================
bool NoiseNinjaProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* NoiseNinjaProcessor::createEditor()
{
    return new NoiseCancellerAudioProcessorEditor (*this);
}

//==============================================================================
void NoiseNinjaProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused (destData);
}

void NoiseNinjaProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ignoreUnused (data, sizeInBytes);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NoiseNinjaProcessor();
}
