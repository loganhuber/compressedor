#pragma once

namespace compressedor {
class PluginEditor : public juce::AudioProcessorEditor {
public:
  explicit PluginEditor(PluginProcessor&);

  void paint(juce::Graphics&) override;
  void resized() override;

private:

  juce::Slider thresholdSlider;
  juce::SliderParameterAttachment thresholdAttachment;
  juce::Label thresholdLabel;

  juce::Slider attackSlider;
  juce::SliderParameterAttachment attackAttachment;
  juce::Label attackLabel;


  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
}  // namespace compressedor
