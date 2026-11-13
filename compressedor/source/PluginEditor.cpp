namespace compressedor {
PluginEditor::PluginEditor(PluginProcessor& p)
    : AudioProcessorEditor(&p), 
    thresholdAttachment{p.getParameterRefs().threshold, thresholdSlider},
    attackAttachment{p.getParameterRefs().attack, attackSlider} {

  
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


  addAndMakeVisible(thresholdSlider);
  addAndMakeVisible(attackSlider);
  addAndMakeVisible(thresholdLabel);
  addAndMakeVisible(attackLabel);
  setSize(600, 400);
}

void PluginEditor::paint(juce::Graphics& g) {
  // (Our component is opaque, so we must completely fill the background with a
  // solid colour)
  g.fillAll(
      getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

  // g.setColour(juce::Colours::white);
  // g.setFont(15.0f);
  // g.drawFittedText("Hello World!", getLocalBounds(),
  //                  juce::Justification::centred, 1);

}

void PluginEditor::resized() {
  // const auto bounds = getLocalBounds();

  attackSlider.setBounds({25, 150, 100, 100});
  attackLabel.setBounds({300, 300, 100, 40});
  thresholdSlider.setBounds({25, 25, 100, 100});
  thresholdLabel.setBounds({25, 45, 100, 40});
}
}  // namespace compressedor
