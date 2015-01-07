emulogic = RubyAction::Font.new "emulogic.txt", "emulogic.png"
almendra = RubyAction::Font.new "almendra.txt", "almendra.png"

text = RubyAction::TextField.new emulogic, "Emulogic"
text.size = [400, 60]
text.anchor = [0.5, 0.5]
text.position = [400, 300]
text.color = [255, 123, 235, 255]

RubyAction::Stage << text

text = RubyAction::TextField.new almendra, "Almendra"
text.size = [600, 200]
text.anchor = [0.5, 0.5]
text.position = [400, 300]
text.color = [0, 255, 0, 100]
text.rotation = 45

RubyAction::Stage << text
