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
            juce::NormalisableRange{-12.f, 3.f, 0.1f},
            0.f,
            juce::AudioParameterFloatAttributes{}.withLabel("dB")
         );

         return addParameterToProcessor(processor, std::move(parameter));

        }

     }

     Parameters::Parameters(juce::AudioProcessor& processor) :
     threshold{createThresholdParameter(processor)}
     {
      juce::ignoreUnused(processor);
     }
    
} // namespace compressedor
