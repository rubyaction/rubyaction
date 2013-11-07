font = RubyAction::TTFont.new "emulogic.ttf", 64

text = RubyAction::TextField.new font, "Hello World"
text.size = [400, 60]
text.anchor = [0.5, 0.5]
text.position = [400, 300]
text.color = [255, 123, 235]

RubyAction::Stage << text
