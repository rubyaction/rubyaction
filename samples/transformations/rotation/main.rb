# background
background = RubyAction::Bitmap.new RubyAction::Texture.new "background.jpg"
RubyAction::Stage << background

# texture
texture = RubyAction::Texture.new "crate.png"

# crate
crate = RubyAction::Bitmap.new texture
crate.position = [400, 300]
crate.anchor = [0.5, 0.5]
crate.rotation = 45
RubyAction::Stage << crate

RubyAction::Stage.on :enter_frame do |dt|
  crate.rotation += dt * 100
end
