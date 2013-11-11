require "button"

up = RubyAction::Bitmap.new(RubyAction::Texture.new("button_up.png"))
down = RubyAction::Bitmap.new(RubyAction::Texture.new("button_down.png"))

button = Button.new(up, down)
button.on :click do
  puts "clicked"
end

RubyAction::Stage << button
