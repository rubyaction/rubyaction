# background
background = RubyAction::Bitmap.new RubyAction::Texture.new "background.jpg"
RubyAction::Stage << background

# texture
texture = RubyAction::Texture.new "crate.png"

# crate1
crate1 = RubyAction::Bitmap.new texture
crate1.position = [200, 400]
RubyAction::Stage << crate1

# crate2
crate2 = RubyAction::Bitmap.new texture
crate2.position = [400, 200]
crate2.anchor = [0.5, 0.5]
RubyAction::Stage << crate2

# crate3
crate3 = RubyAction::Bitmap.new texture
crate3.position = [600, 400]
crate3.anchor = [0.5, 1.5]
RubyAction::Stage << crate3

RubyAction::Stage.on :enter_frame do |dt|
  angle = dt * 100
  crate1.rotation += angle
  crate2.rotation += angle
  crate3.rotation += angle
end

