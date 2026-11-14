#pragma once

namespace compressedor {
class PluginEditor : public juce::AudioProcessorEditor {
public:
  explicit PluginEditor(PluginProcessor&);

  void paint(juce::Graphics&) override;
  void resized() override;

private:

  juce::ImageComponent background;

  juce::Slider thresholdSlider;
  juce::SliderParameterAttachment thresholdAttachment;
  juce::Label thresholdLabel;

  juce::Slider attackSlider;
  juce::SliderParameterAttachment attackAttachment;
  juce::Label attackLabel;

  juce::Slider releaseSlider;
  juce::SliderParameterAttachment releaseAttachment;
  juce::Label releaseLabel;

  juce::Slider ratioSlider;
  juce::SliderParameterAttachment ratioAttachment;
  juce::Label ratioLabel;


  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
}  // namespace compressedor
