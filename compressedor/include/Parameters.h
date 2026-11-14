#pragma once

namespace compressedor {

    struct Parameters {
        explicit Parameters(juce::AudioProcessor&);

        juce::AudioParameterFloat& threshold;
        juce::AudioParameterFloat& attack;
        juce::AudioParameterFloat& release;
        juce::AudioParameterFloat& ratio;
        juce::AudioParameterFloat& makeup;


        JUCE_DECLARE_NON_COPYABLE(Parameters)
        JUCE_DECLARE_NON_MOVEABLE(Parameters)
    };

} // namespace compressedor