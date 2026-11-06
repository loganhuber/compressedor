#pragma once

namespace compressedor {

    class Compressedor {
        public:

        void setThreshold(float thresholdLevel) {
            threshold = thresholdLevel;
        }

        void prepare(double sampleRate, int expectedMaxFramesPerBlock, int numChannels) {

            compressor.reset();
            compressor.setAttack(3.f);
            compressor.setRatio(20.f);
            compressor.setRelease(3.f);
            compressor.setThreshold(threshold.getCurrentValue());

            threshold.reset(sampleRate, .1f);

            juce::dsp::ProcessSpec spec {
                .sampleRate = sampleRate,
                .maximumBlockSize = static_cast<juce::uint32>(expectedMaxFramesPerBlock),
                .numChannels = static_cast<juce::uint32>(numChannels)
            };

            compressor.prepare(spec);

        }

        void process(juce::AudioBuffer<float>& buffer) {

            for (const auto frameIndex : std::views::iota(0, buffer.getNumSamples())) {

                const auto nextThreshold = threshold.getNextValue();
                compressor.setThreshold(nextThreshold);

                for (const auto channelIndex : std::views::iota(0, buffer.getNumChannels())) {
                    const auto inputSample = buffer.getSample(channelIndex, frameIndex);

                    const auto compressedSample = compressor.processSample(channelIndex, inputSample);
                    
                    buffer.setSample(channelIndex, frameIndex, compressedSample);

                }
            }
        }




        private:
            juce::dsp::Compressor<float> compressor;
            juce::SmoothedValue<float> threshold = 0.f;

    };
} // namespace compressedor