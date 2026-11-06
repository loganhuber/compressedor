#pragma once

namespace compressedor {

    class Compressedor {
        public:

        void setCompressorSettings(
                    float thresholdLevel, 
                    float attackLevel, 
                    float releaseLevel, 
                    float ratioLevel) 
        {
            threshold = thresholdLevel;
            attack = attackLevel;
            release = releaseLevel;
            ratio = ratioLevel;

            setSaturation(thresholdLevel, ratioLevel);
        }

        void setSaturation(float thresholdLevel, float ratioLevel) {
            float newSaturation = (-thresholdLevel + ratioLevel) / 100;
            saturation.setTargetValue(newSaturation);
        }

        void prepare(double sampleRate, int expectedMaxFramesPerBlock, int numChannels) {

            compressor.reset();
            compressor.setAttack(3.f);
            compressor.setRatio(20.f);
            compressor.setRelease(3.f);
            compressor.setThreshold(threshold.getCurrentValue());

            threshold.reset(sampleRate, .1f);
            attack.reset(sampleRate, 0.1f);
            release.reset(sampleRate, 0.1f);
            ratio.reset(sampleRate, 0.1f);

            saturation.reset(sampleRate, 0.1f);

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
                const auto nextAttack = attack.getNextValue();
                const auto nextRelease = release.getNextValue();
                const auto nextRatio = ratio.getNextValue();

                const auto nextSaturation = saturation.getNextValue();

                compressor.setThreshold(nextThreshold);
                compressor.setAttack(nextAttack);
                compressor.setRelease(nextRelease);
                compressor.setRatio(nextRatio);

                for (const auto channelIndex : std::views::iota(0, buffer.getNumChannels())) {
                    const auto inputSample = buffer.getSample(channelIndex, frameIndex);

                    const auto shaped = std::tanh(inputSample * nextSaturation) / std::tanh(nextSaturation);
                    const auto compressedSample = compressor.processSample(channelIndex, shaped);

                    buffer.setSample(channelIndex, frameIndex, compressedSample);

                }
            }
        }




        private:
            juce::dsp::Compressor<float> compressor;
            juce::SmoothedValue<float> threshold = 0.f;
            juce::SmoothedValue<float> attack = 3.f;
            juce::SmoothedValue<float> release = 3.f;
            juce::SmoothedValue<float> ratio = 1.f;

            juce::SmoothedValue<float> saturation = 0.f;

    };
} // namespace compressedor