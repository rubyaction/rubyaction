# background
background = RubyAction::Bitmap.new RubyAction::Texture.new "background.jpg"
RubyAction::Stage << background

# texture
texture = RubyAction::Texture.new "crate.png"

# crate
crate = RubyAction::Bitmap.new texture
crate.position = [400, 300]
crate.anchor = [0.5, 0.5]
RubyAction::Stage << crate

RubyAction::Stage.on :enter_frame do |dt|
  crate.rotation += dt * 100
end

RubyAction::Stage.on :mouse_down do |button, x, y|
	x, y = crate.scale
  crate.scale = [x * 1.1, y * 1.1] if button == 0
  crate.scale = [x * 0.9, y * 0.9] if button == 1
end

