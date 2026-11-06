#pragma once 

namespace compressedor
{
     namespace {
        auto& addParameterToProcessor(juce::AudioProcessor& processor, auto parameter){
        auto& parameterReference = *parameter;
        processor.addParameter(parameter.release());
        return parameterReference;
        }

        juce::AudioParameterFloat& createThresholdParameter(juce::AudioProcessor& processor) {
         constexpr int versionHint = 1;

         auto parameter = std::make_unique<juce::AudioParameterFloat>(
            juce::ParameterID("Threshold", versionHint),
            "Threshold",
            juce::NormalisableRange{-24.f, 0.f, 0.1f},
            0.f,
            juce::AudioParameterFloatAttributes{}.withLabel("dB")
         );

         return addParameterToProcessor(processor, std::move(parameter));

        }

        juce::AudioParameterFloat& createAttackParameter(juce::AudioProcessor& processor) {
         constexpr int versionHint = 1;
         auto parameter = std::make_unique<juce::AudioParameterFloat>(
            juce::ParameterID("Attack", versionHint),
            "Attack",
            juce::NormalisableRange(3.f, 300.f, 1.f),
            3.f,
            juce::AudioParameterFloatAttributes{}.withLabel("ms")
         );

         return addParameterToProcessor(processor, std::move(parameter));
        }

         juce::AudioParameterFloat& createReleaseParameter(juce::AudioProcessor& processor) {
         constexpr int versionHint = 1;
         auto parameter = std::make_unique<juce::AudioParameterFloat>(
            juce::ParameterID("Release", versionHint),
            "Release",
            juce::NormalisableRange(3.f, 300.f, 1.f),
            3.f,
            juce::AudioParameterFloatAttributes{}.withLabel("ms")
         );

         return addParameterToProcessor(processor, std::move(parameter));
        }

         juce::AudioParameterFloat& createRatioParameter(juce::AudioProcessor& processor) {
         constexpr int versionHint = 1;
         auto parameter = std::make_unique<juce::AudioParameterFloat>(
            juce::ParameterID("Ratio", versionHint),
            "Ratio",
            juce::NormalisableRange(1.f, 20.f, 1.f),
            1.f,
            juce::AudioParameterFloatAttributes{}.withLabel(" / 1")
         );

         return addParameterToProcessor(processor, std::move(parameter));
        }



     }

     Parameters::Parameters(juce::AudioProcessor& processor) :
     threshold{createThresholdParameter(processor)},
     attack{createAttackParameter(processor)},
     release{createReleaseParameter(processor)},
     ratio{createRatioParameter(processor)}
     {
      juce::ignoreUnused(processor);
     }
    
} // namespace compressedor
