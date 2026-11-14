namespace compressedor {
PluginEditor::PluginEditor(PluginProcessor& p)
    : AudioProcessorEditor(&p), 
    thresholdAttachment{p.getParameterRefs().threshold, thresholdSlider},
    attackAttachment{p.getParameterRefs().attack, attackSlider},
    releaseAttachment{p.getParameterRefs().release, releaseSlider},
    ratioAttachment{p.getParameterRefs().ratio, ratioSlider},
    makeupAttachment{p.getParameterRefs().makeup, makeupSlider}
    {

  
  background.setImage(juce::ImageCache::getFromMemory(
    assets::compressedorBackground_png, assets::compressedorBackground_pngSize
  ));
  
  thresholdSlider.setSliderStyle(juce::Slider::Rotary);
  thresholdSlider.setPopupDisplayEnabled(true, true, this);
  thresholdSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
  thresholdSlider.setTextValueSuffix("db");

  attackSlider.setSliderStyle(juce::Slider::Rotary);
  attackSlider.setPopupDisplayEnabled(true, true, this);
  attackSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
  attackSlider.setTextValueSuffix("ms");

  releaseSlider.setSliderStyle(juce::Slider::Rotary);
  releaseSlider.setPopupDisplayEnabled(true, true, this);
  releaseSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
  releaseSlider.setTextValueSuffix("ms");


  ratioSlider.setSliderStyle(juce::Slider::Rotary);
  ratioSlider.setPopupDisplayEnabled(true, true, this);
  ratioSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);

  makeupSlider.setSliderStyle(juce::Slider::Rotary);
  makeupSlider.setPopupDisplayEnabled(true, true, this);
  makeupSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
  makeupSlider.setTextValueSuffix("dB");

  // labels 
  thresholdLabel.setText("Threshold", juce::dontSendNotification);
  attackLabel.setText("Attack", juce::dontSendNotification);
  releaseLabel.setText("Release", juce::dontSendNotification);
  ratioLabel.setText("Ratio", juce::dontSendNotification);
  makeupLabel.setText("Makeup", juce::dontSendNotification);

  addAndMakeVisible(background);

  addAndMakeVisible(thresholdSlider);
  addAndMakeVisible(attackSlider);
  addAndMakeVisible(releaseSlider);
  addAndMakeVisible(ratioSlider);
  addAndMakeVisible(makeupSlider);

  addAndMakeVisible(thresholdLabel);
  addAndMakeVisible(attackLabel);
  addAndMakeVisible(releaseLabel);
  addAndMakeVisible(ratioLabel);
  addAndMakeVisible(makeupLabel);

  setSize(600, 400);
}

void PluginEditor::paint(juce::Graphics& g) {
  // (Our component is opaque, so we must completely fill the background with a
  juce::ignoreUnused(g);
}

void PluginEditor::resized() {
  const auto bounds = getLocalBounds();
  background.setBounds(bounds);

  attackSlider.setBounds({50, 250, 100, 100});
  attackLabel.setBounds({75, 332, 100, 40});

  thresholdSlider.setBounds({50, 125, 100, 100});
  thresholdLabel.setBounds({64, 207, 100, 40});

  releaseSlider.setBounds({425, 250, 100, 100});
  releaseLabel.setBounds({444, 332, 100, 40});

  ratioSlider.setBounds({425, 125, 100, 100});
  ratioLabel.setBounds({455, 207, 100, 40});

  makeupSlider.setBounds({245, 150, 100, 100});
  makeupLabel.setBounds({260, 232, 100, 40});

}
}  // namespace compressedor
