namespace compressedor {
PluginEditor::PluginEditor(PluginProcessor& p)
    : AudioProcessorEditor(&p), 
    thresholdAttachment{p.getParameterRefs().threshold, thresholdSlider},
    attackAttachment{p.getParameterRefs().attack, attackSlider} {

  
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


  // labels 
  thresholdLabel.setText("Threshold", juce::dontSendNotification);
  attackLabel.setText("Attack", juce::dontSendNotification);

  addAndMakeVisible(background);
  addAndMakeVisible(thresholdSlider);
  addAndMakeVisible(attackSlider);
  addAndMakeVisible(thresholdLabel);
  addAndMakeVisible(attackLabel);
  setSize(600, 400);
}

void PluginEditor::paint(juce::Graphics& g) {
  // (Our component is opaque, so we must completely fill the background with a
  juce::ignoreUnused(g);
}

void PluginEditor::resized() {
  const auto bounds = getLocalBounds();
  background.setBounds(bounds);

  attackSlider.setBounds({25, 250, 100, 100});
  attackLabel.setBounds({50, 340, 100, 40});

  thresholdSlider.setBounds({25, 125, 100, 100});
  thresholdLabel.setBounds({45, 215, 100, 40});
}
}  // namespace compressedor
