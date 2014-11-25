require "tween"

# background
background = RubyAction::Bitmap.new RubyAction::Texture.new "background.jpg"
RubyAction::Stage << background

# texture
texture = RubyAction::Texture.new "crate.png"

# crate
crate = RubyAction::Bitmap.new texture
crate.position = [100, 100]
crate.anchor = [0.5, 0.5]
RubyAction::Stage << crate

start = { x: crate.x, y: crate.y, r: crate.rotation, w: crate.width, h: crate.height }
finish = { x: 700, y: 500, r: 720, w: 0, h: 0 }

tween = Tween.new(start, finish, Tween::Linear, 4)
tween.on :complete do
  tween = Tween.new(finish, start, Tween::Linear, 4)
end

RubyAction::Stage.on :enter_frame do |dt|
  tween.update dt
  crate.x = tween[:x]
  crate.y = tween[:y]
  crate.width = tween[:w]
  crate.height = tween[:h]
  crate.rotation = tween[:r]
end
