/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class TestTake2AudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    TestTake2AudioProcessor();
    ~TestTake2AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    double rawVolume{ 0.5 };

private:
    juce::dsp::Chorus <float> chorusEffect;

    double gainSmoothed{0.5};
    float lastSample = 0;
    float pitchShift = 1.0f;
    float pitchShiftAmount = 1.0f;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestTake2AudioProcessor)
public:
    void setPitchShift(float newPitchShift) { pitchShift = newPitchShift; }
    float getPitchShift() const { return pitchShift; }
    //void applyPitchShift(juce::AudioBuffer<float>& buffer, float pitchShift);
};
