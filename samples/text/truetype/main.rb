emulogic = RubyAction::TTFont.new "emulogic.ttf", 120
almendra = RubyAction::TTFont.new "almendra.ttf", 200

text = RubyAction::TextField.new emulogic, "Emulogic"
text.size = [400, 60]
text.anchor = [0.5, 0.5]
text.position = [400, 300]
text.color = [255, 123, 235]

RubyAction::Stage << text

text = RubyAction::TextField.new almendra, "Almendra"
text.size = [700, 200]
text.anchor = [0.5, 0.5]
text.position = [400, 300]
text.color = [0, 255, 0]
text.rotation = 45

RubyAction::Stage << text
