require "button"

module Game
  include RubyAction

  up = Texture.new("button_up.png")
  down = Texture.new("button_down.png")

  button = Button.new(up, down)
  button.anchor = [0.5, 0.5]
  button.position = [300, 100]
  button.on :click do
    puts "normal button"
  end
  Stage << button

  button = Button.new(up, down)
  button.anchor = [0.5, 0.5]
  button.position = [500, 300]
  button.rotation = 45
  button.on :click do
    puts "angled button"
  end
  Stage << button

  button = Button.new(up, down)
  button.anchor = [0.5, 0.5]
  button.position = [200, 400]
  button.rotation = 90
  button.on :click do
    puts "rotated button"
  end
  Stage << button

end
