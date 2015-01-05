# background
background = RubyAction::Bitmap.new RubyAction::Texture.new "background.jpg"
RubyAction::Stage << background

# texture
texture = RubyAction::Texture.new "crate.png"

# crate1
crate1 = RubyAction::Bitmap.new texture
crate1.position = [400, 300]
crate1.anchor = [0.5, 0.5]
crate1.scale = [2, 2]
RubyAction::Stage << crate1

# crate2
crate2 = RubyAction::Bitmap.new texture
crate2.position = [90, 90]
crate2.anchor = [0.5, 0.5]
crate2.scale = [0.5, 0.5]
crate1 << crate2

RubyAction::Stage.on :enter_frame do |dt|
  angle = dt * 100
  crate1.rotation += angle
  crate2.rotation -= angle
end
