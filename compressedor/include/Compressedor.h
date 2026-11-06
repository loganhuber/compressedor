#pragma once

namespace compressedor {

    class Compressedor {
        public:

        void prepare(double sampleRate, int samplesPerBlock) {
            juce::ignoreUnused(sampleRate);
            juce::ignoreUnused(samplesPerBlock);
            return;
        }

        void process(juce::AudioBuffer<float>& buffer) {
            juce::ignoreUnused(buffer);
            return;
        }

    };
} // namespace compressedor