#pragma once

namespace compressedor {

    class Compressedor {
        public:

        std::unique_ptr<juce::dsp::Oversampling<float>> overSampler;


        void setCompressorSettings(
                    float thresholdLevel, 
                    float attackLevel, 
                    float releaseLevel, 
                    float ratioLevel) 
        {
            threshold.setTargetValue(thresholdLevel);
            attack.setTargetValue(attackLevel);
            release.setTargetValue(releaseLevel);
            ratio.setTargetValue(ratioLevel);

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

            juce::ScopedNoDenormals noDenormals;

            juce::dsp::AudioBlock<float> originalBuffer (buffer);

            juce::dsp::AudioBlock<float> upsampledBlock = overSampler->processSamplesUp(originalBuffer);

            for (size_t frameIndex = 0; frameIndex < upsampledBlock.getNumSamples(); ++frameIndex) {

                const auto nextThreshold = threshold.getNextValue();
                const auto nextAttack = attack.getNextValue();
                const auto nextRelease = release.getNextValue();
                const auto nextRatio = ratio.getNextValue();

                const auto nextSaturation = saturation.getNextValue();

                compressor.setThreshold(nextThreshold);
                compressor.setAttack(nextAttack);
                compressor.setRelease(nextRelease);
                compressor.setRatio(nextRatio);

                for (size_t channelIndex = 0; channelIndex < upsampledBlock.getNumChannels(); ++channelIndex) {
                    const auto inputSample = upsampledBlock.getSample(channelIndex, frameIndex);

                    const auto shaped = nextSaturation > 1.0e-6f // check if 
                        ? std::tanh(inputSample * nextSaturation) / std::tanh(nextSaturation)
                        : inputSample;

                    const auto compressedSample = compressor.processSample(channelIndex, shaped);

                    upsampledBlock.setSample(channelIndex, frameIndex, compressedSample);
                }
            }

            overSampler->processSamplesDown (originalBuffer);
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