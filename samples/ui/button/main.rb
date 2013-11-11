require "button"

up = RubyAction::Bitmap.new(RubyAction::Texture.new("button_up.png"))
down = RubyAction::Bitmap.new(RubyAction::Texture.new("button_down.png"))

button = Button.new(up, down)
button.anchor = [0.5, 0.5]
button.on :click do
  puts "clicked"
end

RubyAction::Stage << button
RubyAction::Stage.anchor = [0.5, 0.5]
RubyAction::Stage.position = [400, 300]
RubyAction::Stage.scale = [2, 1]
RubyAction::Stage.rotation = 45
